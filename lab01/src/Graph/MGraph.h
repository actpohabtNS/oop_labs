#ifndef MGRAPH_H
#define MGRAPH_H

#include "Graph.h"

#include <vector>

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
    /// \brief _nodes stores Nodes values
    ///
    std::vector<NT> _nodesList;

    ///
    /// \brief _matrix stores Edge values which represent connection between nodes
    ///
    std::vector<std::vector<ET>> _matrix;

    int _nodes;
    int _edges;

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
