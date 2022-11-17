#include "digraph.h"
#include <iostream>

struct NodeData {
    int age;
    bool operator<(const NodeData& rhs) const {
        return age < rhs.age;
    }
};

struct EdgeData {
    int weight;
};

int main() {
    DiGraph<NodeData, EdgeData> graph;
    auto first_node = graph.addNode();
    auto second_node = graph.addNode();
    for (auto i = 0; i < 1e6; ++i) {
        graph.addNode();
    }
    for (int i = 0; i < 1e6; ++i) {
        graph.addEdge(first_node, second_node, i);
    }
    std::cout << graph.outDegree(first_node) << std::endl;
}