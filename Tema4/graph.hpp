#include <vector>
#include <map>
#include <stdexcept>
#include <queue>
#include <fstream>
#include <utility>

template <typename NodeType>
class DirectedGraph {
    using matrix = std::vector<std::vector<uint>>;

    public:
    DirectedGraph() {}
    DirectedGraph(const std::vector<NodeType>& nodesValues, const std::vector<std::pair<uint, uint>>& edges) {
        nodes = nodesValues;
        adjacencyLists.resize(nodes.size());
        for (const auto& edge: edges) {
            addEdge(edge.first, edge.second);
        }
    }

    uint addNode(const NodeType& newNodeValue) {
        nodes.push_back(newNodeValue);
        adjacencyLists.push_back({});
        return nodes.size() - 1;
    }

    void addEdge(const uint source, const uint target) {
        if (source >= nodes.size() or target >= nodes.size()) throw std::invalid_argument("Source or target does not exist.");
        adjacencyLists[source].push_back(target);
    }

    uint twoCycles() const {
        uint counter = 0;
        for (uint node = 0; node < nodes.size(); node++) {
            for (const auto& neighbour: adjacencyLists[node]) {
                if (hasEdge(neighbour, node)) counter++;
            }
        }

        return counter / 2;
    }

    bool hasEdge(const uint source, const uint target) const {
        for (const auto& neighbour: adjacencyLists[source]) {
            if (neighbour == target) return true;
        }
        
        return false;
    }

    void BFSPrint(const uint startNode, std::ostream& out) const {
        if (startNode >= nodes.size()) throw std::invalid_argument("Source does not exist."); 

        std::queue<uint> nodesQueue;
        std::vector<bool> visited(nodes.size(), false);

        nodesQueue.push(startNode);
        while (not nodesQueue.empty()) {
            uint currentNode = nodesQueue.front();
            nodesQueue.pop();

            out << currentNode << " ";

            if (visited[currentNode]) continue;
            visited[currentNode] = true;

            for (const auto &neighbour: adjacencyLists[currentNode]) {
                if (not visited[neighbour]) {
                    nodesQueue.push(neighbour);
                }
            }
        }
        out << std::endl;
    }

    void DFSPrint(const uint startNode, std::ostream& out) const {
        std::vector<bool> visited(nodes.size(), false);
        DFSPrintInternal(startNode, out, visited);
        out << std::endl;
    }

    private:
    void DFSPrintInternal(const uint currentNode, std::ostream& out, std::vector<bool>& visited) const {
        visited[currentNode] = true;
        out << currentNode << " ";

        for (const auto& neighbour: adjacencyLists[currentNode]) {
            if (not visited[neighbour]) {
                DFSPrintInternal(neighbour, out, visited);
            }
        }
    }

    matrix adjacencyLists;
    std::vector<NodeType> nodes; 
};