#include "../src/Networks/ipv4.h"

#include "doctest.h"

#include <QString>

TEST_CASE("IPv4") {
    SUBCASE("Constructors") {
        SUBCASE("Zero constructor") {
            IPv4 ip;
            CHECK(ip.QStr() == "0.0.0.0");
        }
    }
}
