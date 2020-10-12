#include "../src/Networks/ipv6.h"

#include "doctest.h"

#include <QString>
#include <QDebug>

TEST_CASE("IPv6") {
    SUBCASE("Constructors") {
        SUBCASE("Zero constructor") {
            IPv6 ip;
            CHECK(ip.QStr() == "0:0:0:0:0:0:0:0");
        }

        SUBCASE("List constructor") {
            IPv6 ip(1, 0xEE, 0xEE, 0xEE, 0xFE20);
            CHECK(ip.QStr() == "1:ee:ee:ee:fe20:0:0:0");

            IPv6 ip2(1, 0xEE);
            CHECK(ip2.QStr() == "1:ee:0:0:0:0:0:0");
        }

        SUBCASE("Initializer list constructor") {
            IPv6 ip({0xFEEE, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7});
            CHECK(ip.QStr() == "feee:1:2:3:4:5:6:7");

            IPv6 ip2({0xFEEE, 0xFEEE});
            CHECK(ip2.QStr() == "feee:feee:0:0:0:0:0:0");
        }
    }

    SUBCASE("Operators") {
        CHECK(IPv6(1,2,1,0) < IPv6(1,2,3,4));
        CHECK(IPv6() <= IPv6(0,0,0));
        CHECK(IPv6(1,1,1,1) == IPv6(1,1,1,1));
        CHECK(IPv6(1,2,3,5) >= IPv6(1,2,3,4));
        CHECK(IPv6(1,2,3,5) > IPv6(1,2,3,4));
    }
}
