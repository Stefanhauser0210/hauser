#include <iostream>
#include <thread>
#include <chrono>
#include <stack>

#include "asio.hpp"
#include "CLI11.hpp"


using namespace std;
using namespace asio;
using namespace asio::ip;


stack<int> stk;

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

                cout << "länge " << i << endl;

                for (int j{1}; j <= i; j++){

                    getline(strm, data);

                    char *temp = new char[data.size() + 1];
                    strcpy(temp, data.c_str());

                    cout << "zeichen " << temp[0] << endl;

                    if (isdigit(temp[0])){
                        stk.push(stoi(data));
                    } else if (data == "+"){
                        cout << "zeichen erkannt +" << endl;
                    } else if (data == "-"){
                        cout << "zeichen erkannt -" << endl;
                    } else if (data == "/"){
                        cout << "zeichen erkannt /" << endl;
                    } else if (data == "X"){
                        cout << "zeichen erkannt *" << endl;
                    } else {
                        cout << "Fehler" << endl;
                    }

                }

                cout << "fertig" << endl;
                strm << "accepted" << endl;

            
        }

    } catch (...){
        cerr << "Error accured" << endl;
    }
}

