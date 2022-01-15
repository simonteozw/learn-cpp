#define CATCH_CONFIG_MAIN
#include "catch.hh"
#include <boost/smart_ptr/scoped_ptr.hpp>

struct DeadMenOfDunharrow {
    DeadMenOfDunharrow(const char* m = "") : message{ m } {
        oaths_to_fulfill++;
    }
    ~DeadMenOfDunharrow() {
        oaths_to_fulfill--;
    }

    const char* message;
    static int oaths_to_fulfill;
};

int DeadMenOfDunharrow::oaths_to_fulfill{};
using ScopedOathbreakers = boost::scoped_ptr<DeadMenOfDunharrow>;

TEST_CASE("ScopedPtr evaluates to") {
    SECTION("true when full") {
        ScopedOathbreakers aragorn{ new DeadMenOfDunharrow{} };
        REQUIRE(aragorn);
    }
    SECTION("false when empty") {
        ScopedOathbreakers aragorn;
        REQUIRE_FALSE(aragorn);
    }
}

TEST_CASE("ScopedPtr is an RAII (Resource Acquisition is Initialization) wrapper") {
    REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 0);
    ScopedOathbreakers aragorn{ new DeadMenOfDunharrow{} };
    REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1);
    {
        ScopedOathbreakers legolas{ new DeadMenOfDunharrow{} };
        REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 2);
    }
    REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1);
}

TEST_CASE("ScopedPtr supports pointer semantics, like") {
    auto message = "The way is shut";
    ScopedOathbreakers aragorn{ new DeadMenOfDunharrow{ message } };
    SECTION("operator*") {
        REQUIRE((*aragorn).message == message);
    }
    SECTION("operator->") {
        REQUIRE(aragorn->message == message);
    }
    SECTION("get(), which returns a raw pointer") {
        REQUIRE(aragorn.get() != nullptr);
    }
}

TEST_CASE("ScopedPtr supports comparison with nullptr") {
    SECTION("operator==") {
        ScopedOathbreakers legolas{};
        REQUIRE(legolas == nullptr);
    }
    SECTION("operator!=") {
        ScopedOathbreakers aragorn{ new DeadMenOfDunharrow{} };
        REQUIRE(aragorn != nullptr);
    }
}

TEST_CASE("ScopedPtr reset") {
    ScopedOathbreakers aragorn{ new DeadMenOfDunharrow{} };
    SECTION("destructs owned object.") {
        // if you provide no argument, reset simply destroys the owned object
        aragorn.reset();
        REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 0);
    }
    SECTION("can replace an owned object.") {
        auto message = "It was made by those who are Dead.";
        REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1);
        auto new_dead_men = new DeadMenOfDunharrow{ message };
        REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 2);
        // if you instead provide a new dynamic object as a parameter, reset will first destroy the currently owned object and then gain ownership of the parameter
        aragorn.reset(new_dead_men);
        REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1);
        REQUIRE(aragorn->message == new_dead_men->message);
        REQUIRE(aragorn.get() == new_dead_men);
    }
}
