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

TEST_CASE("WeakPtr lock() yields") {
    auto message = "The way is shut";
    SECTION("a shared pointer when tracked object is alive") {
        auto aragorn = std::make_shared<DeadMenOfDunharrow>(message);
        std::weak_ptr<DeadMenOfDunharrow> legolas{ aragorn };
        // lock method always creates a shared pointer
        auto sh_ptr = legolas.lock();
        REQUIRE(sh_ptr->message == message);
        REQUIRE(sh_ptr.use_count() == 2);
    }
    SECTION("empty when shared pointer empty") {
        std::weak_ptr<DeadMenOfDunharrow> legolas;
        {
            auto aragorn = std::make_shared<DeadMenOfDunharrow>(message);
            legolas = aragorn;
        }
        // lock method always creates a shared pointer
        auto sh_ptr = legolas.lock();
        REQUIRE(nullptr == sh_ptr);
    }
}