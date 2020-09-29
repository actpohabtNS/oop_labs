#ifndef LGRAPH_H
#define LGRAPH_H

#include "Graph.h"

#include <vector>
#include <unordered_map>

///
///\brief Adjacent list graph class
///
///Graph implemented using lists of nodes adjacent to each node.
///Consumes O(|N| + |E|) space, where |N| - number of nodes, |E| - number of edges.
template <typename NT, typename ET>
class LGraph : public Graph<NT, ET> {
private:

    ///
    /// \brief The LGraph Edge struct
    ///
    /// The Edge struct is used to implement a connection between two Nodes.
    struct Edge {
        NT* toNode;
        ET* data;

        Edge() = default;
        explicit Edge(const NT* toNode, const ET* data = nullptr)
            : toNode {toNode}, data {data} {};

        ~Edge() {
            delete toNode;
            delete data;
        }
    };

    ///
    /// \brief _list
    ///
    ///  _list represents Adjacency list of LGraph.
    /// std::unordered_map is used instead of std::map because keeping order is not needed.
    std::unordered_map<const NT*, std::vector<Edge*>> _list;

    int _nodes;
    int _edges;
    bool _weighed;

public:

    ///
    /// \brief LGraph
    ///
    /// Basic constructor.
    LGraph() : _nodes {0}, _edges {0}, _weighed {false} {};

    ///
    /// \brief LGraph
    /// \param list
    ///
    /// Used to create LGraph and add Nodes given in std::initializer_list.
    explicit LGraph(std::initializer_list<NT> list)
        : _nodes {0}, _edges {0}, _weighed {false} {
        for (auto elem : list)
            this->addNode(elem);
    }

    ~LGraph() = default;

    void addNode(const NT& data) override {
        this->_nodes++;

        this->_list.emplace(std::make_pair(&data, std::vector<Edge*>()));
    }

    int nodes() const override {
        return this->_nodes;
    }

    int edges() const override {
        return this->_edges;
    }

    bool empty() const override {
        return this->_nodes == 0;
    }

    bool weighed() const override {
        return this->_weighed;
    }
};

#endif // LGRAPH_H
