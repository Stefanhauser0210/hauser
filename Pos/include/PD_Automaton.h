#pragma once

#include <string>
#include <vector>
#include <memory>
#include <stack>


class PD_Automaton {

    typedef struct Transition {
        std::string next_state;
        std::string write_back;
    } Transition;

    size_t transitionTableIndex(char current_state, char stack_token, char input_token);
    const std::shared_ptr<Transition>& getTransition(std::string current_state, char stack_token, char input_token) const;
    void transitionTo(const std::shared_ptr<Transition>);
    bool next(char);

    std::string title;
    std::vector<char> input_alphabet;
    std::vector<std::string> states;
    std::vector<std::string> accepted_states;
    std::vector<char> stack_alphabet;


    static PD_Automaton fromFile(const std::string& file);

    PD_Automaton(const PD_Automaton&);
    virtual ~PD_Automaton();

    std::unique_ptr<Transition>* transition_table;
    std::string current_state;
    std::stack<char> stack;

    static PD_Automaton load(std::string file);

    bool check(const std::string&);
    std::string getTitle() const noexcept;
};
