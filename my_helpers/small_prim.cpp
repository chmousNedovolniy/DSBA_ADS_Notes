int main() {
    // Ввод графа
    std::vector<bool> visited(graph.getNodes().size());
    std::vector<int> dist(graph.getNodes().size(), 1e9);
    std::set<std::pair<int, int>> unvisited;
    dist[0] = 0;
    unvisited.insert({ dist[0], 0 });
    
    int mstWeight = 0;

    while (!unvisited.empty()) {
        int nearestV = unvisited.begin()->second;
        unvisited.erase(unvisited.begin());

        visited[nearestV] = true;
        mstWeight += dist[nearestV];

        for (auto neighbor : graph.getNeighbors(graph.getNode(nearestV))) {
            int to = neighbor->data;
            int weight = graph.getEdgeWeight(graph.getNode(nearestV), neighbor);
            if (!visited[to] && dist[to] > weight) {
                unvisited.erase({ dist[to], to });
                dist[to] = weight;
                unvisited.insert({ dist[to], to });
            }
        }
    }
    std::cout << mstWeight << '\n';
    return 0;
}
