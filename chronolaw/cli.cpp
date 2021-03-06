

#include "cpplang.hpp"
#include "SalesData.hpp"
#include "Zmq.hpp"

#include "json.hpp"

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

static
auto make_sales = [](const auto& id, auto s, auto r)
{
    //return SalesData(id, s, r).pack();

#if 1
    SalesData book(id);

    book.inc_sold(s);
    book.inc_revenue(r);

    debug_print(book);

    auto buf = book.pack();
    cout << buf.size() << endl;

    return buf;
#endif
};

static
auto send_sales = [](const auto& addr, const auto& buf)
{
    using zmq_ctx = ZmqContext<1>;

    auto sock = zmq_ctx::send_sock();

    sock.connect(addr);
    assert(sock.connected());

    auto len = sock.send(buf.data(), buf.size());
    assert(len == buf.size());

    cout << "send len = " << len << endl;
};

int main()
try
{
    cout << "hello zmq client" << endl;
    auto buf = make_sales("001", 10, 100);
    //std::cout << buf.data() << std::endl;
    send_sales("tcp://127.0.0.1:5555"s, buf);

    std::this_thread::sleep_for(1000ms);

    send_sales("tcp://127.0.0.1:5555"s, make_sales("002", 20, 200));
}
catch(std::exception& e)
{
    std::cerr << e.what() << std::endl;
}
