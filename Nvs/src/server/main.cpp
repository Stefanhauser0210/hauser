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
                
                string data{};
                getline(strm, data);

                auto i = stoi(data);

                for (int j{1}; j < i; j++){
                    getline(strm, data);
                    cout << data << endl;
                    cout << "j : " << j << endl;
                }

                cout << "fertig" << endl;
                strm << "accepted" << endl;

            
        }

    } catch (...){
        cerr << "Error accured" << endl;
    }
}

