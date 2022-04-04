#include <set>

// class works like easy-to-use set, which we utilize for extracting minimum values
template <typename T>
class PriorityQueue {
public:
    const T& getMin() const  // returns value of min key in pq
    {
        return _pq.begin()->second;
    }

    void update(const T& x, int oldWeight, int newWeight) // updates value of key x from oldWeight to newWeight
    {
        _pq.erase(_pq.find({oldWeight, x}));
        _pq.insert({newWeight, x});
    }

    void removeMin() // removes min key from pq
    {
        _pq.erase(_pq.begin());
    }

    void insert(const T& x, int weight) { // inserts pair {x, weight} into pq
        _pq.insert({weight, x});
    }

    bool empty() { // checks if pq is empty
        return !_pq.size();
    }

    void print() { // prints contents of pq
        for (auto pair: _pq)
            std::cout << '(' << pair.first << ',' << pair.second << ") ";
        std::cout << std::endl;
    }

private:
    std::set<std::pair<int, T>> _pq;
};

using Node = Graph<std::string>::Node;
using MyGraph = Graph<std::string>;

// Dijkstra, takes graph, starting end ending nodes, and empty vector path
// returns map of distances between startNode and all other nodes
// fills vector path with nodes on shortest path between startNode and endNode
std::map<Node*, int> dijkstra(MyGraph& graph, Node* startNode, Node* endNode, std::vector<Node*>& path) {
    std::map<Node*, int> distance;
    std::map<Node*, Node*> parentMap;
    std::map<Node*, bool> visited;
    PriorityQueue<Node*> pq;
    
    for (auto v: graph.getNodes()) {
        distance[v] = INT_MAX / 2; // be careful with int overflow, don't do INT_MAX + INT_MAX
        visited[v] = false;
        pq.insert(v, distance[v]);
        parentMap[v] = nullptr;
    }

    distance[startNode] = 0;
    pq.update(startNode, INT_MAX / 2, 0);

    while (!pq.empty()) {
        Node* u = pq.getMin();
        for (auto v: graph.getNeighbors(u)) {
            if (!visited[v] && distance[u] + graph.getEdgeWeight(u, v) < distance[v]) {
                pq.update(v, distance[v], distance[u] + graph.getEdgeWeight(u, v));
                distance[v] = distance[u] + graph.getEdgeWeight(u, v);
                parentMap[v] = u;
            }
        }

        visited[u] = true;
        pq.removeMin();

    }

    // getting path
    Node* curNode = endNode;
    while (curNode != nullptr) {
        path.push_back(curNode);
        curNode = parentMap[curNode];
    }
    std::reverse(path.begin(), path.end());
    return distance;
}

int main() {
    // setting up the graph

    std::vector<Node*> path;
    auto distance = dijkstra(graph, startNode, endNode, path);

    // printing all distances between startNode and other nodes
    for (auto pair: distance) {
        std::cout << pair.first->data << " : " << pair.second << std::endl;
    }

    // printing path between startNode and endNode
    for (auto elem : path) {
        std::cout << elem->data << ' ';
    }

    return 0;
}
