const int inf = 1e9;

// Works like Dijkstra algo, finds all  dists between startNode and other nodes, returns them in map
std::map<Node*, int> BellmanFord(MyGraph& graph, Node* startNode, Node* endNode) {
    std::map<Node*, int> distance;

    for (auto v: graph.getNodes()) {
        distance[v] = inf;
    }

    distance[startNode] = 0;

    int node_count = graph.getNodes().size();
    auto edges = graph.getEdgeWeights();
    for (int i = 1; i < node_count; ++i) {

        // You can write inner cycle like this
        // for (auto edge : edges) {
            // Node* from = edge.first.first;
            // Node* to = edge.first.second;
            // int weight = edge.second;
            // if (distance[from] < INT_MAX / 2) {
                // distance[to] = std::min(distance[to], distance[from] + weight);
            // }
        // }

        // Or like this, which is preferable, because was used in seminar presentation
        for (auto from : graph.getNodes()) {
            for (auto to : graph.getNeighbors(from)) {
                distance[to] = std::min(distance[to], distance[from] + graph.getEdgeWeight(from, to));
            }
        }
    }

    return distance;
}


int main() {
    // setting up the graph
  
    std::map<Node*, int> distance = BellmanFord(graph, startNode, endNode);

    // printing all distances between startNode and other nodes
    for (auto pair: distance) {
        std::cout << pair.first->data << " : " << pair.second << std::endl;
    }

    return 0;
}
