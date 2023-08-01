

#include <chrono>
#include <nng/nng.h>
#include <nng/protocol/pubsub0/sub.h>
#include "SpotAgent.h"

using namespace stradex::flat;

namespace stradex {

const char* SpotAgent::ms_pubUrl = "ipc:///tmp/stradex_real_pub.ipc";
const char* SpotAgent::ms_startTag = ":spot:[start spot]";
const char* SpotAgent::ms_endTag = ":spot:[end spot]";
const char* SpotAgent::ms_spotTopic = ":spot:";
const size_t SpotAgent::ms_spotTopicLength = strlen(SpotAgent::ms_spotTopic);
const size_t SpotAgent::ms_startTagLength = strlen(SpotAgent::ms_startTag);
const size_t SpotAgent::ms_endTagLength = strlen(SpotAgent::ms_endTag);

Datetime SpotAgent::ms_start_rev_time;

SpotAgent::~SpotAgent() {
    stop();
}

void SpotAgent::start() {
    if (m_stop) {
        m_stop = false;
        m_receiveThread = std::move(std::thread([this]() { work_thread(); }));
    }
}

void SpotAgent::stop() {
    m_stop = true;
    if (m_receiveThread.joinable()) {
        m_receiveThread.join();
    }
}

class ProcessTask {
public:
    ProcessTask(const std::function<void(const SpotRecord&)>& func, const SpotRecord& spot)
    : m_func(func), m_spot(spot) {}

    void operator()() {
        m_func(m_spot);
    }

private:
    std::function<void(const SpotRecord&)> m_func;
    SpotRecord m_spot;
};

unique_ptr<SpotRecord> SpotAgent::parseFlatSpot(const stradex::flat::Spot* spot) {
    SpotRecord* result = nullptr;
    try {
        result = new SpotRecord;
        result->market = spot->market()->str();
        result->code = spot->code()->str();
        result->name = spot->name()->str();
        result->datetime = Datetime(spot->datetime()->str());
        result->yesterday_close = spot->yesterday_close();
        result->open = spot->open();
        result->high = spot->high();
        result->low = spot->low();
        result->close = spot->close();
        result->amount = spot->amount();
        result->volumn = spot->volumn();
        result->bid1 = spot->bid1();
        result->bid1_amount = spot->bid1_amount();
        result->bid2 = spot->bid2();
        result->bid2_amount = spot->bid2_amount();
        result->bid3 = spot->bid3();
        result->bid3_amount = spot->bid3_amount();
        result->bid4 = spot->bid4();
        result->bid4_amount = spot->bid4_amount();
        result->bid5 = spot->bid5();
        result->bid5_amount = spot->bid5_amount();
        result->ask1 = spot->ask1();
        result->ask1_amount = spot->ask1_amount();
        result->ask2 = spot->ask2();
        result->ask2_amount = spot->ask2_amount();
        result->ask3 = spot->ask3();
        result->ask3_amount = spot->ask3_amount();
        result->ask4 = spot->ask4();
        result->ask4_amount = spot->ask4_amount();
        result->ask5 = spot->ask5();
        result->ask5_amount = spot->ask5_amount();

    } catch (std::exception& e) {
        result = nullptr;
        stradex_ERROR(e.what());
    } catch (...) {
        result = nullptr;
        stradex_ERROR_UNKNOWN;
    }

    return unique_ptr<SpotRecord>(result);
}

void SpotAgent::parseSpotData(const void* buf, size_t buf_len) {
    // SPEND_TIME(receive_data);
    const uint8_t* spot_list_buf = (const uint8_t*)(buf) + ms_spotTopicLength;

    // 校验数据
    flatbuffers::Verifier verify(spot_list_buf, buf_len);
    stradex_CHECK(VerifySpotListBuffer(verify), "Invalid data!");

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4267)
#endif

    // 更新日线数据
    auto* spot_list = GetSpotList(spot_list_buf);
    auto* spots = spot_list->spot();
    size_t total = spots->size();
    m_batch_count += total;
    for (size_t i = 0; i < total; i++) {
        auto* spot = spots->Get(i);
        for (auto& process : m_processList) {
            auto spot_record = parseFlatSpot(spot);
            if (spot_record) {
                m_process_task_list.push_back(m_tg.submit(ProcessTask(process, *spot_record)));
            }
        }
    }

#if defined(_MSC_VER)
#pragma warning(pop)
#endif
}

void SpotAgent::work_thread() {
    nng_socket sock;

    int rv = nng_sub0_open(&sock);
    stradex_ERROR_IF_RETURN(rv != 0, void(), "Can't open nng sub0! {}", nng_strerror(rv));

    rv = nng_setopt(sock, NNG_OPT_SUB_SUBSCRIBE, ms_spotTopic, ms_spotTopicLength);
    stradex_ERROR_IF_RETURN(rv != 0, void(), "Failed set nng socket option! {}", nng_strerror(rv));

    rv = nng_setopt_ms(sock, NNG_OPT_RECVTIMEO, m_revTimeout);
    stradex_ERROR_IF_RETURN(rv != 0, void(), "Failed set receive timeout option!");

    rv = -1;
    while (!m_stop && rv != 0) {
        rv = nng_dial(sock, ms_pubUrl, nullptr, 0);
        stradex_WARN_IF(
          rv != 0,
          "Faied nng_dial, will retry after 5 seconds! You Maybe need start the collection service "
          "first.");
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    stradex_INFO("Ready to receive ...");

    while (!m_stop) {
        char* buf = nullptr;
        size_t length = 0;
        try {
            rv = nng_recv(sock, &buf, &length, NNG_FLAG_ALLOC);
            if (!buf || length == 0) {
                continue;
            }
            stradex_CHECK(rv == 0 || rv == NNG_ETIMEDOUT, "Failed nng_recv! {} ", nng_strerror(rv));
            switch (m_status) {
                case WAITING:
                    if (memcmp(buf, ms_startTag, ms_startTagLength) == 0) {
                        ms_start_rev_time = Datetime::now();
                        m_status = RECEIVING;
                    }
                    break;
                case RECEIVING:
                    if (memcmp(buf, ms_endTag, ms_endTagLength) == 0) {
                        m_status = WAITING;
                        for (auto& task : m_process_task_list) {
                            task.get();
                        }
                        stradex_INFO_IF(m_print, "received count: {}", m_batch_count);
                        m_batch_count = 0;
                        // 执行后处理
                        for (auto& postProcess : m_postProcessList) {
                            postProcess(ms_start_rev_time);
                        }
                        m_process_task_list.clear();
                    } else {
                        stradex_CHECK(memcmp(buf, ms_startTag, ms_startTagLength) != 0,
                                  "Data not received in time, maybe the send speed is too fast!");
                        parseSpotData(buf, length);
                    }
                    break;
            }
        } catch (std::exception& e) {
            stradex_ERROR(e.what());
        } catch (...) {
            stradex_ERROR_UNKNOWN;
        }
        if (buf) {
            nng_free(buf, length);
        }
    }

    nng_close(sock);
}

void SpotAgent::addProcess(std::function<void(const SpotRecord&)> process) {
    stradex_CHECK(m_stop, "SpotAgent is running, please stop agent first!");
    m_processList.push_back(process);
}

void SpotAgent::addPostProcess(std::function<void(Datetime)> func) {
    stradex_CHECK(m_stop, "SpotAgent is running, please stop agent first!");
    m_postProcessList.push_back(func);
}

void SpotAgent::clearProcessList() {
    stradex_CHECK(m_stop, "SpotAgent is running, please stop agent first!");
    m_processList.clear();
}

void SpotAgent::clearPostProcessList() {
    stradex_CHECK(m_stop, "SpotAgent is running, please stop agent first!");
    m_postProcessList.clear();
}

}  // namespace stradex