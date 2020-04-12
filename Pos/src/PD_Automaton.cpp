#include "PD_Automaton.h"
#include <fstream>
#include "toml++/toml.h"
#include <algorithm>
#include <memory>
#include <iostream>

using namespace std::string_view_literals;

PD_Automaton::PD_Automaton([[maybe_unused]] const PD_Automaton& other) {}


PD_Automaton::~PD_Automaton() {
    delete[] transition_table_;
}


PD_Automaton PD_Automaton::load(const std::string& file) {
    toml::table config = toml::parse_file(file);
    std::cout << config;

    PD_Automaton automaton;
    return automaton;
}
