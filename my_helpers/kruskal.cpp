#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <stack>

template<typename T>
class Graph
{
public:

    class Node
    {
    public:
        T data;
        Node(const T& data = T()) : data(data) {}
    };

    ~Graph()
    {
        for (Node* node : _nodes)
            delete node;
    }

    Node* addNode(const T& data = T())
    {
        Node* node = new Node(data);

        _nodes.push_back(node);

        return node;
    }

    bool existsNode(T& x)
    {
        // Check if exists a node with data = x
        for(Node* node : _nodes)
            if(node->data == x)
                return true;
        return false;
    }

    void addEdge(Node* nodeSource, Node* nodeDest, int weight)
    {
        bool existsNodeSource = std::find(_nodes.begin(), _nodes.end(), nodeSource) != _nodes.end();
        bool existsNodeDest = std::find(_nodes.begin(), _nodes.end(), nodeDest) != _nodes.end();

        if (existsNodeSource && existsNodeDest)
        {
            // Create two edges (A,B) and (A,B) which represent a bi-directional link A<--->B
            _adjList.insert( { nodeSource , nodeDest });
            _adjList.insert( { nodeDest , nodeSource  });

            _edgeWeights.insert({ {nodeSource, nodeDest}, weight } );
            _edgeWeights.insert({ {nodeDest, nodeSource}, weight } );

            _edgesByWeight.insert({ weight, {nodeSource, nodeDest}});
            _edgesByWeight.insert({ weight, {nodeDest, nodeSource}});
        }
    }

    Node* getNode(const T& data)
    {
        for(Node* node : _nodes)
            if(node->data == data)
                return node;
        return nullptr;
    }

    bool existsEdge(Node* x, Node* y)
    {
        auto ret = _adjList.equal_range(x);

        // all pairs whose first component is equal to x are in the range [ret->first, ret->second)
        for(auto it = ret.first; it != ret.second; ++it)
            if(it->second == y)
                return true;
        return false;
    }

    std::vector<Node*> getNeighbors(Node* x)
    {
        std::vector<Node*> neighbors;

        auto ret = _adjList.equal_range(x);

        for(auto it = ret.first; it != ret.second; ++it)
            neighbors.push_back(it->second);

        // for every node "y" in the vector "neighbors", there exists an edge "(x,y)" in the graph.
        return neighbors;
    }

    int getNodeOutDegree(Node* x)
    {
        return this->getNeighbors(x).size();
    }

    int getNodeInDegree(Node* x)
    {
        int cnt = 0;

        for(auto pair : _adjList)
            if(pair.second == x)
                cnt++;
        return cnt;
    }

    const std::vector<Node*>& getNodes() const
    {
        return _nodes;
    }

    const std::map<std::pair<Node*,Node*>,int> getEdgeWeights() const
    {
        return _edgeWeights;
    }

    const std::multimap<int,std::pair<Node*,Node*>> getEdgesByWeight() const
    {
        return _edgesByWeight;
    }

    int getEdgeWeight(Node* nodeSource, Node* nodeDest)
    {
        return _edgeWeights[{nodeSource,nodeDest}];
    }

private:

    std::multimap<Node*, Node*> _adjList;

    std::map<std::pair<Node*,Node*>,int> _edgeWeights;

    std::multimap<int,std::pair<Node*,Node*>> _edgesByWeight;

    std::vector<Node*> _nodes;

};


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
        --from;
        --to;
        // если нумерация с единицы, стоит сделать --from; --to;
        graph.addEdge(nodes[from], nodes[to], weight); // в случае неориентированного графа
    }

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
    std::cout << mst_weight << '\n';

    return 0;
}