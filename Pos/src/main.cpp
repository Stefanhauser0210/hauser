#include <iostream>
#include <thread>
#include <vector>
#include <stack>


#include "toml++/toml.h"
#include "CLI11.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    CLI::App app("automata");

    string input{};
    app.add_option("INPUT", input, "The input")->required();
    
    string file{"automaton.toml"};
    app.add_option("-f, --file", file, "Automata file", true);

    bool debug{};
    app.add_flag("-d", debug, "debug"); 

    bool verbose{};
    app.add_flag("-v", verbose, "verbose");

    CLI11_PARSE(app, argc, argv);

    if (debug){
        cout << "d" << input << " " << file << endl;
    } else if (verbose) {
        cout << "v" << input << " " << file << endl;
    }

}