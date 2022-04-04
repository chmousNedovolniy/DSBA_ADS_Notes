int main() {
    // Обзор функций графа.
    Graph<int> graph; // просто создаём граф, в вершинах которого инты
    // Graph<std::string> graph; // а здесь строки
    int data1 = 1, data2 = 2; //

    // Добавлять вершинки можно так
    Graph<int>::Node* node1 = graph.addNode(data1);
    Graph<int>::Node* node2 = graph.addNode(data2);

    // А можно в цикле
    std::vector<Graph<int>::Node*> nodes;
    for (int i = 0; i < 5; ++i) {
        nodes[i] = graph.addNode(i);
    }

    // Проверяем, существует ли вершина графа - на вход скармливаем её data
    bool does_exist = graph.existsNode(data1);

    // Добавляем рёбра - неориентированные и ориентированные
    int weight = 3;
    graph.addEdge(node1, node2, weight);
    graph.addDirectedEdge(node1, node2, weight);

    // Получаем указатель на вершинку по её data
    Graph<int>::Node* node = graph.getNode(data1);

    // Проверяем, существует ли ребро {node1, node2}
    bool edge_does_exist = graph.existsEdge(node1, node2);

    // Получаем вектор соседей вершины
    std::vector<Graph<int>::Node*> neighbors = graph.getNeighbors(node1);

    // Считаем входную и выходную степени вершины
    int out_count = graph.getNodeOutDegree(node);
    int in_count = graph.getNodeInDegree(node);

    // Получаем список добавленных верщин
    std::vector<Graph<int>::Node*> nodes_ = graph.getNodes();
    return 0;
}
