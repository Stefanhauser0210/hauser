#include "PD_Automaton.h"
#include <fstream>
#include "toml++/toml.h"
#include <algorithm>
#include <memory>
#include <iostream>

using namespace std::string_view_literals;

PD_Automaton::PD_Automaton([[maybe_unused]] const PD_Automaton& other) {}


PD_Automaton::~PD_Automaton() {
    delete[] transition_table;
}


PD_Automaton PD_Automaton::load(const std::string& file) {
    toml::table config = toml::parse_file(file);

    PD_Automaton automaton;

    auto title = config["title"].as_string()->get();
    automaton.title = title;

    auto definitions = config["definitions"];

    auto E_node = definitions["E"];
    auto E = E_node.as_array(); 
    for (const auto& node : *E) {
        auto input_character = node.as_string()->get();
        automaton.input_alphabet.push_back(input_character[0]);
    }

    auto K_node = definitions["K"];
    auto K = K_node.as_array();
    for (const auto& node : *K) {
        auto input_character = node.as_string()->get();
        automaton.stack_alphabet.push_back(input_character[0]);
    }

    auto Z_node = definitions["Z"];
    auto Z = Z_node.as_array();
    for (const auto& node : *Z) {
        auto state = node.as_string()->get();
        automaton.states.push_back(state);
    }

    auto F_node = definitions["F"];
    auto F = F_node.as_array();
    for (const auto& node : *F) {
        auto accepted_state = node.as_string()->get();   
        automaton.accepted_states.push_back(accepted_state);
    }

    auto z0_node = definitions["z0"];
    auto z0 = z0_node.as_string()->get();
    automaton.current_state = z0;

    auto k0_node = definitions["k0"];
    auto k0 = k0_node.as_string()->get();
    for (const char& c : k0) {
        automaton.stack.push(c);
    }

    return automaton;


}
