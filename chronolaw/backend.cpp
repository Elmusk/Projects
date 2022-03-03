
#include <iostream>

#include <cinatra/cinatra.hpp>

using namespace std;
using namespace cinatra;

int main()
{
    cout << "http srv is running" << endl;

    http_server srv(1);

    srv.listen("0.0.0.0", "80");

    srv.set_not_found_handler(
        [](auto& req, auto& res) {
            res.set_status_and_content(
                status_type::forbidden, "code:403\n");
        });

    srv.set_http_handler<POST>(
        "/cpp_note",
        [](auto& req, auto& res) {
            auto token = req.get_query_value("token");

            std::cout << req.body() << std::endl;

            if (token != "cpp" || !req.has_body()) {
                res.set_status_and_content(
                    status_type::forbidden, "code:403\n");
                return;
            }

            cout << req.body() << endl;

            res.set_status_and_content(status_type::ok, "ok");
        });

    srv.run();
}

