class DSU {
public:
    std::vector<int> id;
    std::vector<int> sizes;

    explicit DSU(int vertex_count) : id(vertex_count), sizes(vertex_count, 1) {
        for (int i = 0; i != vertex_count; ++i)
            id[i] = i;
    }

    int FindSet(int vertex) {
        if (id[vertex] == vertex)
            return vertex;
        return id[vertex] = FindSet(id[vertex]);
    };

    void Merge(int vertex1, int vertex2) {
        int set1 = FindSet(vertex1);
        int set2 = FindSet(vertex2);
        if (set1 == set2)
            return;
        if (sizes[set1] < sizes[set2]) {
            id[set1] = set2;
            sizes[set2] += sizes[set1];
        } else {
            id[set2] = set1;
            sizes[set1] += sizes[set2];
        }
    };

    bool IsConnected(int vertex1, int vertex2) {
        return FindSet(vertex1) == FindSet(vertex2);
    }
};


int main() {
    // Ввод графа

    DSU dsu(node_count);
    long long mst_weight = 0;
    for (auto edge : graph.getEdgesByWeight()) {
        int len = edge.first;
        auto nodes_pair = edge.second;
        if (!dsu.IsConnected(nodes_pair.first->data, nodes_pair.second->data)) {
            dsu.Merge(nodes_pair.first->data, nodes_pair.second->data);
            mst_weight += len;
        }
    }
    // Вывод минимального веса остовного дерева.
    std::cout << mst_weight << '\n';

    return 0;
}
