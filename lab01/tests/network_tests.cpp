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

            sh_ptr_ip ipv4_ptr(new IPv4(5,6,7,8));
            Network nt2(ipv4_ptr, 16);
            CHECK(nt2.QStr() == "5.6.7.8/16");

            sh_ptr_ip ipv6_ptr(new IPv6(15, 16, 17, 18, 19));
            Network nt4(ipv6_ptr, 100);
            CHECK(nt4.QStr() == "15:16:17:18:19:0:0:0/100");
        }
    }

    SUBCASE("Set mask") {
        sh_ptr_ip ipv4(new IPv4(1,2,3,4));
        Network nt1(ipv4, 16);
        nt1.setMask(20);
        CHECK(nt1.QStr() == "1.2.3.4/20");

        sh_ptr_ip ipv6(new IPv6(10, 11, 12, 13, 14));
        Network nt3(ipv6, 100);
        nt3.setMask(138);
        CHECK(nt3.QStr() == "10:11:12:13:14:0:0:0/10");
    }

    SUBCASE("Min and max | IPv4") {
        sh_ptr_ip ipv4(new IPv4(1,2,3,4));
        Network nt1(ipv4, 16);

        CHECK(nt1.min()->QStr() == "1.2.0.0");
        CHECK(nt1.max()->QStr() == "1.2.255.255");

        sh_ptr_ip ipv4_2(new IPv4(1,2,30,4));
        Network nt2(ipv4_2, 21);
        CHECK(nt2.min()->QStr() == "1.2.24.0");
        CHECK(nt2.max()->QStr() == "1.2.31.255");
    }

    SUBCASE("Min and max | IPv6") {
        sh_ptr_ip ipv6(new IPv6(0x15, 0x16, 0x17, 0x18, 0x211));
        Network nt1(ipv6, 64);

        CHECK(nt1.min()->QStr(16) == "15:16:17:18:0:0:0:0");
        CHECK(nt1.max()->QStr(16) == "15:16:17:18:ffff:ffff:ffff:ffff");

        sh_ptr_ip ipv6_1(new IPv6(0x15, 0x16, 0x17, 0x18, 211));
        Network nt2(ipv6_1, 74);

        CHECK(nt2.min()->QStr(16) == "15:16:17:18:c0:0:0:0");
        CHECK(nt2.max()->QStr(16) == "15:16:17:18:ff:ffff:ffff:ffff");
    }
}
