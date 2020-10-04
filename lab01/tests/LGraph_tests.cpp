#include "../src/Graph/LGraph.h"

#include "doctest.h"

TEST_CASE("LGraph") {

    SUBCASE("Creating with Initializer list") {
        LGraph<int, int> lg({1,2,3,4,5});
        CHECK(lg.nodes() == 5);
    }

    LGraph<int, int> lg;

    SUBCASE("Creating empty") {
        CHECK(lg.nodes() == 0);
    }

    SUBCASE("Nodes") {
        SUBCASE("Adding node") {
            lg.addNode(1);
            CHECK(lg.nodes() == 1);
        }

        lg.addNode(1);
        lg.addNode(2);

        SUBCASE("Adding node with the same value") {
            lg.addNode(1);
            CHECK(lg.nodes() == 2);
        }

        SUBCASE("Node exist") {
            CHECK(lg.nodeExist(1) == true);
            CHECK(lg.nodeExist(10) == false);
        }
    }

    lg.addNode(1);
    lg.addNode(2);

    SUBCASE("Edges") {
        SUBCASE("Adding edge") {
            lg.addEdge(1, 2, 15);
            CHECK(lg.edges() == 1);
        }

        lg.addEdge(1, 2, 15);

        SUBCASE("Edge exist") {
            CHECK(lg.edgeExist(1, 2) == true);
            CHECK(lg.edgeExist(1, 10) == false);
        }
    }

}
