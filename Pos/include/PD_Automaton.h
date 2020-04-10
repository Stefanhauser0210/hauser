#include <string>
#include <vector>
#include <memory>
#include <stack>

#include "PD_Automaton.cpp"

class PD_Automaton {

    typedef struct Transition {
        std::string next_state;
        std::string write_back;
    } Transition;

    size_t transitionTableIndex(char current_state, char stack_token, char input_token);

    std::string title;
    std::vector<char> input_alphabet;
    std::vector<std::string> states;
    std::vector<std::string> accepted_states;
    std::vector<char> stack_alphabet;



    std::unique_ptr<Transition>* transition_table;
    std::string current_state;
    std::stack<char> stack;

    static PD_Automaton load(std::string file);
    bool next(char token);

};
