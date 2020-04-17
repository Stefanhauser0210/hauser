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
    PD_Automaton automaton1{PD_Automaton::load(file)};
    PD_Automaton automaton2{PD_Automaton::load(file)};
    PD_Automaton automaton3{PD_Automaton::load(file)};
    PD_Automaton automaton4{PD_Automaton::load(file)};
    PD_Automaton automaton5{PD_Automaton::load(file)};
    PD_Automaton automaton6{PD_Automaton::load(file)};
    PD_Automaton automaton7{PD_Automaton::load(file)};
    PD_Automaton automaton8{PD_Automaton::load(file)};
    
    CHECK(automaton1.check("11000"));
    CHECK(automaton2.check("00011"));
    CHECK(automaton3.check("00110"));
    CHECK(automaton4.check("10001"));

    CHECK(!automaton5.check("00111"));
    CHECK(!automaton6.check("11100"));
    CHECK(!automaton7.check("11001"));
    CHECK(!automaton8.check("01110"));
}