const int inf = 1e9;

// Floyd algo, returns map of shortest dists between all pairs of nodes in graph
std::map<std::pair<Node*, Node*>, long long> Floyd(MyGraph& graph) {
    std::map<std::pair<Node*, Node*>, long long> dists;

    // initializing dists
    for (auto from : graph.getNodes()) {
        for (auto to : graph.getNodes()) {
            if (from == to) {
                dists[{from, to}] = 0;
            } else if (graph.existsEdge(from, to)) {
                dists[{from, to}] = graph.getEdgeWeight(from, to);
            } else {
                dists[{from, to}] = inf;
            }
        }
    }

    for (auto k : graph.getNodes()) {
        for (auto from : graph.getNodes()) {
            for (auto to : graph.getNodes()) {
                // if graph has negative weights of edges, than we could observe thigs like INT_MAX - 1 or INT_MAX - other_negative_weight
                // it can actually make our infinity = INT_MAX not so big and crash the algo, so it's better to use if condition
                // which checks if some of the nodes is unreachable
                
                // So, if graph has negative edge weights, use this
                // if (dists[{from, k}] < INT_MAX && dists[{k, to}] < INT_MAX) {
                    // dists[{from, to}] = std::min(dists[{from, to}], dists[{from, k}] + dists[{k, to}]);
                // }
                
                // If no negative edge weights, use this
                dists[{from, to}] = std::min(dists[{from, to}], dists[{from, k}] + dists[{k, to}]);
            }
        }
    }
    return dists;
}

int main() {
    // input graph
    
    // printing all dists
    for (auto result : Floyd(graph)) {
        std::cout << result.first.first->data << ' ' << result.first.second->data << ' ' << result.second << '\n';
    }
    return 0;
}
