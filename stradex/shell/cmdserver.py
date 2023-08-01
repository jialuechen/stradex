import os, sys, subprocess
import requests, json
from stradexcmd import stradexShell
from stradex.util.check import stradex_catch

g_server_url = "http://127.0.0.1:520/stradex"
g_api_version = "v1"
g_token = None


def get_url(service, api):
    return "{}/{}/{}/{}".format(g_server_url, service, g_api_version, api)


def login():
    data = json.dumps({'user': 'stradex'})
    url = get_url('login', 'login')
    r = requests.post(url, data)
    global g_token
    g_token = r.json()['stradex_token']


def logout():
    url = get_url('login', 'logout')
    r = requests.post(url, data)


def get_token():
    global g_token
    if g_token is None:
        login()
    return g_token


def get_headers():
    headers = {"stradex_token": get_token(), "User-Agent": "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36"}
    return headers


@stradex_catch()
def start_server():
    if stradexShell.server is not None:
        server_status()
        return
    target = 'stradexserver.exe' if sys.platform == 'win32' else 'stradexserver'
    if os.path.exists(target):
        stradexShell.server = subprocess.Popen([target])
        return

    platform = 'windows'
    if sys.platform == 'linux':
        platform = 'linux'
    elif sys.platform == 'darwin':
        platform = 'macosx'
    target = "./build/release/{}/x64/lib/{}".format(platform, target)
    if os.path.exists(target):
        stradexShell.server = subprocess.Popen([target])
        return

    try:
        import stradex as stradex
        target = "{}/cpp/{}".format(stradex.__path__[0], target)
        if os.path.exists(target):
            stradexShell.server = subprocess.Popen([target])
    except:
        print("Can't found {}".format(target))


def stop_server():
    if stradexShell.server:
        stradexShell.server.terminate()
        stradexShell.server.wait()
        stradexShell.server = None
        print("server stopped.")


def server_status():
    if stradexShell.server is None:
        print("server stopped.")
        return
    url = get_url('assist', 'status')
    headers = get_headers()
    r = requests.get(url, headers=headers)
    print(r.json())


def set_server_logger_level(logger, level):
    url = get_url('assist', 'log_level')
    headers = get_headers()
    data = {'logger': logger, 'level': int(level)} if logger is not None else {'level': int(level)}
    r = requests.post(url, data, headers=headers)
    print(r.json())


def server(self, args):
    
    if args == "":
        start_server()
    x = args.split()
    if not x or x[0] == 'status':
        server_status()
    elif x[0] == 'stop':
        stop_server()
    elif x[0] == 'set_logger_level':
        if len(x) == 2:
            set_server_logger_level(None, x[1])
        else:
            set_server_logger_level(x[1], x[2])
