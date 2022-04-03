int main() {
    int node_count, edge_count; // or n, m - количество вершин и рёбер
    std::cin >> node_count >> edge_count;
    Graph<int> graph; // создание графа
    
    // Наиболее часто граф задают последовательностью ребёр на node_count вершинах.
    // В таком случае граф стоит считать так:
    // Добавляем верщины в граф
    std::vector<Graph<int>::Node*> nodes(node_count);
    for (int i = 0; i < node_count; ++i) {
        nodes[i] = graph.addNode(i);
    }
    
    // Теперь считываем рёбра
    for (int i = 0; i < edge_count; ++i) {
        int from, to; // считаем, что вершины пронумерованы с нуля
        int weight; // иногда дают, иногда нет
        // long long weigth; // если большой вес
        std::cin >> from >> to >> weight;
         // если нумерация с единицы, стоит сделать --from; --to;
        graph.addEdge(nodes[from], nodes[to], weight); // в случае неориентированного графа
        graph.addDirectedEdge(nodes[from], nodes[to], weight); // в случае ориентированного графа
    }    
    return 0;
}
