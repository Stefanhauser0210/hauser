#include "PD_Automaton.h"
#include <fstream>
#include "toml++/toml.h"
#include <algorithm>
#include <memory>
#include <iostream>
#include "Logger.h"


using namespace std::string_view_literals;

PD_Automaton::PD_Automaton([[maybe_unused]] const PD_Automaton& other) {}


PD_Automaton::~PD_Automaton() {
    delete[] transition_table_;
}


PD_Automaton PD_Automaton::load(const std::string& file) {
    toml::table config = toml::parse_file(file);

    PD_Automaton automaton;

    Logger::debug_logger->info("Checking property 'title'");
    if (!config["title"]) throw std::runtime_error{"Property 'title' missing"};
    if (!config["title"].is_string()) throw std::runtime_error{"Property 'title' is not a string"};
    auto title = config["title"].as_string()->get();
    automaton.title = title;
    Logger::debug_logger->info("Property 'title' parsed successfully. Value: '{}'", automaton.title);

    Logger::debug_logger->info("Parsing definitions");
    auto definitions = config["definitions"];

    Logger::debug_logger->info("Checking property 'E' (input alphabet)");
    auto E_node = definitions["E"];
    if (!E_node) throw std::runtime_error{"Property 'definitions.E' missing"}; 
    if (!E_node.is_array()) throw std::runtime_error{"Property 'definitions.E' is not an array"};
    auto E = E_node.as_array();
    if (E->size() == 0) throw std::runtime_error{"Property 'definitions.E' is empty."};  
    for (const auto& node : *E) {
        auto input_character = node.as_string()->get();
        automaton.input_alphabet.push_back(input_character[0]);
    }
    Logger::debug_logger->info("Property 'E' (input alphabet) parsed successfully");

    Logger::debug_logger->info("Checking property 'K' (stack alphabet)");
    auto K_node = definitions["K"];
    if (!K_node) throw std::runtime_error{"Property 'definitions.K' missing"};
    if (!K_node.is_array()) throw std::runtime_error{"Property 'definitions.K' is not an array"};
    auto K = K_node.as_array();
    if (K->size() == 0) throw std::runtime_error{"Property 'definitions.K' is empty"};
    for (const auto& node : *K) {
        auto input_character = node.as_string()->get();
        automaton.stack_alphabet.push_back(input_character[0]);
    }
    Logger::debug_logger->info("Property 'K' (stack alphabet) parsed successfully");

    Logger::debug_logger->info("Checking property 'Z' (possible states)");   
    auto Z_node = definitions["Z"];
    if (!Z_node) throw std::runtime_error{"Property 'definitions.Z' missing"};
    if (!Z_node.is_array()) throw std::runtime_error{"Property 'definitions.Z' is not an array"};
    auto Z = Z_node.as_array();
    if (Z->size() == 0) throw std::runtime_error{"Property 'definitions.Z' is empty"};
    for (const auto& node : *Z) {
        auto state = node.as_string()->get();
        automaton.states.push_back(state);
    }
    Logger::debug_logger->info("Property 'Z' (possible states) parsed successfully");

    Logger::debug_logger->info("Checking property 'F' (accepted states)");
    auto F_node = definitions["F"];
    if (!F_node) throw std::runtime_error{"Property 'definitions.F' missing"};
    if (!F_node.is_array()) throw std::runtime_error{"Property 'definitions.F' is not an array"};
    auto F = F_node.as_array();
    if (F->size() == 0) throw std::runtime_error{"Property 'definitions.F' is empty"};
    for (const auto& node : *F) {
        auto accepted_state = node.as_string()->get();
        if (std::find(automaton.states.begin(), automaton.states.end(), accepted_state) == automaton.states.end()) 
            throw std::runtime_error{"Item of property 'definitions.F' is not a possible state"};   
        automaton.accepted_states.push_back(accepted_state);
    }
    Logger::debug_logger->info("Property 'F' (accepted states) parsed successfully");

    Logger::debug_logger->info("Checking property 'z0' (start state)");
    auto z0_node = definitions["z0"];
    if (!z0_node) throw std::runtime_error{"Property 'definitions.z0' missing"};
    if (!z0_node.is_string()) throw std::runtime_error{"Property 'definitions.z0' is not a string"};
    auto z0 = z0_node.as_string()->get();
    if (std::find(automaton.states.begin(), automaton.states.end(), z0) == automaton.states.end())  
        throw std::runtime_error{"Property 'definitions.z0' is not a possible state"};
    automaton.current_state = z0;
    Logger::debug_logger->info("Property 'z0' (start state) parsed successfully. Value: '{}'", z0);

    Logger::debug_logger->info("Checking property 'k0' (initial stack state)");
    auto k0_node = definitions["k0"];
    if (!k0_node) throw std::runtime_error{"Property 'definitions.k0' missing"};
    if (!k0_node.is_string()) throw std::runtime_error{"Property 'definitions.k0' is not a string"};
    auto k0 = k0_node.as_string()->get();
    for (const char& c : k0) {
        if (std::find(automaton.stack_alphabet.begin(), automaton.stack_alphabet.end(), c) == automaton.stack_alphabet.end())
            throw std::runtime_error{"Property 'definitions.k0' is not an allowed charakter of stack alphabet"};
        automaton.stack_.push(c);
    }
    Logger::debug_logger->info("Property 'k0' (initial stack state) parsed successfully. Value: '{}'", k0);  

    Logger::debug_logger->info("Definitions parsed successfully");
    Logger::debug_logger->info("Parsing transitions");


    auto table_node = config["table"];
    auto table = table_node.as_table();

    automaton.transition_table_ = new std::shared_ptr<Transition>[automaton.states.size() * automaton.stack_alphabet.size() * (automaton.input_alphabet.size() + 1)];

    Logger::debug_logger->info("Parsing property 'table.transition' (transition table)");
    auto transition_node = (*table)["transition"];
    auto transitions = transition_node.as_array();
    Logger::debug_logger->info("Start parsing entry of transition table");

    for (const auto& t : *transitions) {

        Logger::debug_logger->info("Parsing one property 'table.transition' (transition)");
        auto transition_table = t.as_table();

        Logger::debug_logger->info("Checking property 'table.transition.z' (current state)");
        auto z_node = (*transition_table)["z"];
        auto z = z_node.as_string()->get();
        Logger::debug_logger->info("Property 'table.transition.z' (current state) parsed successfully");

        Logger::debug_logger->info("Checking property 'table.transition.k0' (stack top)");
        auto transition_k0_node = (*transition_table)["k0"];
        auto transition_k0 = transition_k0_node.as_string()->get();
        Logger::debug_logger->info("Property 'table.transition.k0' (stack top) parsed successfully");

        Logger::debug_logger->info("Checking property 'table.transition.e' (input token)");
        auto e_node = (*transition_table)["e"];
        auto e = e_node.as_string()->get();
        Logger::debug_logger->info("Property 'table.transition.e' (input token) parsed successfully");        

        Logger::debug_logger->info("Checking property 'table.transition.z_new' (new state) ");
        auto z_new_node = (*transition_table)["z_new"];
        auto z_new = z_new_node.as_string()->get();
        Logger::debug_logger->info("Property 'table.transition.z_new' (new state) parsed successfully");

        Logger::debug_logger->info("Checking property 'table.transition.k_new' (new stack word)");
        auto k_new_node = (*transition_table)["k_new"];
        auto k_new = k_new_node.as_string()->get();
        Logger::debug_logger->info("Property 'table.transition.k_new' (new stack word) parsed successfully");

        Logger::debug_logger->info("Creating transition object and placing it into transition table");
        auto transition_index{automaton.transitionTableIndex(z, transition_k0[0], e[0])};
        automaton.transition_table_[transition_index] = std::make_shared<Transition>(z_new, k_new);
        
    }

        Logger::debug_logger->info("Parsing of transitios successfull");
        Logger::debug_logger->info("Parsing successfull");
   
    return automaton;


}

size_t PD_Automaton::transitionTableIndex(std::string current_state, char stack_token, char input_token) const {
    Logger::debug_logger->info("Calculating transition table index for: z = '{}', k0 = '{}', e = '{}'", current_state, stack_token, input_token);

    Logger::debug_logger->info("Getting index of z (current state) in list of states");
    auto state_index_it{std::find(states.begin(), states.end(), current_state)};
    auto state_index{std::distance(states.begin(), state_index_it)};
    Logger::debug_logger->info("Index of z (current state) in list of states is {}", state_index);

    Logger::debug_logger->info("Getting index of k (stack token) in stack alphabet");
    auto stack_character_index_it{std::find(stack_alphabet.begin(), stack_alphabet.end(), stack_token)};
    auto stack_character_index{std::distance(stack_alphabet.begin(), stack_character_index_it)};
    Logger::debug_logger->info("Index of k (stack token) in stack alphabet is {}", stack_character_index);

    Logger::debug_logger->info("Getting index of e (input token) in input alphabet");
    auto input_character_index_it{std::find(input_alphabet.begin(), input_alphabet.end(), input_token)};
    auto input_character_index = std::distance(input_alphabet.begin(), input_character_index_it);
    Logger::debug_logger->info("Index of e (input token) in input alphabet is {}", input_character_index);

    size_t row{state_index * stack_alphabet.size() + stack_character_index};
    size_t index{row * (input_alphabet.size() + 1) + input_character_index};

    Logger::debug_logger->info("Calculated index is {}", index);

    return index;
}

std::string PD_Automaton::getTitle() {
    return title;
}

const std::shared_ptr<PD_Automaton::Transition>& PD_Automaton::getTransition(std::string current_state, char stack_token, char input_token) const {
    return transition_table_[transitionTableIndex(current_state, stack_token, input_token)];
}

void PD_Automaton::transitionTo(const std::shared_ptr<Transition> transition) {
    Logger::debug_logger->info("Transitioning from {} -> {}, stack word: {}", current_state, transition->next_state, transition->write_back);
    current_state = transition->next_state;
    for (const auto& character : transition->write_back) {
        stack_.push(character);
    }
}

bool PD_Automaton::next(char token) {
    auto k0{stack_.top()};
    Logger::debug_logger->info("Getting transition for: e = '{}', z = '{}', k0 = '{}'", token, current_state, k0);
    auto transition = this->getTransition(current_state, k0, token);

    if (!transition) {
        Logger::debug_logger->info("No transition available, trying transition for: e = '', z = {}, k0 = {}", current_state, k0);
        transition = this->getTransition(current_state, k0, 0);  // 0 -> empty character

        if (!transition) {  
            Logger::debug_logger->info("No transition available", current_state, k0);
            return false;           
        }

        Logger::debug_logger->info("Transitioning to new state (0)");
        transitionTo(transition);

        return next(token);
    }

    stack_.pop();
    Logger::debug_logger->info("Transitioning to new state");
    transitionTo(transition);

    return true;
}

bool PD_Automaton::check(const std::string& word) {
    bool accepted{true};
    for (const auto& token : word) {
        Logger::debug_logger->info("Current state: {}", current_state);
        if (!(accepted = next(token)))
            break;
    }

    accepted = accepted && (std::find(accepted_states.begin(), accepted_states.end(), current_state) != accepted_states.end());

    return accepted;
}


