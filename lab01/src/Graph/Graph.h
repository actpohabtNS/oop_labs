#ifndef GRAPH_H
#define GRAPH_H

template <typename NT, typename ET>
class Graph {
public:
    Graph() = default;
    virtual ~Graph() = default;

    virtual void addNode(const NT& data) = 0;
    virtual void eraseNode(const NT& data) = 0;
    virtual bool nodeExist(const NT& data) const = 0;

    virtual void addEdge(const NT& n1, const NT& n2, const ET& edgeData) = 0;
    virtual void eraseEdge(const NT& n1, const NT& n2) = 0;
    virtual const ET* getEdge(const NT& n1, const NT& n2) const = 0;
    virtual bool edgeExist(const NT& n1, const NT& n2) const = 0;
    virtual void eraseEdges() = 0;

//    virtual void weighed(bool weighed) = 0;

//    virtual bool connected() const = 0;
//    virtual bool cyclic() const = 0;

//    [[nodiscard]] virtual int distance(const NT& n1, const NT& n2) const = 0;

    virtual int nodes() const = 0;
    virtual int edges() const = 0;
    virtual bool empty() const = 0;
    virtual bool weighed() const = 0;
};

#endif // GRAPH_H
