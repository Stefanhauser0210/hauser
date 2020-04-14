#pragma once

#include <string>
#include <vector>
#include <memory>
#include <stack>



class PD_Automaton {
public:
    typedef struct Transition {
        Transition(std::string next_state, std::string write_back) : next_state{next_state}, write_back{write_back} {}
        std::string next_state;
        std::string write_back;
    } Transition;
    
    PD_Automaton() = default;  

    size_t transitionTableIndex(std::string current_state, char stack_token, char input_token) const;
    const std::shared_ptr<Transition>& getTransition(std::string current_state, char stack_token, char input_token) const;
    void transitionTo(const std::shared_ptr<Transition>);
    bool next(char);

    std::string title;
    std::vector<char> input_alphabet;
    std::vector<std::string> states;
    std::vector<std::string> accepted_states;
    std::vector<char> stack_alphabet;

    std::shared_ptr<Transition>* transition_table_;
    std::string current_state;
    std::stack<char> stack;


    static PD_Automaton load(const std::string& file); 

    PD_Automaton(const PD_Automaton&); 
    virtual ~PD_Automaton();  

    bool check(const std::string&);
    std::string getTitle();

private:

};
