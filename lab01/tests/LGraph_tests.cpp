#include "../src/Graph/LGraph.h"

#include "doctest.h"

TEST_CASE("LGraph") {
    LGraph<int, int> lg;
    lg.addNode(5);

    SUBCASE("Adding Nodes") {
        lg.addNode(2);
        CHECK(lg.nodes() == 2);
    }

    SUBCASE("Node exist") {
        CHECK(lg.nodeExist(5));
    }

    SUBCASE("Adding node with the same value") {
        lg.addNode(5);
        CHECK(lg.nodes() == 1);
    }

    SUBCASE("Creating with Initializer list") {
        LGraph<int, int> lg2({1,2,3,4,5});
        CHECK(lg2.nodes() == 5);
    }

    SUBCASE("Adding edge") {
        lg.addNode(1);

        lg.addEdge(1, 5, 15);

        lg.print();
    }
}
