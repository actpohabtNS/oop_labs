#include "doctest.h"

int sum(int a, int b) {
    return a+b;
}

TEST_CASE("testing the sum function") {
    CHECK(sum(1,1) == 2);
    CHECK(sum(2,2) == 4);
    CHECK(sum(0,0) == 0);
}
