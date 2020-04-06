#include <iostream>
#include <thread>
#include <chrono>

#include "asio.hpp"
#include "CLI11.hpp"


using namespace std;
using namespace asio;
using namespace asio::ip;

int main() {
    try {
        asio::io_context ctx;
        tcp::endpoint ep{ip::address_v4::any(), 1113};
        tcp::acceptor acceptor {ctx, ep};

        acceptor.listen();

        while (true){
            tcp::iostream strm{acceptor.accept()};
                
                cout << "accepted" << endl;
                string data{};
                getline(strm, data);
                cout << data << endl;
                getline(strm, data);
                cout << data << endl;
                getline(strm, data);
                cout << data << endl;

                strm << "accepted" << endl;

            
        }

    } catch (...){
        cerr << "Error accured" << endl;
    }
}

