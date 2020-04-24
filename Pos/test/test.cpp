#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "PD_Automaton.h"
#include "toml++/toml.h"
#include "Logger.h"
#include "spdlog/spdlog.h"

using namespace std;

TEST_CASE("Automaton page 45 - More 0 then 1: length 0 and 1"){
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

TEST_CASE("Automaton page 45 - More 0 then 1: length: 3"){
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

TEST_CASE("Automaton page 45 - More 0 then 1: length: 4"){
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

TEST_CASE("Automaton page 45 - More 0 then 1: length: 5"){
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

TEST_CASE("Automaton page 45 - More 0 then 1: same number of 0 and 1"){
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

TEST_CASE("Automaton page 45 - More 0 then 1: invalid char"){
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

TEST_CASE("Automaton page 50 - Input word mirrored: length 0 and 1"){
    Logger::logger->set_level(spdlog::level::off);
    Logger::debug_logger->set_level(spdlog::level::off);

    string file{"./../automaton2.toml"};
    PD_Automaton automaton{PD_Automaton::load(file)};

    SUBCASE("length: 0 chars"){
        CHECK(!automaton.check(""));
    }

    SUBCASE("length: 1, char: 0"){
        CHECK(!automaton.check("0"));
    }

    SUBCASE("length: 1, char: 1"){
        CHECK(!automaton.check("1"));
    }

    SUBCASE("length: 1, char: $ - accepted"){
        CHECK(automaton.check("$"));
    }

}

TEST_CASE("Automaton page 50 - Input word mirrored: length 3"){
    Logger::logger->set_level(spdlog::level::off);
    Logger::debug_logger->set_level(spdlog::level::off);

    string file{"./../automaton2.toml"};
    PD_Automaton automaton{PD_Automaton::load(file)};

    SUBCASE("length: 3, begin:1, end:1 - accepted"){
        CHECK(automaton.check("1$1"));
    }

    SUBCASE("length: 3, begin:0, end:0 - accepted"){
        CHECK(automaton.check("0$0"));
    }

    SUBCASE("length: 3, begin:0, end:1 - rejected"){
        CHECK(!automaton.check("0$1"));
    }

    SUBCASE("length: 3, begin:1, end:0 - rejected"){
        CHECK(!automaton.check("1$0"));
    }

}

TEST_CASE("Automaton page 50 - Input word mirrored: straight length (asymmetrical)"){
    Logger::logger->set_level(spdlog::level::off);
    Logger::debug_logger->set_level(spdlog::level::off);

    string file{"./../automaton2.toml"};
    PD_Automaton automaton{PD_Automaton::load(file)};

    SUBCASE("length: 4, left side length:2, right side length:1"){
        CHECK(!automaton.check("10$1"));
    }

    SUBCASE("length: 4, left side length:1, right side length:2"){
        CHECK(!automaton.check("1$11"));
    }

    SUBCASE("length: 6, left side length:3, right side length:2"){
        CHECK(!automaton.check("101$10"));
    }

    SUBCASE("length: 6, left side length:2, right side length:3"){
        CHECK(!automaton.check("01$010"));
    }

    SUBCASE("length: 6, left side length:4, right side length:1"){
        CHECK(!automaton.check("1011$1"));
    }

    SUBCASE("length: 6, left side length:1, right side length:4"){
        CHECK(!automaton.check("1$1011"));
    }

}

TEST_CASE("Automaton page 50 - Input word mirrored: odd length (symmetrical)"){
    Logger::logger->set_level(spdlog::level::off);
    Logger::debug_logger->set_level(spdlog::level::off);

    string file{"./../automaton2.toml"};
    PD_Automaton automaton{PD_Automaton::load(file)};

    SUBCASE("length: 5, left side length:2, right side length:2 : 10$01 - accepted"){
        CHECK(automaton.check("10$01"));
    }

    SUBCASE("length: 5, left side length:2, right side length:2 : 01$10 - accepted"){
        CHECK(automaton.check("01$10"));
    }

    SUBCASE("length: 5, left side length:2, right side length:2 : 11$11 - accepted"){
        CHECK(automaton.check("11$11"));
    }

    SUBCASE("length: 5, left side length:2, right side length:2 : 00$00 - accepted"){
        CHECK(automaton.check("00$00"));
    }

    SUBCASE("length: 5, left side length:2, right side length:2 : 01$01 - rejected"){
        CHECK(!automaton.check("01$01"));
    }

    SUBCASE("length: 5, left side length:2, right side length:2 : 10$10 - rejected"){
        CHECK(!automaton.check("10$10"));
    }

    SUBCASE("length: 7, left side length:3, right side length:3 : 010$010 - accepted"){
        CHECK(automaton.check("010$010"));
    }

    SUBCASE("length: 7, left side length:3, right side length:3 : 101$101- accepted"){
        CHECK(automaton.check("101$101"));
    }

    SUBCASE("length: 7, left side length:3, right side length:3 : 110$011- accepted"){
        CHECK(automaton.check("110$011"));
    }

    SUBCASE("length: 7, left side length:3, right side length:3 : 111$111- accepted"){
        CHECK(automaton.check("111$111"));
    }

    SUBCASE("length: 7, left side length:3, right side length:3 : 000$000- accepted"){
        CHECK(automaton.check("000$000"));
    }

    SUBCASE("length: 7, left side length:3, right side length:3 : 110$101- rejected"){
        CHECK(!automaton.check("110$101"));
    }

    SUBCASE("length: 7, left side length:3, right side length:3 : 110$011- rejected"){
        CHECK(!automaton.check("010$101"));
    }

}

TEST_CASE("Automaton page 50 - Input word mirrored: odd length (asymmetrical)"){
    Logger::logger->set_level(spdlog::level::off);
    Logger::debug_logger->set_level(spdlog::level::off);

    string file{"./../automaton2.toml"};
    PD_Automaton automaton{PD_Automaton::load(file)};

    SUBCASE("length: 7, left side length:2, right side length:4 : 10$0110"){
        CHECK(!automaton.check("10$0110"));
    }

    SUBCASE("length: 7, left side length:4, right side length:2 : 1001$10"){
        CHECK(!automaton.check("1001$10"));
    }
}

TEST_CASE("Automaton page 50 - Input word mirrored: errors"){
    Logger::logger->set_level(spdlog::level::off);
    Logger::debug_logger->set_level(spdlog::level::off);

    string file{"./../automaton2.toml"};
    PD_Automaton automaton{PD_Automaton::load(file)};

    SUBCASE("length: 5, unvalid char left"){
        CHECK(!automaton.check("1a$01"));
    }

    SUBCASE("length: 5, unvalid char right"){
        CHECK(!automaton.check("10$a1"));
    }

    SUBCASE("length: 5, unvalid char both sides"){
        CHECK(!automaton.check("1a$a1"));
    }

    SUBCASE("length: 4, missing $"){
        CHECK(!automaton.check("0110"));
    }
}

TEST_CASE("errors"){
    Logger::logger->set_level(spdlog::level::off);
    Logger::debug_logger->set_level(spdlog::level::off);

    CHECK_THROWS(PD_Automaton::load("no")); //test for file not found

}


