#include <iostream>
#include <thread>
#include <chrono>
#include <stack>

#include "asio.hpp"
#include "CLI11.hpp"

using namespace std;
using namespace asio;
using namespace asio::ip;

void empty_stack(stack<int> &stk)
{
    while (!stk.empty())
    {
        stk.pop();
    }
}

void calc(tcp::iostream strm)
{
    stack<int> stk;

    int errcode{0};
    size_t err_pos{0};
    char err_symbol{' '};

    string data{};
    getline(strm, data);

    auto i = stoi(data);

    for (int j{1}; j <= i; j++)
    {

        getline(strm, data);

        char *temp = new char[data.size() + 1];
        strcpy(temp, data.c_str());

        if (isdigit(temp[0]))
        {
            stk.push(stoi(data));
        }
        else if (data == "+")
        {
            if (stk.size() >= 2)
            {
                int op2 = stk.top();
                stk.pop();
                int op1 = stk.top();
                stk.pop();
                cout << op1 + op2 << endl;
                stk.push(op1 + op2);
            }
            else
            {
                err_pos = j;
                errcode = 2;
                break;
            }
        }
        else if (data == "-")
        {
            if (stk.size() >= 2)
            {
                int op2 = stk.top();
                stk.pop();
                int op1 = stk.top();
                stk.pop();
                cout << op1 - op2 << endl;
                stk.push(op1 - op2);
            }
            else
            {
                errcode = 2;
                err_pos = j;
                break;
            }
        }
        else if (data == "/")
        {
            if (stk.size() >= 2)
            {
                int op2 = stk.top();
                stk.pop();
                int op1 = stk.top();
                stk.pop();
                if (op2 != 0)
                {
                    cout << op1 / op2 << endl;
                    stk.push(op1 / op2);
                }
                else
                {
                    errcode = 4;
                    err_pos = j;
                    break;
                }
            }
            else
            {
                errcode = 2;
                err_pos = j;
                break;
            }
        }
        else if (data == "*")
        {
            if (stk.size() >= 2)
            {
                int op2 = stk.top();
                stk.pop();
                int op1 = stk.top();
                stk.pop();
                cout << op1 * op2 << endl;
                stk.push(op1 * op2);
            }
            else
            {
                errcode = 2;
                err_pos = j;
                break;
            }
        }
        else
        {
            errcode = 1;
            err_pos = j;
            err_symbol = temp[0];
            break;
        }
    }

    if (stk.size() > 1)
    {
        errcode = 3;
    }

    if (stk.empty() and errcode == 0)
    {
        errcode = 5;
    }

    if (errcode == 0)
    {
        strm << stk.top() << endl;
        empty_stack(stk);
    }
    else
    {

        switch (errcode)
        {
        case 1:
            strm << "ERROR: invalid character '" << err_symbol << "' at " << err_pos << endl;
            errcode = 0;
            empty_stack(stk);
            break;
        case 2:
            strm << "ERROR: there are not enough operands on the stack. Position: " << err_pos << endl;
            errcode = 0;
            empty_stack(stk);
            break;
        case 3:
            strm << "ERROR: there are more then one character left on the stack " << endl;
            errcode = 0;
            empty_stack(stk);
            break;
        case 4:
            strm << "ERROR: division by zero. Position: " << err_pos << endl;
            errcode = 0;
            empty_stack(stk);
            break;
        case 5:
            strm << "ERROR: stack is empty" << endl;
            errcode = 0;
            empty_stack(stk);
            break;
        }
    }
}

int main()
{
    try
    {

        asio::io_context ctx;
        tcp::endpoint ep{ip::address_v4::any(), 1113};
        tcp::acceptor acceptor{ctx, ep};

        acceptor.listen();

        while (true)
        {
            tcp::iostream strm{acceptor.accept()};
            std::thread t{calc, move(strm)};
            t.join();
        }
    }
    catch (...)
    {
        cerr << "ERROR: unable to start server " << endl;
    }
}
