#include <iostream>

#include <string>
#include <vector>
#include <future>

#include <zmq.hpp>

using namespace std;

const auto thread_num = 1;

zmq::context_t context(thread_num);

auto make_sock = [](auto mode)
{
    return zmq::socket_t(context, mode);
};
int main()
{
    const auto addr = "tcp://127.0.0.1:5555"s;

    auto client = [=](int i)
    {
        auto sock = make_sock(ZMQ_PUSH);

        sock.setsockopt(ZMQ_SNDHWM, 100);

        sock.connect(addr);
        assert(sock.connected());

        string s = "zmq msg " + to_string(i);
        //zmq::message_t msg(begin(s), end(s));
        //sock.send(msg);

        //sock.send(begin(s), end(s));
        auto len = sock.send(s.data(), s.size());
        cout << len << endl;
    };

    for (int i = 0; i < 4; i++) {
        client(i);
    }

    cout << "zmq client" << endl;
}
