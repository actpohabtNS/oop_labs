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

    mg.addNode(1);
    mg.addNode(2);
    mg.addNode(3);

    SUBCASE("Edges") {
        SUBCASE("Adding edge") {
            mg.addEdge(1, 2, 12);
            CHECK(mg.edges() == 1);
        }

        mg.addEdge(1, 2, 12);

        SUBCASE("Edge exist") {
            CHECK(mg.edgeExist(1, 2) == true);
            CHECK(mg.edgeExist(2, 1) == true);
            CHECK(mg.edgeExist(1, 3) == false);
            CHECK(mg.edgeExist(1, 10) == false);
        }

        SUBCASE("Get edge") {
            CHECK(*mg.getEdge(1, 2) == 12);
            CHECK(*mg.getEdge(2, 1) == 12);
            CHECK(mg.getEdge(1, 3) == nullptr);
            CHECK(mg.getEdge(1, 10) == nullptr);
        }

//        SUBCASE("Erase edge") {
//            mg.eraseEdge(1, 3);
//            CHECK(mg.edges() == 1);
//            CHECK(mg.edgeExist(1,3) == false);

//            mg.eraseEdge(1,2);
//            CHECK(mg.edges() == 0);

//            mg.eraseEdge(1,2);
//            CHECK(mg.edges() == 0);
//        }

//        SUBCASE("Erase edges") {
//            qDebug() << "erase edges";
//            mg.eraseEdges();
//            CHECK(mg.edges() == 0);
//        }
    }

    mg.addEdge(1, 2, 12);

    SUBCASE("Connected") {                  // <- if comment this subcase - everything works
        qDebug() << "connected";
        mg.addEdge(1, 2, 12);               // though even when it is uncommented, it can work
        CHECK(mg.connected() == false);

        mg.addEdge(1, 3, 13);
        CHECK(mg.connected() == true);
    }

    mg.addEdge(1, 3, 13);

    mg.addNode(4);
    mg.addEdge(1, 4, 14);

    SUBCASE("Cyclic") {
        qDebug() << "cyclic";
        CHECK(mg.cyclic() == false);

        mg.addEdge(2, 4, 24);
        CHECK(mg.cyclic() == true);
    }

    SUBCASE("Distance") {
        qDebug() << "distance";
        mg.addNode(5);
        CHECK(mg.distance(1, 5) == -1);

        CHECK(mg.distance(1, 3) == 1);
        CHECK(mg.distance(2, 3) == 2);
        CHECK(mg.distance(2, 2) == 0);
    }
    qDebug() << "end";
}
