#include "PD_Automaton.h"
#include <fstream>
#include "toml++/toml.h"
#include <algorithm>
#include <memory>

using namespace std::string_view_literals;


PD_Automaton::PD_Automaton(const PD_Automaton& other) {}


PD_Automaton::~PD_Automaton() {
    delete[] transition_table;
}