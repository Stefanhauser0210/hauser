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
    
    string file{"./../automaton.toml"};
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


    //toml-parsen Tests
    toml::table tab = toml::parse_file(file);

    cout << tab["title"] << endl;

    cout << tab["definitions"] << endl;

    auto definitions = tab["definitions"];
    cout << definitions << endl;

    auto z0 = definitions["z0"];
    cout << z0 << endl;

    auto e = definitions["E"];
    cout << e << endl;

    auto e_array = e.as_array();

    for (const auto& k : *e_array){
        cout << k.as_string()->get() << endl;
    }
}