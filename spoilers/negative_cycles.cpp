// returns true if negative cycle exists or false if it doesn't using BellmanFord algo
bool NegativeCycleBellmanFord(MyGraph& graph, Node* startNode, Node* endNode) {
    std::map<Node*, int> distance;

    for (auto v: graph.getNodes()) {
        distance[v] = INT_MAX / 2;
    }

    distance[startNode] = 0;

    int node_count = graph.getNodes().size();
    for (int i = 0; i < node_count; ++i) { // i = 0, not i = 1, we make additional iteration

        for (auto from : graph.getNodes()) {
            for (auto to : graph.getNeighbors(from)) {
                int old_distance = distance[to]; // saving old dist
                distance[to] = std::min(distance[to], distance[from] + graph.getEdgeWeight(from, to));
                
                if (i == node_count - 1) { // last_iteration
                    if (old_distance != distance[to]) { // sth changed on last iteration only if negative cycle exists
                        return true; // cycle exists
                    }
                }
            }
        }
    }

    return false; // no negative cycles found previously
}

int main() {
    // setting up the graph
    
    if (NegativeCycleBellmanFord(graph, startNode, endNode)) {
        std::cout << "Has negative cycle";
    } else {
        std::cout << "No negative cycles";
    }
    return 0;
}
