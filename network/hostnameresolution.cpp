#include <iostream>
#include <boost/asio.hpp>
#include <string>

int main() {
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver{ io_context };
    boost::system::error_code ec;
    std::array<std::string, 3> arr = { "www.nostarch.com", "www.instagram.com", "www.linkedin.com" };

    for (const std::string& str : arr) {
        std::cout << str << std::endl;
        for (auto&& res : resolver.resolve(str, "http", ec)) {
            std::cout << res.service_name() << " "
                << res.host_name() << " "
                << res.endpoint() << std::endl;
        }
    }

    if (ec) std::cout << "Error code: " << ec << std::endl;
}