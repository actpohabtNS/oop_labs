#include "../src/Networks/ipv4.h"

#include "doctest.h"

#include <QString>

TEST_CASE("IPv4") {
    SUBCASE("Constructors") {
        SUBCASE("Zero constructor") {
            IPv4 ip;
            CHECK(ip.QStr() == "0.0.0.0");
        }

        SUBCASE("List constructor") {
            IPv4 ip(1, 20, 33, 45);
            CHECK(ip.QStr() == "1.20.33.45");

            IPv4 ip2(1, 20, 33);
            CHECK(ip2.QStr() == "1.20.33.0");
        }

        SUBCASE("Initializer list constructor") {
            IPv4 ip({1, 20, 33, 45});
            CHECK(ip.QStr() == "1.20.33.45");

            IPv4 ip2({1, 20});
            CHECK(ip2.QStr() == "1.20.0.0");

            IPv4 ip3({1, 20, 33, 45, 55, 65});
            CHECK(ip3.QStr() == "1.20.33.45");
        }
    }
}
