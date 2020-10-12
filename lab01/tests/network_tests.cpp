#include "../src/Networks/network.h"
#include "../src/Networks/ipv4.h"
#include "../src/Networks/ipv6.h"

#include "doctest.h"

#include <QString>
#include <QDebug>

TEST_CASE("Network") {

    SUBCASE("Constructors") {

        SUBCASE("Empty constructor") {
            Network nt;
            CHECK(nt.QStr() == "0.0.0.0/32");
        }

        SUBCASE("Basic constructor") {
            IPv4 ipv4(1,2,3,4);
            Network nt1(&ipv4, 16);
            CHECK(nt1.QStr() == "1.2.3.4/16");

            std::shared_ptr<IPv4> ipv4_ptr(new IPv4(5,6,7,8));
            Network nt2(ipv4_ptr, 16);
            CHECK(nt2.QStr() == "5.6.7.8/16");

            IPv6 ipv6(10, 11, 12, 13, 14);
            Network nt3(&ipv6, 100);
            CHECK(nt3.QStr() == "10:11:12:13:14:0:0:0/100");

            std::shared_ptr<IPv6> ipv6_ptr(new IPv6(15, 16, 17, 18, 19));
            Network nt4(ipv6_ptr, 100);
            CHECK(nt4.QStr() == "15:16:17:18:19:0:0:0/100");
        }
    }
}
