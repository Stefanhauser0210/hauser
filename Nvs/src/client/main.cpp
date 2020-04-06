#include <iostream>
#include <thread>

#include "asio.hpp"
#include "CLI11.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    CLI::App app{"postfix client"};

    vector<string> input;
    app.add_option("INPUT", input, "input values");

    CLI11_PARSE(app, argc, argv);

    for (auto c : input){
        cout << c << endl;
    }

}