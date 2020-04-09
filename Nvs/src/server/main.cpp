#include <iostream>
#include <thread>
#include <chrono>
#include <stack>

#include "asio.hpp"
#include "CLI11.hpp"

using namespace std;
using namespace asio;
using namespace asio::ip;

void empty_stack(stack<int> &stk){
    while (!stk.empty()){
        stk.pop();
    }
}

int main() {
    try {
        stack<int> stk;

        int errcode{0};

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
                        } else {
                            errcode = 2;
                            break;
                        }
                    } else if (data == "-"){
                        if (stk.size() >= 2){
                            int op2 = stk.top();
                            stk.pop();
                            int op1 = stk.top();
                            stk.pop();
                            cout << op1 - op2 << endl;
                            stk.push(op1 - op2);
                        } else {
                            errcode = 2;
                            break;
                        }
                    } else if (data == "/"){
                        if (stk.size() >= 2){
                            int op2 = stk.top();
                            stk.pop();
                            int op1 = stk.top();
                            stk.pop();
                            if (op2 != 0){
                                cout << op1 / op2 << endl;
                                stk.push(op1 / op2);
                            } else {
                                errcode = 4;
                                break;
                            }
                        } else {
                            errcode = 2;
                            break;
                        }
                    } else if (data == "*"){
                        if (stk.size() >= 2){
                            int op2 = stk.top();
                            stk.pop();
                            int op1 = stk.top();
                            stk.pop();
                            cout << op1 * op2 << endl;
                            stk.push(op1 * op2);
                        } else {
                            errcode = 2;
                            break;
                        }
                    } else {
                        errcode = 1;
                        break;
                    }

                }

        if (stk.size() > 1){
            errcode = 3;
        }

        if (errcode == 0) {
            strm << stk.top() << endl;
            empty_stack(stk);
        } else {

            switch (errcode) {
                case 1:
                    strm << "ERROR: invalid character " << endl;
                    errcode = 0;
                    empty_stack(stk);
                    break;
                case 2:
                    strm << "ERROR: there are not enough operands on the stack" << endl;
                    errcode = 0;
                    empty_stack(stk);
                    break;
                case 3:
                    strm << "ERROR: there are more then one character left on the stack " << endl;
                    errcode = 0;
                    empty_stack(stk);
                    break;
                case 4:
                strm << "ERROR: division by zero " << endl;
                errcode = 0;
                empty_stack(stk);
                break;
            }
        }

            
        }

    } catch (...){
        cerr << "Error accured" << endl;
    }
}

