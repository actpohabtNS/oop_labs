#ifndef LGRAPH_H
#define LGRAPH_H

#include "Graph.h"

#include <vector>
#include <unordered_map>

#include <QDebug>

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
        const NT* toNode;
        ET data;

        Edge() = default;
        explicit Edge(const NT* toNode, const ET data)
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
    std::unordered_map<NT, std::vector<Edge*>> _list;

    int _nodes;
    int _edges;
    bool _weighed;

public:

    ///
    /// \brief LGraph
    ///
    /// Basic constructor.
    LGraph();

    ///
    /// \brief LGraph
    /// \param list
    ///
    /// Used to create LGraph and add Nodes given in std::initializer_list.
    explicit LGraph(std::initializer_list<NT> list);

    ~LGraph() = default;

    void addNode(const NT& data) override;

    ///
    /// \brief nodeExist
    /// \param data
    /// \return bool
    ///
    /// Checks whether node with [ data ] is presented in LGraph.
    bool nodeExist(const NT& data) const override;

    ///
    /// \brief eraseNode
    /// \param data
    ///
    /// Erases node with data = [ data ] and all its edges.
    void eraseNode(const NT& data) override;


    ///
    /// \brief addEdge
    /// \param n1
    /// \param n2
    /// \param edgeData
    ///
    /// Adds an edge with [ edgeData ] between nodes [ n1 ] and [ n2 ].
    /// \note If either of nodes [ n1 ] or [ n2 ] does not exist, edge is not added.
    void addEdge(const NT& n1, const NT& n2, const ET& edgeData) override;


    ///
    /// \brief getEdge
    /// \param n1
    /// \param n2
    /// \return const EdgeType*
    ///
    /// Return pointer to data, contained in an egde, connecting nodes [ n1 ] and [ n2 ].
    /// \note If either of these nodes does not exist or the edge does not exist, null pointer is returned.
    const ET* getEdge(const NT& n1, const NT& n2) const;

    ///
    /// \brief edgeExist
    /// \param n1
    /// \param n2
    /// \return
    ///
    /// Checks whether an edge between nodes [ n1 ] and [ n2 ] exists.
    /// \note If either of nodes [ n1 ] or [ n2 ] does not exist, false is returned.
    bool edgeExist(const NT& n1, const NT& n2) const override;

    ///
    /// \brief eraseEdge
    /// \param n1
    /// \param n2
    ///
    /// Erase edge between nodes [ n1 ] and [ n2 ]
    /// \note If either of these nodes does not exist or the edge does not exist, nothing happens.
    void eraseEdge(const NT& n1, const NT& n2) override;

    ///
    /// \brief eraseEdges
    /// Erases all edges in graph.
    void eraseEdges() override;

    ///
    /// \brief print
    ///
    /// Prints graph to qDebug stream.
    void print() const;

    int nodes() const override;

    int edges() const override;

    bool empty() const override;

    bool weighed() const override;
};

#endif // LGRAPH_H



// -------------------------------------- CONSTRUCTOR, DESTRUCTOR --------------------------------------

template<typename NT, typename ET>
LGraph<NT, ET>::LGraph() : _nodes {0}, _edges {0}, _weighed {false} {}

template<typename NT, typename ET>
LGraph<NT, ET>::LGraph(std::initializer_list<NT> list)
    : _nodes {0}, _edges {0}, _weighed {false} {
    for (auto elem : list)
        this->addNode(elem);
}



// -------------------------------------- NODE METHODS --------------------------------------

template<typename NT, typename ET>
void LGraph<NT, ET>::addNode(const NT &data) {
    if (this->nodeExist(data))
        return;

    this->_nodes++;

    this->_list.emplace(std::make_pair(data, std::vector<Edge*>()));
}

template<typename NT, typename ET>
bool LGraph<NT, ET>::nodeExist(const NT &data) const {
    return this->_list.find(data) != this->_list.end();
}

template<typename NT, typename ET>
void LGraph<NT, ET>::eraseNode(const NT &data) {
    if (!this->nodeExist(data))
        return;

    for (auto& nodeEdges : this->_list) {
        for (std::size_t i = 0; nodeEdges.second.size(); i++) {
            if (*nodeEdges.second[i]->toNode == data) {
                nodeEdges.second.erase(nodeEdges.second.begin() + i);
                break;
            }
        }
    }

    this->_list.erase(data);

    this->_nodes--;
}



// -------------------------------------- EDGE METHODS --------------------------------------

template<typename NT, typename ET>
void LGraph<NT, ET>::addEdge(const NT &n1, const NT &n2, const ET &edgeData) {
    if (!this->nodeExist(n1) || !this->nodeExist(n2))
        return;

    this->_list[n1].emplace_back(new Edge(&this->_list.find(n2)->first, edgeData));
    this->_list[n2].emplace_back(new Edge(&this->_list.find(n1)->first, edgeData));

    this->_edges++;
}

template<typename NT, typename ET>
const ET *LGraph<NT, ET>::getEdge(const NT &n1, const NT &n2) const {
    if (!this->nodeExist(n1) || !this->nodeExist(n2))
        return nullptr;

    for (const auto* edge : this->_list.find(n1)->second) {
        if (edge->toNode == &this->_list.find(n2)->first)
            return &edge->data;
    }

    return nullptr;
}

///
/// \note In std::unordered_map find() used due to const_iterator version presense unlike in []. const_iterator is required here because method defined as const.
///
template<typename NT, typename ET>
bool LGraph<NT, ET>::edgeExist(const NT &n1, const NT &n2) const {
    if (!this->nodeExist(n1) || !this->nodeExist(n2))
        return false;

    for (const auto* edge : this->_list.find(n1)->second) {
        if (edge->toNode == &this->_list.find(n2)->first)
            return true;
    }

    return false;
}

template<typename NT, typename ET>
void LGraph<NT, ET>::eraseEdge(const NT &n1, const NT &n2) {
    if (!this->nodeExist(n1) || !this->nodeExist(n2))
        return;

    auto& n1Edges = this->_list[n1];

    bool edgeRemoved = false;

    for (std::size_t i = 0; i < n1Edges.size(); i++) {
        if (*n1Edges[i]->toNode == n2) {
            n1Edges.erase(n1Edges.begin() + i);
            edgeRemoved = true;
            break;
        }
    }

    if (!edgeRemoved)
        return;

    auto& n2Edges = this->_list[n2];

    for (std::size_t i = 0; i < n2Edges.size(); i++) {
        if (*n2Edges[i]->toNode == n1) {
            n2Edges.erase(n2Edges.begin() + i);
            break;
        }
    }

    this->_edges--;
}

template<typename NT, typename ET>
void LGraph<NT, ET>::eraseEdges() {
    for (auto& keyValue : this->_list)
        keyValue.second.clear();

    this->_edges = 0;
}



// -------------------------------------- TO OUTPUT FORMAT --------------------------------------

template<typename NT, typename ET>
void LGraph<NT, ET>::print() const {
    for (const auto& pair : this->_list) {
        qDebug() << pair.first << ": ";

        for (const auto& edge : pair.second)
            qDebug() << "to" << *edge->toNode << "( data:" << edge->data << ")";
    }
}



// -------------------------------------- GETTERS --------------------------------------

template<typename NT, typename ET>
int LGraph<NT, ET>::nodes() const {
    return this->_list.size();
}

template<typename NT, typename ET>
int LGraph<NT, ET>::edges() const {
    return this->_edges;
}

template<typename NT, typename ET>
bool LGraph<NT, ET>::empty() const {
    return this->_nodes == 0;
}

template<typename NT, typename ET>
bool LGraph<NT, ET>::weighed() const {
    return this->_weighed;
}
