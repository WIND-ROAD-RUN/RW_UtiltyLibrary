#include <boost/mysql.hpp>
#include <iostream>
#include"boost/asio.hpp"
 
int main() {
    try {
        boost::asio::io_context context;

        boost::mysql::tcp_connection conn(context);

        boost::asio::ip::tcp::endpoint ep(boost::asio::ip::make_address("127.0.0.1"), 3306);

        boost::mysql::handshake_params params(
            "zyf",
            "zyf",
            "RWChat"
        );

        //conn.connect(ep, params);
        std::cout << "Connect success";

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}