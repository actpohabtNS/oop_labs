#include "../src/Graph/MGraph.h"

#include "doctest.h"

TEST_CASE("MGraph") {
    SUBCASE("Creating with initializer list") {
        MGraph<int, int> mg({1,2,3,4,5});
        CHECK(mg.nodes() == 5);
    }

    MGraph<int, int> mg;

    SUBCASE("Creating empty") {
        CHECK(mg.nodes() == 0);
    }
}
