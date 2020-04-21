#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "PD_Automaton.h"
#include "toml++/toml.h"
#include "Logger.h"
#include "spdlog/spdlog.h"

using namespace std;


TEST_CASE("Automaton Page 45 - More 0 then 1"){
    Logger::logger->set_level(spdlog::level::off);
    Logger::debug_logger->set_level(spdlog::level::off);

    string file{"./../automaton.toml"};
    PD_Automaton automaton{PD_Automaton::load(file)};
    
    SUBCASE("Test dependency of begin and end of the word: begin:1, end:0 - accepted"){
        CHECK(automaton.check("11000"));
    }

    SUBCASE("Test dependency of begin and end of the word: begin:0, end:1 - accepted"){
        CHECK(automaton.check("00011"));
    }

    SUBCASE("Test dependency of begin and end of the word: begin:0, end:0 - accepted"){
        CHECK(automaton.check("00110"));
    }

    SUBCASE("Test dependency of begin and end of the word: begin:1, end:1 - accepted"){
        CHECK(automaton.check("10001"));
    }
   
    SUBCASE("Test dependency of begin and end of the word: begin:1, end:0 - rejected"){
        CHECK(!automaton.check("11100"));
    }

    SUBCASE("Test dependency of begin and end of the word: begin:0, end:1 - rejected"){
        CHECK(!automaton.check("00111"));
    }

    SUBCASE("Test dependency of begin and end of the word: begin:0, end:0 - rejected"){
        CHECK(!automaton.check("01110"));
    }

    SUBCASE("Test dependency of begin and end of the word: begin:1, end:1 - rejected"){
        CHECK(!automaton.check("11001"));
    }      

}