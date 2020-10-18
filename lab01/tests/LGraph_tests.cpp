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
        lg.addNode(3);

        SUBCASE("Adding node with the same value") {
            lg.addNode(1);
            CHECK(lg.nodes() == 3);
        }

        SUBCASE("Node exist") {
            CHECK(lg.nodeExist(1) == true);
            CHECK(lg.nodeExist(10) == false);
        }

        SUBCASE("Erase node") {
           lg.eraseNode(3);
           CHECK(lg.nodes() == 2);

           lg.eraseNode(2);
           CHECK(lg.nodes() == 1);
           CHECK(lg.edges() == 0);
        }
    }

    lg.addNode(1);
    lg.addNode(2);
    lg.addNode(3);

    SUBCASE("Edges") {
        SUBCASE("Adding edge") {
            lg.addEdge(1, 2, 12);
            CHECK(lg.edges() == 1);
        }

        lg.addEdge(1, 2, 12);

        SUBCASE("Edge exist") {
            CHECK(lg.edgeExist(1, 2) == true);
            CHECK(lg.edgeExist(2, 1) == true);
            CHECK(lg.edgeExist(1, 3) == false);
            CHECK(lg.edgeExist(1, 10) == false);
        }

        SUBCASE("Get edge") {
            CHECK(*lg.getEdge(1, 2) == 12);
            CHECK(*lg.getEdge(2, 1) == 12);
            CHECK(lg.getEdge(1, 3) == nullptr);
            CHECK(lg.getEdge(1, 10) == nullptr);
        }

        SUBCASE("Erase edge") {
            lg.eraseEdge(1, 3);
            CHECK(lg.edges() == 1);

            lg.eraseEdge(1,2);
            CHECK(lg.edges() == 0);

            lg.eraseEdge(1,2);
            CHECK(lg.edges() == 0);
        }

        SUBCASE("Erase edges") {
            lg.eraseEdges();
            CHECK(lg.edges() == 0);
        }
    }


    lg.addEdge(1, 2, 12);

    SUBCASE("Connected") {
        lg.addEdge(1, 2, 12);
        CHECK(lg.connected() == false);

        lg.addEdge(1, 3, 13);
        CHECK(lg.connected() == true);
    }

    lg.addEdge(1, 2, 12);
    lg.addEdge(1, 3, 13);

    lg.addNode(4);
    lg.addEdge(1, 4, 14);

    SUBCASE("Cyclic") {
        CHECK(lg.cyclic() == false);

        lg.addEdge(2, 4, 24);
        CHECK(lg.cyclic() == true);
    }

    SUBCASE("Distance") {
        lg.addNode(5);
        CHECK(lg.distance(1, 5) == -1);

        CHECK(lg.distance(1, 3) == 1);
        CHECK(lg.distance(2, 3) == 2);
        CHECK(lg.distance(2, 2) == 0);
    }

    SUBCASE("TypeStr") {
        CHECK(lg.typeStr() == "LGraph");
    }
}
