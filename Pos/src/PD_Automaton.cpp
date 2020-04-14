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
        automaton.stack_.push(c);
    }

    
    auto table_node = config["table"];
    auto table = table_node.as_table();

    automaton.transition_table_ = new std::shared_ptr<Transition>[automaton.states.size() * automaton.stack_alphabet.size() * (automaton.input_alphabet.size() + 1)];

    auto transition_node = (*table)["transition"];
    auto transitions = transition_node.as_array();

    for (const auto& t : *transitions) {
        auto transition_table = t.as_table();

        auto z_node = (*transition_table)["z"];
        auto z = z_node.as_string()->get();

        auto transition_k0_node = (*transition_table)["k0"];
        auto transition_k0 = transition_k0_node.as_string()->get();

        auto e_node = (*transition_table)["e"];
        auto e = e_node.as_string()->get();

        auto z_new_node = (*transition_table)["z_new"];
        auto z_new = z_new_node.as_string()->get();

        auto k_new_node = (*transition_table)["k_new"];
        auto k_new = k_new_node.as_string()->get();

        auto transition_index{automaton.transitionTableIndex(z, transition_k0[0], e[0])};
        automaton.transition_table_[transition_index] = std::make_shared<Transition>(z_new, k_new);
        
    }

    return automaton;


}

size_t PD_Automaton::transitionTableIndex(std::string current_state, char stack_token, char input_token) const {
    auto state_index_it{std::find(states.begin(), states.end(), current_state)};
    auto state_index{std::distance(states.begin(), state_index_it)};

    auto stack_character_index_it{std::find(stack_alphabet.begin(), stack_alphabet.end(), stack_token)};
    auto stack_character_index{std::distance(stack_alphabet.begin(), stack_character_index_it)};

    auto input_character_index_it{std::find(input_alphabet.begin(), input_alphabet.end(), input_token)};
    auto input_character_index = std::distance(input_alphabet.begin(), input_character_index_it);

    size_t row{state_index * stack_alphabet.size() + stack_character_index};
    size_t index{row * (input_alphabet.size() + 1) + input_character_index};

    return index;
}

std::string PD_Automaton::getTitle() {
    return title;
}

const std::shared_ptr<PD_Automaton::Transition>& PD_Automaton::getTransition(std::string current_state, char stack_token, char input_token) const {
    return transition_table_[transitionTableIndex(current_state, stack_token, input_token)];
}

void PD_Automaton::transitionTo(const std::shared_ptr<Transition> transition) {
    current_state = transition->next_state;
    for (const auto& character : transition->write_back)
        PD_Automaton::stack_.push(character);
}

