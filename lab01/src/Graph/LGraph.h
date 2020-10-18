#ifndef LGRAPH_H
#define LGRAPH_H

#include "Graph.h"

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>

#include <QDebug>

///
///\brief Adjacent list graph class
///
///LGraph implemented using lists of nodes adjacent to each node.
///Consumes O(|N| + |E|) space, where |N| - number of nodes, |E| - number of edges.
///
template <typename NT, typename ET>
class LGraph : public Graph<NT, ET> {
private:

    ///
    /// \brief The LGraph Edge struct
    ///
    /// The Edge struct is used to implement a connection between two Nodes.
    ///
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
    /// \brief _list represents Adjacency list of LGraph.
    ///
    /// std::unordered_map is used instead of std::map because keeping order is not needed.
    ///
    mutable std::unordered_map<NT, std::vector<Edge*>> _list;

    int _nodes;
    int _edges;

    ///
    /// \brief Depth First Search
    /// \param snode Pointer to starting node
    /// \param visited Pointer to set containing visited nodes
    ///
    /// An internal implementation of Depth First Search to be widely use in LGraph methods.
    ///
    void _dfs(const NT& snode, std::unordered_set<const NT*>* visited) const;

    ///
    /// \brief Breadth First Search
    /// \param snode Pointer to starting node
    /// \param visited Pointer to set containing visited nodes
    ///
    /// An internal implementation of node - distances to other nodes using Breadth First Search to be widely use in LGraph methods.
    ///
    [[nodiscard]] std::unordered_map<const NT*, int> _bfsDistances(const NT* snode) const;

public:

    ///
    /// \brief Basic constructor.
    ///
    LGraph();

    ///
    /// \brief Constructor using initializer_list of nodes.
    /// \param list Initializer_list of nodes
    ///
    /// Used to create LGraph and add Nodes given in std::initializer_list.
    ///
    explicit LGraph(std::initializer_list<NT> list);

    ~LGraph() = default;

    ///
    /// \brief Add a node
    /// \param data Data to be added as node
    ///
    /// Adds a node with [ data ] to LGraph.
    ///
    void addNode(const NT& data) override;

    ///
    /// \brief Checks if node exist
    /// \param data Data to be searched
    /// \return bool Whether node with [ data ] exists
    ///
    /// Checks whether node with [ data ] is presented in LGraph.
    ///
    bool nodeExist(const NT& data) const override;

    ///
    /// \brief Erase node
    /// \param data Node with [ data ] to be erased
    ///
    /// Erases node with data = [ data ] and all its edges.
    ///
    void eraseNode(const NT& data) override;


    ///
    /// \brief Add an edge
    /// \param n1 Node 1 data ref
    /// \param n2 Node 2 data ref
    /// \param edgeData Data to be stored in an edge
    ///
    /// Adds an edge with [ edgeData ] between nodes [ n1 ] and [ n2 ].
    ///
    /// \note If either of nodes [ n1 ] or [ n2 ] does not exist, edge is not added.
    ///
    void addEdge(const NT& n1, const NT& n2, const ET& edgeData) override;

    ///
    /// \brief Get edge data
    /// \param n1 Node 1 data ref
    /// \param n2 Node 2 data ref
    /// \return const ET* Pointer to data stored in an edge
    ///
    /// Return pointer to data, contained in an egde, connecting nodes [ n1 ] and [ n2 ].
    /// \note If either of these nodes does not exist or the edge does not exist, null pointer is returned.
    ///
    const ET* getEdge(const NT& n1, const NT& n2) const;

    ///
    /// \brief Check if an edge exist
    /// \param n1 Node 1 data ref
    /// \param n2 Node 2 data ref
    /// \return bool Whether an edge exist
    ///
    /// Checks whether an edge between nodes [ n1 ] and [ n2 ] exists.
    ///
    /// \note If either of nodes [ n1 ] or [ n2 ] does not exist, false is returned.
    ///
    bool edgeExist(const NT& n1, const NT& n2) const override;

    ///
    /// \brief Delete an edge
    /// \param n1 Node 1 data ref
    /// \param n2 Node 2 data ref
    ///
    /// Erase edge between nodes [ n1 ] and [ n2 ]
    ///
    /// \note If either of these nodes does not exist or the edge does not exist, nothing happens.
    ///
    void eraseEdge(const NT& n1, const NT& n2) override;

    ///
    /// \brief Delete all adges
    ///
    /// Erases all edges in graph.
    ///
    void eraseEdges() override;


    ///
    /// \brief Deep First Search
    /// \param snode Pointer to starting node
    /// \param visited Pointer to set storing visited nodes
    ///
    /// Does Deep First Search, adding visited nodes to [ visited ].
    ///
    void dfs(const NT& snode, std::unordered_set<const NT*>* visited) const;

    ///
    /// \brief Is connected
    /// \return bool If graph is connected
    ///
    /// Checks whether graph is connected (any node can be reached from any other one).
    ///
    bool connected() const override;

    ///
    /// \brief Is cyclic
    /// \return bool If graph is cyclic
    ///
    /// Checks whether graph has cycles.
    ///
    bool cyclic() const override;

    ///
    /// \brief Get distance between 2 nodes
    /// \param n1 Node 1 data ref
    /// \param n2 Node 2 data ref
    /// \return int Number if edges
    ///
    /// Returns distance between nodes [ n1 ] and [ n2 ].
    ///
    /// \note If either of nodes are not in graph or they are not connecred, -1 is returned.
    ///
    [[nodiscard]] int distance(const NT& n1, const NT& n2) const override;


    ///
    /// \brief print
    ///
    /// Prints graph to qDebug stream.
    ///
    void print() const;

    ///
    /// \brief typeStr
    /// \return QString - Graph type in QString
    ///
    QString typeStr() const override;

    int nodes() const override;

    int edges() const override;

    bool empty() const override;
};

#endif // LGRAPH_H



// -------------------------------------- INTERNAL METHODS --------------------------------------

template<typename NT, typename ET>
void LGraph<NT, ET>::_dfs(const NT &snode, std::unordered_set<const NT *> *visited) const {
    if (visited->count(&snode))
            return;

    std::stack<const NT*> nodes;
    nodes.push(&snode);
    visited->insert(&snode);

    while (!nodes.empty()) {
        const NT* current = nodes.top();
        nodes.pop();

        for (const auto* edge : this->_list.find(*current)->second)
            if (!visited->count(edge->toNode)) {
                nodes.push(edge->toNode);
                visited->insert(edge->toNode);
            }
    }
}

template<typename NT, typename ET>
std::unordered_map<const NT *, int> LGraph<NT, ET>::_bfsDistances(const NT *snode) const {
    std::unordered_set<const NT*> visited;
    std::unordered_map<const NT*, int> distances;

    std::queue<const NT*> queue;
    queue.push(snode);

    visited.insert(snode);
    distances[snode] = 0;

    while (!queue.empty()) {
        const NT* curr = queue.front();
        queue.pop();

        for (const auto* edge : this->_list[*curr]) {
            if (visited.count(edge->toNode) == 1)
                continue;

            distances[edge->toNode] = distances[curr] + 1;
            visited.insert(edge->toNode);
            queue.push(edge->toNode);
        }
    }

    return distances;
}



// -------------------------------------- CONSTRUCTOR, DESTRUCTOR --------------------------------------

template<typename NT, typename ET>
LGraph<NT, ET>::LGraph() : _nodes {0}, _edges {0}{}

template<typename NT, typename ET>
LGraph<NT, ET>::LGraph(std::initializer_list<NT> list)
    : _nodes {0}, _edges {0} {
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



// -------------------------------------- GRAPH PROPERTIES METHODS --------------------------------------

template<typename NT, typename ET>
void LGraph<NT, ET>::dfs(const NT &snode, std::unordered_set<const NT *> *visited) const {
    this->_dfs(snode, visited);
}

template<typename NT, typename ET>
bool LGraph<NT, ET>::connected() const {
    if (this->empty())
        return true;

    std::unordered_set<const NT*> visited;
    this->dfs(this->_list.begin()->first, &visited);

    if (this->_list.size() != visited.size())
        return false;

    return true;
}

///
/// \note White, grey, black (coloring) algorithm is used. Instead of numbers, two unordered_sets are used.
///
template<typename NT, typename ET>
bool LGraph<NT, ET>::cyclic() const {
    std::unordered_set<const NT*> vis_black;
    std::unordered_set<const NT*> vis_grey;

        std::function<bool(const NT*, const NT*)> _dfs = [&](const NT* snode, const NT* parent) {
            vis_grey.insert(snode);

            for (const auto* edge : this->_list[*snode]) {
               if (vis_black.find(edge->toNode) == vis_black.end() && vis_grey.find(edge->toNode) == vis_grey.end()) {
                    if (_dfs(edge->toNode, snode))
                        return true;

               }

               if (vis_grey.find(edge->toNode) != vis_grey.end()) {
                   if (edge->toNode == parent)
                       continue;

                    return true;
               }
            }

            vis_grey.erase(snode);
            vis_black.insert(snode);
            return false;
        };

        for (const auto& kV : this->_list) {
            if (vis_black.find(&kV.first) != vis_black.end() || vis_grey.find(&kV.first) != vis_grey.end() )
                continue;

            if (_dfs(&kV.first, nullptr))
                return true;
        }

        return false;
}

template<typename NT, typename ET>
int LGraph<NT, ET>::distance(const NT &n1, const NT &n2) const {
    if (!this->nodeExist(n1) || !this->nodeExist(n2))
        return -1;

    std::unordered_map<const NT*, int> distances = this->_bfsDistances(&this->_list.find(n1)->first);

    return ( distances.count(&this->_list.find(n2)->first) == 1 ) ? distances[&this->_list.find(n2)->first] : -1;
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

template<typename NT, typename ET>
QString LGraph<NT, ET>::typeStr() const {
    return "LGraph";
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
