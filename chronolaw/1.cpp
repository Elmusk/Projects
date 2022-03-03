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

    auto srv = [=]()
    {
        auto sock = make_sock(ZMQ_PULL);

        sock.setsockopt(ZMQ_LINGER, 0);
        sock.setsockopt(ZMQ_RCVHWM, 1000);

        sock.bind(addr);
        assert(sock.connected());

        zmq::message_t msg;

        for(int i = 0; i < 4; i++) {
            sock.recv(&msg);

            string s = {msg.data<char>(), msg.size()};
            cout << s << endl;
        }
    };

    auto fu2 = std::async(srv);

    fu2.wait();
}

