#include "../src/Networks/ipv6.h"

#include "doctest.h"

#include <QString>

TEST_CASE("IPv6") {
    SUBCASE("Constructors") {
        SUBCASE("Zero constructor") {
            IPv6 ip;
            CHECK(ip.QStr() == "0:0:0:0:0:0:0:0");
        }
    }
}
