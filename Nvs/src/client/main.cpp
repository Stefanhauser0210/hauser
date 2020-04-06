#include <iostream>
#include <thread>

#include "asio.hpp"
#include "CLI11.hpp"

using namespace std;
using namespace asio;
using namespace asio::ip;

int main(int argc, char* argv[]) {
    CLI::App app{"postfix client"};

    vector<string> input;
    app.add_option("INPUT", input, "input values");

    CLI11_PARSE(app, argc, argv);

    tcp::iostream strm("127.0.0.1", "1113");
    if (strm) {

        for (auto c : input){
            strm << c << endl;
            cout << c << endl;
        }

        string data;
        getline(strm, data);

        cout << data << endl;

        strm.close();
    } else {
        cerr << "Connection failed" << endl;
        cerr << strm.error().message() << endl;
    }

}