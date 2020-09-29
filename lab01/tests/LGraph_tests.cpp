#include "../src/Graph/LGraph.h"

#include "doctest.h"

TEST_CASE("LGraph") {
    LGraph<int, int> lg;

    SUBCASE("Adding Node") {
        lg.addNode(5);
        CHECK(lg.nodes() == 1);
    }

    SUBCASE("Creating with Initializer list") {
        LGraph<int, int> lg2({1,2,3,4,5});
        CHECK(lg2.nodes() == 5);
    }
}
