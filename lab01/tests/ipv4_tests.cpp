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

            IPv4 ip2(1, 20);
            CHECK(ip2.QStr() == "1.20.0.0");
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

    SUBCASE("Operators") {
        CHECK(IPv4(1,2,1,0) < IPv4(1,2,3,4));
        CHECK(IPv4() <= IPv4(0,0,0));
        CHECK(IPv4(1,1,1,1) == IPv4(1,1,1,1));
        CHECK(IPv4(1,2,3,5) >= IPv4(1,2,3,4));
        CHECK(IPv4(1,2,3,5) > IPv4(1,2,3,4));
    }

    SUBCASE("Parsing") {
        CHECK(IPv4("").QStr() == "0.0.0.0");
        CHECK(IPv4("1.2f") == IPv4());
        CHECK(IPv4("1.2.3.4").QStr() == "1.2.3.4");
        CHECK(IPv4("1..22.3   44").QStr() == "1.22.3.44");
        CHECK(IPv4("1.2.3.4.5.6").QStr() == "1.2.3.4");
        CHECK(IPv4("1.400.3.4.5.6").QStr() == "1.0.0.0");
    }
}
