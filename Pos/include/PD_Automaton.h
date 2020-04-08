#include <string>
#include <vector>
#include <memory>
#include <stack>

#include "PD_Automaton.cpp"

class PD_Atomaton {

    typedef struct Transition {
        std::string next_state;
        std::string write_back;
    } Transition;

    size_t transitionTableIndex(char current_state, char stack_token, char input_token);

    std::string title;
    std::vector<std::string> input_alphabet;
    std::vector<std::string> states;
    std::vector<std::string> accepted_states;
    std::vector<std::string> stack_alphabet;



    std::unique_ptr<Transition>* transition_table;
    std::string current_state;
    std::stack<std::string> stack;

};
