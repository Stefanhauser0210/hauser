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

    CHECK(automaton.check("11000"));
    CHECK(automaton.check("00011"));
    CHECK(automaton.check("00110"));
    CHECK(automaton.check("10001"));

    CHECK(!automaton.check("00111"));
    CHECK(!automaton.check("11100"));
    CHECK(!automaton.check("11001"));
    CHECK(!automaton.check("01110"));
}