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
                dists[{from, to}] = INT_MAX;
            }
        }
    }

    for (auto k : graph.getNodes()) {
        for (auto from : graph.getNodes()) {
            for (auto to : graph.getNodes()) {
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
