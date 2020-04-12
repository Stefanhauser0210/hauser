#pragma once

#include <string>
#include <vector>
#include <memory>
#include <stack>



class PD_Automaton {
private:
    typedef struct Transition {
        Transition(std::string next_state, std::string write_back) : next_state_{next_state}, write_back_{write_back} {}
        std::string next_state_;
        std::string write_back_;
    } Transition;
    
    PD_Automaton() = default;  

    size_t transitionTableIndex(std::string current_state, char stack_token, char input_token) const;
    const std::shared_ptr<Transition>& getTransition(std::string current_state, char stack_token, char input_token) const;
    void transitionTo(const std::shared_ptr<Transition>);
    bool next(char);

    std::string title_;
    std::vector<char> input_alphabet_;
    std::vector<std::string> states_;
    std::vector<std::string> accepted_states_;
    std::vector<char> stack_alphabet_;

    std::shared_ptr<Transition>* transition_table_;
    std::string current_state_;
    std::stack<char> stack_;

public:
    static PD_Automaton load(const std::string& file); 

    PD_Automaton(const PD_Automaton&); 
    virtual ~PD_Automaton();  

    bool check(const std::string&);
    std::string getTitle() const noexcept;
};
