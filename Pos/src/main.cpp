#include <iostream>
#include <thread>
#include <vector>
#include <stack>

#include "PD_Automaton.h"
#include "toml++/toml.h"
#include "CLI11.hpp"
#include "spdlog/spdlog.h"
#include "Logger.h"

using namespace std;


int main(int argc, char* argv[]) {

    Logger::logger->set_level(spdlog::level::off);
    Logger::debug_logger->set_level(spdlog::level::off);

    CLI::App app("automata");

    string input{};
    app.add_option("INPUT", input, "The input")->required();
    
    string file{"./../automaton.toml"};
    app.add_option("-f, --file", file, "Automata file", true);

    bool debug{false};
    app.add_flag("-d", debug, "debug"); 

    bool verbose{false};
    app.add_flag("-v", verbose, "verbose");

    CLI11_PARSE(app, argc, argv);

    if (debug){
        Logger::debug_logger->set_level(spdlog::level::info);
    }

    if (verbose){
        Logger::logger->set_level(spdlog::level::info); 
    }

   Logger::logger->info("Parsing file {}", file);
   PD_Automaton automaton{PD_Automaton::load(file)};

    bool accepted{automaton.check(input)};

    if (accepted){
        cout << "accepted" << endl;
    } else {
        cout << "rejected" << endl;
    }

    Logger::logger->info("Input has been {}", accepted ? "accepted" : "rejected");
}