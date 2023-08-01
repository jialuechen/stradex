from setuptools import setup, find_packages
import sys
import os

if sys.argv[-1] == 'publish':
    os.system("python setup.py bdist_wheel --python-tag cp35 -p win-amd64")
    
    os.system("twine upload dist/*")
    sys.exit()

stradex_name = "stradex"
stradex_version = "0.0.1"
stradex_author = "jialuechen"
stradex_author_email = "jialuechen@outlook.com"

stradex_license = "MIT"
stradex_keywords = ("quant", "trade", "System Trading", "backtester", "量化", "程序化交易", "量化交易", "系统交易")
stradex_platforms = "Independant"
stradex_url = "http://stradex.org/"

stradex_description = "stradex Quant Framework for System Trading Analysis and backtester"
with open("README.rst", encoding='utf-8') as f:
    stradex_long_description = f.read()

if sys.platform == 'win32':
    stradex_data_files = [('Lib/site-packages/stradex', ['stradex/stradex.dll']),
                      ('Lib/site-packages/stradex', ['stradex/stradex_utils.dll']),
                      ('Lib/site-packages/stradex', ['stradex/sqlite3.dll']),
                      ('Lib/site-packages/stradex', ['stradex/importdata.exe']),
                      ('Lib/site-packages/stradex', ['stradex/boost_date_time-vc141-mt-x64-1_68.dll']),
                      ('Lib/site-packages/stradex', ['stradex/boost_filesystem-vc141-mt-x64-1_68.dll']),
                      ('Lib/site-packages/stradex', ['stradex/boost_python35-vc141-mt-x64-1_68.dll']),
                      ('Lib/site-packages/stradex', ['stradex/boost_serialization-vc141-mt-x64-1_68.dll']),
                      ('Lib/site-packages/stradex', ['stradex/boost_system-vc141-mt-x64-1_68.dll']),
                      ('Lib/site-packages/stradex', ['stradex/libmysql.dll']),
                      ('Lib/site-packages/stradex', ['stradex/hdf5.dll']),
                      ('Lib/site-packages/stradex', ['stradex/hdf5_hl.dll']),
                      ('Lib/site-packages/stradex', ['stradex/hdf5_cpp.dll']),
                      ('Lib/site-packages/stradex', ['stradex/hdf5_hl_cpp.dll']),
                      ('Lib/site-packages/stradex', ['stradex/szip.dll']),
                      ('Lib/site-packages/stradex', ['stradex/zlib.dll']),
                      ('Lib/site-packages/stradex', ['stradex/concrt140.dll']),
                      ('Lib/site-packages/stradex', ['stradex/vcruntime140.dll'])]
else:
    stradex_data_files = []

setup(
        name = stradex_name,
        version = stradex_version,
        description = stradex_description,
        long_description = stradex_long_description,
        author = stradex_author,
        author_email = stradex_author_email,

        license = stradex_license,
        keywords = stradex_keywords,
        platforms = stradex_platforms,
        url = stradex_url,

        packages = find_packages(),
        zip_safe = False,
        include_package_data=True,
        package_data = {
            '': ['*.rst', '*.pyd', '*.ini', '*.sql', '*.properties', '*.xml', 'LICENSE.txt', 'lib*.so.*'],
        },
        
        data_files = stradex_data_files,
        
        classifiers=[
            
            
            
            
            'Development Status :: 3 - Alpha',

            
            'Intended Audience :: Developers',
            'Topic :: Software Development :: Libraries :: Python Modules',
            'Topic :: Office/Business :: Financial',
            'Topic :: Office/Business :: Financial :: Investment',
            'Topic :: Scientific/Engineering :: Mathematics',

            
             'License :: OSI Approved :: MIT License',

            'Operating System :: Microsoft :: Windows',
             
            
            
            'Programming Language :: Python :: 3',
            'Programming Language :: Python :: 3.5',
        ],

        install_requires=[
            'matplotlib>=1.5.0',
            
            
            
            'pyecharts>=0.2.7',
        ],        
        )