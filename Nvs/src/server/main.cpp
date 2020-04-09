#include <iostream>
#include <thread>
#include <chrono>
#include <stack>

#include "asio.hpp"
#include "CLI11.hpp"


using namespace std;
using namespace asio;
using namespace asio::ip;




int main() {
    try {
        stack<int> stk;

        asio::io_context ctx;
        tcp::endpoint ep{ip::address_v4::any(), 1113};
        tcp::acceptor acceptor {ctx, ep};

        acceptor.listen();

        while (true){
            tcp::iostream strm{acceptor.accept()};
                
                string data{};
                getline(strm, data);

                auto i = stoi(data);

                for (int j{1}; j <= i; j++){

                    getline(strm, data);

                    char *temp = new char[data.size() + 1];
                    strcpy(temp, data.c_str());

                    if (isdigit(temp[0])){
                        stk.push(stoi(data));
                    } else if (data == "+"){
                        if (stk.size() >= 2){
                            int op2 = stk.top();
                            stk.pop();
                            int op1 = stk.top();
                            stk.pop();
                            cout << op1 + op2 << endl;
                            stk.push(op1 + op2);
                        }
                    } else if (data == "-"){
                        if (stk.size() >= 2){
                            int op2 = stk.top();
                            stk.pop();
                            int op1 = stk.top();
                            stk.pop();
                            cout << op1 - op2 << endl;
                            stk.push(op1 - op2);
                        }
                    } else if (data == "/"){
                        if (stk.size() >= 2){
                            int op2 = stk.top();
                            stk.pop();
                            int op1 = stk.top();
                            stk.pop();
                            cout << op1 / op2 << endl;
                            stk.push(op1 / op2);
                        }
                    } else if (data == "*"){
                        if (stk.size() >= 2){
                            int op2 = stk.top();
                            stk.pop();
                            int op1 = stk.top();
                            stk.pop();
                            cout << op1 * op2 << endl;
                            stk.push(op1 * op2);
                        }
                    } else {
                        cout << "Fehler" << endl;
                    }

                }

                strm << "accepted" << endl;

            
        }

    } catch (...){
        cerr << "Error accured" << endl;
    }
}

