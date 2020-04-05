#include <iostream>
#include <thread>

#include "CLI11.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    CLI::App app("automata");

    vector<int> input{};
    app.add_option("INPUT", input, "The input")->required();
    

    string toml{"automaton.toml"};
    app.add_option("-f, --file", toml, "Automata file", true)->required();;

    bool debug{};
    app.add_flag("-d", debug, "debug"); 

    bool verbose{};
    app.add_flag("-v", verbose, "verbose");

    CLI11_PARSE(app, argc, argv);
}