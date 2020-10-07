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

    SUBCASE("Nodes") {
        SUBCASE("Adding node") {
            mg.addNode(1);
            CHECK(mg.nodes() == 1);
        }

        mg.addNode(1);
        mg.addNode(2);
        mg.addNode(3);

        SUBCASE("Adding node with the same value") {
            mg.addNode(1);
            CHECK(mg.nodes() == 3);
        }

        SUBCASE("Node exist") {
            CHECK(mg.nodeExist(1) == true);
            CHECK(mg.nodeExist(10) == false);
        }

        SUBCASE("Erase node") {
           mg.eraseNode(3);
           CHECK(mg.nodes() == 2);

           mg.eraseNode(2);
           CHECK(mg.nodes() == 1);
           CHECK(mg.edges() == 0);
        }
    }
}
