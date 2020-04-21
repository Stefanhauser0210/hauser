#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "PD_Automaton.h"
#include "toml++/toml.h"
#include "Logger.h"
#include "spdlog/spdlog.h"

using namespace std;

TEST_CASE("Automaton Page 45 - More 0 then 1: length 0 and 1"){
    Logger::logger->set_level(spdlog::level::off);
    Logger::debug_logger->set_level(spdlog::level::off);

    string file{"./../automaton.toml"};
    PD_Automaton automaton{PD_Automaton::load(file)};
    
    SUBCASE("length: 0 chars"){
        CHECK(!automaton.check(""));
    }

    SUBCASE("length: 0 chars - accepted"){
        CHECK(automaton.check("0"));
    }

    SUBCASE("length: 0 chars - rejected"){
        CHECK(!automaton.check("1"));
    }
}

TEST_CASE("Automaton Page 45 - More 0 then 1: length: 3"){
    Logger::logger->set_level(spdlog::level::off);
    Logger::debug_logger->set_level(spdlog::level::off);

    string file{"./../automaton.toml"};
    PD_Automaton automaton{PD_Automaton::load(file)};

    SUBCASE("length: 3 chars, begin:1, end:0 - accepted"){
        CHECK(automaton.check("100"));
    }

    SUBCASE("length: 3 chars, begin:0, end:1 - accepted"){
        CHECK(automaton.check("001"));
    }   

    SUBCASE("length: 3 chars, begin:0, end:0 - accepted"){
        CHECK(automaton.check("010"));
    }

    SUBCASE("length: 3 chars, begin:1, end:0 - rejected"){
        CHECK(!automaton.check("110"));
    }

    SUBCASE("length: 3 chars, begin:0, end:1 - rejected"){
        CHECK(!automaton.check("011"));
    }

    SUBCASE("length: 3 chars, begin:1, end:1 - rejected"){
        CHECK(!automaton.check("101"));
    }

    SUBCASE("length: 3 chars, only 0"){
        CHECK(automaton.check("000"));
    }

    SUBCASE("length: 3 chars, only 1"){
        CHECK(!automaton.check("111"));
    }  

}

TEST_CASE("Automaton Page 45 - More 0 then 1: length: 4"){
    Logger::logger->set_level(spdlog::level::off);
    Logger::debug_logger->set_level(spdlog::level::off);

    string file{"./../automaton.toml"};
    PD_Automaton automaton{PD_Automaton::load(file)};

    SUBCASE("length: 4 chars, begin:1, end:0 - accepted"){
        CHECK(automaton.check("1000"));
    }

    SUBCASE("length: 4 chars, begin:0, end:1 - accepted"){
        CHECK(automaton.check("0001"));
    }   

    SUBCASE("length: 4 chars, begin:0, end:0 - accepted"){
        CHECK(automaton.check("0100"));
    }

    SUBCASE("length: 4 chars, begin:1, end:0 - rejected"){
        CHECK(!automaton.check("1110"));
    }

    SUBCASE("length: 4 chars, begin:0, end:1 - rejected"){
        CHECK(!automaton.check("0111"));
    }

    SUBCASE("length: 4 chars, begin:1, end:1 - rejected"){
        CHECK(!automaton.check("1011"));
    } 

}

TEST_CASE("Automaton Page 45 - More 0 then 1: length: 5"){
    Logger::logger->set_level(spdlog::level::off);
    Logger::debug_logger->set_level(spdlog::level::off);

    string file{"./../automaton.toml"};
    PD_Automaton automaton{PD_Automaton::load(file)};
    
    SUBCASE("length: 5 chars, begin:1, end:0 - accepted"){
        CHECK(automaton.check("11000"));
    }

    SUBCASE("length: 5 chars, begin:0, end:1 - accepted"){
        CHECK(automaton.check("00011"));
    }

    SUBCASE("length: 5 chars, begin:0, end:0 - accepted"){
        CHECK(automaton.check("00110"));
    }

    SUBCASE("length: 5 chars, begin:1, end:1 - accepted"){
        CHECK(automaton.check("10001"));
    }
   
    SUBCASE("length: 5 chars, begin:1, end:0 - rejected"){
        CHECK(!automaton.check("11100"));
    }

    SUBCASE("length: 5 chars, begin:0, end:1 - rejected"){
        CHECK(!automaton.check("00111"));
    }

    SUBCASE("length: 5 chars, begin:0, end:0 - rejected"){
        CHECK(!automaton.check("01110"));
    }

    SUBCASE("length: 5 chars, begin:1, end:1 - rejected"){
        CHECK(!automaton.check("11001"));
    }      

}

TEST_CASE("Automaton Page 45 - More 0 then 1: same number of 0 and 1"){
    Logger::logger->set_level(spdlog::level::off);
    Logger::debug_logger->set_level(spdlog::level::off);

    string file{"./../automaton.toml"};
    PD_Automaton automaton{PD_Automaton::load(file)};
    
    SUBCASE("length: 2 chars, begin:1, end:0"){
        CHECK(!automaton.check("10"));
    }

    SUBCASE("length: 2 chars, begin:0, end:1"){
        CHECK(!automaton.check("01"));
    }

    SUBCASE("length: 4 chars, begin:0, end:1"){
        CHECK(!automaton.check("0101"));
    }

    SUBCASE("length: 4 chars, begin:1, end:0"){
        CHECK(!automaton.check("1100"));
    }

    SUBCASE("length: 4 chars, begin:0, end:0"){
        CHECK(!automaton.check("0110"));
    }

    SUBCASE("length: 4 chars, begin:1, end:1"){
        CHECK(!automaton.check("1001"));
    }

}

TEST_CASE("Automaton Page 45 - More 0 then 1: invalid char"){
    Logger::logger->set_level(spdlog::level::off);
    Logger::debug_logger->set_level(spdlog::level::off);

    string file{"./../automaton.toml"};
    PD_Automaton automaton{PD_Automaton::load(file)};
    
    SUBCASE("length: 1 chars"){
        CHECK(!automaton.check("a"));
    }

    SUBCASE("length: 5 chars, error at begin"){
        CHECK(!automaton.check("a0010"));
    }

    SUBCASE("length: 4 chars, error in the middle"){
        CHECK(!automaton.check("00a0"));
    }

    SUBCASE("length: 6 chars, error at the end"){
        CHECK(!automaton.check("10010a"));
    }

}



