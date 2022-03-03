

#include "cpplang.hpp"
#include "Summary.hpp"
#include "Zmq.hpp"
#include "Config.hpp"

#include "json.hpp"

#include <cstdio>
#include <cpr/cpr.h>

USING_NAMESPACE(std);
USING_NAMESPACE(cpp_note);

static
auto debug_print = [](auto& b)
{
    using json_t = nlohmann::json;

    json_t j;

    j["id"] = b.id();
    j["sold"] = b.sold();
    j["revenue"] = b.revenue();

    std::cout << j.dump(2) << std::endl;
};

int main()
try
{
    cout << "hello zmq server" << endl;

    Config conf;
    conf.load("./conf.lua");
//    auto addr = conf.get<string>("config.zmq_ipc_addr");

    Summary sum;
    std::atomic_int count {0};

  //  cout << addr << endl;
    // todo: try-catch
    auto recv_cycle = [&]()
    {
        using zmq_ctx = ZmqContext<1>;

        auto sock = zmq_ctx::recv_sock();

        sock.bind(conf.get<string>("config.zmq_ipc_addr"));

        cout << conf.get<string>("config.zmq_ipc_addr") << endl;

        assert(sock.connected());

        cout << "server" << endl;
        for (;;) {

            auto msg_ptr = std::make_shared<zmq_message_type>();

            sock.recv(msg_ptr.get());

            ++count;
            cout << count << endl;

            std::thread([&sum, msg_ptr]()
            {
                SalesData book;

                auto handle = msgpack::unpack(
                            msg_ptr->data<char>(), msg_ptr->size());

                auto obj = handle.get();
                obj.convert(book);

                debug_print(book);

                sum.add_sales(book);
            }).detach();
        }
    };

    auto log_cycle = [&]()
    {
        auto http_addr = conf.get<string>("config.http_addr");
        auto time_interval = conf.get<int>("config.time_interval");

        for(;;) {
            std::this_thread::sleep_for(time_interval * 1s);

            using json_t = nlohmann::json;

            json_t j;

            j["count"] = static_cast<int>(count);
            j["minmax"] = sum.minmax_sales();

            auto res = cpr::Post(
                       cpr::Url{http_addr},
                       cpr::Header{{"Content-type", "text/plain"}},
                       cpr::Body{j.dump()},
                       cpr::Timeout{200ms}
                    );

            if (res.status_code != 200) {
                cerr << "http post failed: " << http_addr << endl;
            }
        }
    };

//    auto fu1 = std::async(std::launch::async, log_cycle);

    //auto fu2 = std::async(recv_cycle);
    auto fu2 = std::async(std::launch::async, recv_cycle);

    fu2.wait();
}
catch(std::exception& e)
{
    std::cerr << e.what() << std::endl;
}
