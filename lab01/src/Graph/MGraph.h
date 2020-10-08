#ifndef MGRAPH_H
#define MGRAPH_H

#include "Graph.h"

#include <algorithm>
#include <memory>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <functional>

#include <QDebug>

///
///\brief Matrix graph class
///
///MGraph implemented using matrix containing adges.
///Consumes O(|N|^2) space, where |N| - number of nodes, |E| - number of edges.
///
template <typename NT, typename ET>
class MGraph : public Graph<NT, ET> {
private:
    ///
    /// \brief The Edge class
    ///
    /// To store data somewhere and use smart pointers to them.
    ///
    struct Edge {
      ET data;

      Edge(const ET& data) : data {data} {}
      ~Edge() = default;
    };

    ///
    /// \brief _nodes stores Nodes values
    ///
    std::vector<NT> _nodeList;

    ///
    /// \brief _matrix stores Edge values which represent connection between nodes
    ///
    std::vector<std::vector<std::shared_ptr<Edge>>> _matrix;

    int _nodes;
    int _edges;


    ///
    /// \brief Depth First Search
    /// \param snode Pointer to starting node
    /// \param visited Pointer to set containing visited nodes
    ///
    /// An internal implementation of Depth First Search to be widely use in MGraph methods.
    ///
    void _dfs(const NT& snode, std::unordered_set<const NT*>* visited) const;

    ///
    /// \brief Breadth First Search
    /// \param snode Pointer to starting node
    /// \param visited Pointer to set containing visited nodes
    ///
    /// An internal implementation of node - distances to other nodes using Breadth First Search to be widely use in MGraph methods.
    ///
    [[nodiscard]] std::unordered_map<const NT*, int> _bfsDistances(const NT* snode) const;

public:
    ///
    /// \brief Basic constructor.
    ///
    MGraph();

    ///
    /// \brief Constructor using initializer_list of nodes.
    /// \param list Initializer_list of nodes
    ///
    /// Is used to create MGraph and add Nodes given in std::initializer_list.
    ///
    explicit MGraph(std::initializer_list<NT> list);

    ~MGraph() = default;

    ///
    /// \brief Add a node
    /// \param data Data to be added as node
    ///
    /// Adds a node with [ data ] to MGraph.
    ///
    void addNode(const NT& data) override;

    ///
    /// \brief Checks if node exist
    /// \param data Data to be searched
    /// \return bool Whether node with [ data ] exists
    ///
    /// Checks whether node with [ data ] is presented in MGraph.
    ///
    bool nodeExist(const NT& data) const override;

    ///
    /// \brief Erase node
    /// \param data Node with [ data ] to be erased
    ///
    /// Erases node with data = [ data ] and all its edges.
    ///
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
    const ET* getEdge(const NT& n1, const NT& n2) const override;

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


    int nodes() const override;

    int edges() const override;

    bool empty() const override;
};

#endif // MGRAPH_H



// -------------------------------------- INTERNAL METHODS --------------------------------------

template<typename NT, typename ET>
void MGraph<NT, ET>::_dfs(const NT &snode, std::unordered_set<const NT *> *visited) const {
    if (visited->count(&snode))
            return;

    std::stack<const NT*> nodes;
    nodes.push(&snode);
    visited->insert(&snode);

    while (!nodes.empty()) {
        const NT* current = nodes.top();
        nodes.pop();

        int nodeIdx = std::find(this->_nodeList.begin(), this->_nodeList.end(), *current) - this->_nodeList.begin();

        for (int i = 0; i < this->_nodes; i++) {
            if (!this->_matrix[nodeIdx][i])
                continue;

            if (!visited->count(&this->_nodeList[i])) {
                nodes.push(&this->_nodeList[i]);
                visited->insert(&this->_nodeList[i]);
            }
        }
    }
}

template<typename NT, typename ET>
std::unordered_map<const NT *, int> MGraph<NT, ET>::_bfsDistances(const NT *snode) const {
    std::unordered_set<const NT*> visited;
    std::unordered_map<const NT*, int> distances;

    std::queue<const NT*> queue;
    queue.push(snode);

    visited.insert(snode);
    distances[snode] = 0;

    while (!queue.empty()) {

        const NT* curr = queue.front();
        queue.pop();

        int nodeIdx = std::find(this->_nodeList.begin(), this->_nodeList.end(), *curr) - this->_nodeList.begin();

        for (int i = 0; i < this->_nodes; i++) {
            if (!this->_matrix[nodeIdx][i])
                continue;

            if (visited.count(&this->_nodeList[i]) == 1)
                continue;

            distances[&this->_nodeList[i]] = distances[curr] + 1;
            visited.insert(&this->_nodeList[i]);
            queue.push(&this->_nodeList[i]);
        }
    }

    return distances;
}



// -------------------------------------- CONSTRUCTOR, DESTRUCTOR --------------------------------------

template<typename NT, typename ET>
MGraph<NT, ET>::MGraph() : _nodes {0}, _edges {0} {}

template<typename NT, typename ET>
MGraph<NT, ET>::MGraph(std::initializer_list<NT> list)
    : _nodes {0}, _edges {0} {
    for (const auto& node : list) {
        this->addNode(node);
    }
}



// -------------------------------------- NODE METHODS --------------------------------------

template<typename NT, typename ET>
void MGraph<NT, ET>::addNode(const NT &data) {
    if (this->nodeExist(data))
        return;

    this->_nodes++;

    this->_nodeList.emplace_back(data);

    for (auto& row : this->_matrix)
         row.resize(this->_nodes, nullptr);

    this->_matrix.emplace_back(std::vector<std::shared_ptr<Edge>>(this->_nodes, nullptr));
}

template<typename NT, typename ET>
bool MGraph<NT, ET>::nodeExist(const NT &data) const {
    return std::find(this->_nodeList.begin(), this->_nodeList.end(), data) != this->_nodeList.end();
}

template<typename NT, typename ET>
void MGraph<NT, ET>::eraseNode(const NT &data) {
    if (!this->nodeExist(data))
        return;

    int idx = std::find(this->_nodeList.begin(), this->_nodeList.end(), data) - this->_nodeList.begin();

    for (auto& row : this->_matrix)
        row.erase(row.begin() + idx);

    this->_matrix.erase(this->_matrix.begin() + idx);

    this->_nodeList.erase(this->_nodeList.begin() + idx);

    this->_nodes--;
}



// -------------------------------------- EDGE METHODS --------------------------------------

template<typename NT, typename ET>
void MGraph<NT, ET>::addEdge(const NT &n1, const NT &n2, const ET &edgeData) {
    if (!this->nodeExist(n1) || !this->nodeExist(n2))
        return;

    int n1Idx = std::find(this->_nodeList.begin(), this->_nodeList.end(), n1) - this->_nodeList.begin();
    int n2Idx = std::find(this->_nodeList.begin(), this->_nodeList.end(), n2) - this->_nodeList.begin();

    std::shared_ptr<Edge> edgePtr = std::shared_ptr<Edge>(new Edge(edgeData));

    this->_matrix[n1Idx][n2Idx] = edgePtr;
    this->_matrix[n2Idx][n1Idx] = edgePtr;

    this->_edges++;
}

template<typename NT, typename ET>
const ET *MGraph<NT, ET>::getEdge(const NT &n1, const NT &n2) const {
    if (!this->nodeExist(n1) || !this->nodeExist(n2))
        return nullptr;

    int n1Idx = std::find(this->_nodeList.begin(), this->_nodeList.end(), n1) - this->_nodeList.begin();
    int n2Idx = std::find(this->_nodeList.begin(), this->_nodeList.end(), n2) - this->_nodeList.begin();

    return (this->_matrix[n1Idx][n2Idx] ? &this->_matrix[n1Idx][n2Idx]->data : nullptr);
}

template<typename NT, typename ET>
bool MGraph<NT, ET>::edgeExist(const NT &n1, const NT &n2) const {
    if (!this->nodeExist(n1) || !this->nodeExist(n2))
        return false;

    int n1Idx = std::find(this->_nodeList.begin(), this->_nodeList.end(), n1) - this->_nodeList.begin();
    int n2Idx = std::find(this->_nodeList.begin(), this->_nodeList.end(), n2) - this->_nodeList.begin();

    return this->_matrix[n1Idx][n2Idx] != nullptr;
}

template<typename NT, typename ET>
void MGraph<NT, ET>::eraseEdge(const NT &n1, const NT &n2) {
    if (!this->nodeExist(n1) || !this->nodeExist(n2))
        return;

    int n1Idx = std::find(this->_nodeList.begin(), this->_nodeList.end(), n1) - this->_nodeList.begin();
    int n2Idx = std::find(this->_nodeList.begin(), this->_nodeList.end(), n2) - this->_nodeList.begin();

    if (this->_matrix[n1Idx][n2Idx] != nullptr) {
        this->_matrix[n1Idx][n2Idx] = nullptr;
        this->_matrix[n2Idx][n1Idx] = nullptr;

        this->_edges--;
    }
}

template<typename NT, typename ET>
void MGraph<NT, ET>::eraseEdges() {
    this->_edges = 0;

        for (int i = 0; i < this->_nodes; i++)
            for (int j = 0; j < this->_nodes; j++)
                this->_matrix[i][j] = nullptr;

}



// -------------------------------------- GRAPH PROPERTIES METHODS --------------------------------------

template<typename NT, typename ET>
void MGraph<NT, ET>::dfs(const NT &snode, std::unordered_set<const NT *> *visited) const {
    this->_dfs(snode, visited);
}

template<typename NT, typename ET>
bool MGraph<NT, ET>::connected() const {
    if (this->empty())
        return true;

    std::unordered_set<const NT*> visited;
    this->dfs(this->_nodeList[0], &visited);

    if (this->_nodeList.size() != visited.size())
        return false;

    return true;
}

template<typename NT, typename ET>
bool MGraph<NT, ET>::cyclic() const {
    std::unordered_set<const NT*> vis_black;
    std::unordered_set<const NT*> vis_grey;

        std::function<bool(const NT*, const NT*)> _dfs = [&](const NT* snode, const NT* parent) {
            vis_grey.insert(snode);

            int nodeIdx = std::find(this->_nodeList.begin(), this->_nodeList.end(), *snode) - this->_nodeList.begin();

            for (int i = 0; i < this->_nodes; i++) {
                if (!this->_matrix[nodeIdx][i])
                    continue;

               if (vis_black.find(&this->_nodeList[i]) == vis_black.end() && vis_grey.find(&this->_nodeList[i]) == vis_grey.end()) {
                    if (_dfs(&this->_nodeList[i], snode))
                        return true;

               }

               if (vis_grey.find(&this->_nodeList[i]) != vis_grey.end()) {
                   if (&this->_nodeList[i] == parent)
                       continue;

                    return true;
               }
            }

            vis_grey.erase(snode);
            vis_black.insert(snode);
            return false;
        };

        for (const auto& node : this->_nodeList) {
            if (vis_black.find(&node) != vis_black.end() || vis_grey.find(&node) != vis_grey.end() )
                continue;

            if (_dfs(&node, nullptr))
                return true;
        }

        return false;
}

template<typename NT, typename ET>
int MGraph<NT, ET>::distance(const NT &n1, const NT &n2) const {
    if (!this->nodeExist(n1) || !this->nodeExist(n2))
        return -1;

    int node1Idx = std::find(this->_nodeList.begin(), this->_nodeList.end(), n1) - this->_nodeList.begin();
    int node2Idx = std::find(this->_nodeList.begin(), this->_nodeList.end(), n2) - this->_nodeList.begin();

    std::unordered_map<const NT*, int> distances = this->_bfsDistances(&this->_nodeList[node1Idx]);

    return ( distances.count(&this->_nodeList[node2Idx]) == 1 ) ? distances[&this->_nodeList[node2Idx]] : -1;
}



// -------------------------------------- GETTERS --------------------------------------

template<typename NT, typename ET>
int MGraph<NT, ET>::nodes() const {
    return this->_nodes;
}

template<typename NT, typename ET>
int MGraph<NT, ET>::edges() const {
    return this->_edges;
}

template<typename NT, typename ET>
bool MGraph<NT, ET>::empty() const {
    return this->_nodes == 0;
}
