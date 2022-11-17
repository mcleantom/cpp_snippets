#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <tuple>
#include <vector>

template <class NodeDataType, class EdgeDataType> class DiGraph {
public:
    struct Node {
        int index;
        std::shared_ptr<NodeDataType> data;
        bool operator<(const Node& rhs) const { return data < rhs.data; }
        Node(int index)
            : index(index) {};
    };
    struct Edge {
        std::shared_ptr<Node> from;
        std::shared_ptr<Node> to;
        std::shared_ptr<EdgeDataType> data;
        float weight;
        Edge(std::shared_ptr<Node> from, std::shared_ptr<Node> to, float weight)
            : from(from)
            , to(to)
            , weight(weight) {};
        bool operator<(const Edge& rhs) const
        {
            return std::tie(from, to, weight) < std::tie(rhs.from, rhs.to, rhs.weight);
        }
    };
    DiGraph<NodeDataType, EdgeDataType>() {};
    std::shared_ptr<Node> addNode()
    {
        auto new_node = std::shared_ptr<Node>(new Node(m_Nodes.size()));
        m_Nodes.push_back(new_node);
        return new_node;
    };
    std::shared_ptr<Edge> addEdge(const std::shared_ptr<Node>& from, const std::shared_ptr<Node>& to, float weight)
    {
        auto new_edge = std::shared_ptr<Edge>(new Edge(from, to, weight));
        if (m_AdjacencyList.count(from)) {
            m_AdjacencyList[from].push_back(new_edge);
        }
        else {
            m_AdjacencyList.insert(
                std::pair<std::shared_ptr<Node>, std::vector<std::shared_ptr<Edge>>>(from, std::vector<std::shared_ptr<Edge>>()));
            m_AdjacencyList[from].push_back(new_edge);
        }
        return new_edge;
    };
    int outDegree(const std::shared_ptr<Node>& node) {
        return m_AdjacencyList[node].size();
    }
    int numNodes() {
        return m_Nodes.size();
    }
private:
    std::vector<std::shared_ptr<Node>> m_Nodes;
    std::map<std::shared_ptr<Node>, std::vector<std::shared_ptr<Edge>>> m_AdjacencyList;
};

#endif