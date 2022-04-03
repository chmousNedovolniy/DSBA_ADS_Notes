#include <string>
#include <map>
#include <climits>
#include <algorithm>
#include <queue>

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>

template<typename T>
class Graph
{
public:

    class Node
    {
    public:
        T data;
        double x;
        double y;
        Node(const T& data = T()) : data(data) {}
        bool operator()(const Node& lv,const Node& rv)
        {
            return lv.data < rv.data;
        }
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
            _edgeWeights.insert({ {nodeSource, nodeDest}, weight } );
            _edgesByWeight.insert({ weight, {nodeSource, nodeDest}});
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

    const std::map<std::pair<Node*,Node*>, int> getEdgeWeights() const
    {
        return _edgeWeights;
    }

    const std::multimap<int,std::pair<Node*,Node*>> getEdgesByWeight() const
    {
        return _edgesByWeight;
    }

    double getEdgeWeight(Node* nodeSource, Node* nodeDest)
    {
        return _edgeWeights[{nodeSource,nodeDest}];
    }

    const std::multimap<Node*, Node*> getAdjList() const
    {
        return _adjList;
    }

    void setEdgeWeight(Node* nodeSource, Node* nodeDest, int weight)
    {
        _edgeWeights[{nodeSource,nodeDest}] = weight;
//            for (auto it: _edgesByWeight)
//            {
//                if (it.second.first == nodeSource && it.second.second == nodeDest)
//                    _edgesByWeight.erase(it.first);
//            }
//            _edgesByWeight.insert({weight, {nodeSource,nodeDest}});
    }


private:

    std::multimap<Node*, Node*> _adjList;

    std::map<std::pair<Node*,Node*>,int> _edgeWeights; // O(LogN)

    std::multimap<int,std::pair<Node*,Node*>> _edgesByWeight; // M elements O(M)

    std::vector<Node*> _nodes;

};

using Node = Graph<std::string>::Node;
using MyGraph = Graph<std::string>;

using flowMapping = std::map<std::pair<Node*, Node*>, int>;

bool isVisited(Node* x, std::vector<Node*>& path)
{
    for (int i = 0; i < path.size(); i++)
        if (path[i] == x)
            return true;
    return false;
}

std::vector<Node*> bfs(MyGraph& graph, Node* source, Node* sink)
{
    std::queue<std::vector<Node*>> q; // queue which stores paths

    std::vector<Node*> path; // vector to store the current path

    path.push_back(source);

    q.push(path);

    while(q.empty() == false)
    {
        path = q.front();

        q.pop();

        Node* lastNode = path[path.size() - 1]; // get the last node of the current path

        if(lastNode == sink)
            break; // path found!

        for(Node* v : graph.getNeighbors(lastNode))
        {
            if(isVisited(v,path) == false && graph.getEdgeWeight(lastNode, v) > 0)
            {
                std::vector<Node*> newPath(path);
                newPath.push_back(v);
                q.push(newPath);
            }
        }

    }

    return path;
}

void update_residual(MyGraph& residual, MyGraph& network, std::map<std::pair<Node*, Node*>, int>& f)
{
    for (auto edge: network.getEdgeWeights())
    {
        Node* u = edge.first.first;
        Node* v = edge.first.second;
        Node* x = residual.getNode(u->data);
        Node* y = residual.getNode(v->data);
        residual.setEdgeWeight(x, y, network.getEdgeWeight(u, v) - f[{u, v}]);
        residual.setEdgeWeight(y, x, f[{u, v}]);
    }
}


flowMapping FordFulkersonAlgo(MyGraph& graph, Node* source, Node* sink)
{
    flowMapping flowMap;

    for(std::pair<Node*, Node*> edge : graph.getAdjList())
    {
        std::pair<Node*, Node*> edgeBack = {edge.second,edge.first};
        flowMap.insert({edge,0});
        flowMap.insert({edgeBack,0});

    }

    MyGraph Gf;

    for(Node* node: graph.getNodes())
    {
        Gf.addNode(node->data);
    }

    for(auto edge: graph.getEdgeWeights())
    {
        Node* u = edge.first.first;
        Node* v = edge.first.second;

        Node* x = Gf.getNode(u->data);
        Node* y = Gf.getNode(v->data);

        Gf.addEdge(x, y, edge.second);
        Gf.addEdge(y, x, 0);
    }


    //!!!!!
    Node* sourceGf = Gf.getNode(source->data);
    Node* sinkGf = Gf.getNode(sink->data);

    std::vector<Node*> P = bfs(Gf, sourceGf, sinkGf);


    while(P[P.size() - 1] == sinkGf)
    {
        int bottleneck = INT_MAX;
        //bottleneck min( { cf( (u,v) ) | (u,v) P } );
        for(int i = 1; i < P.size(); ++i)
        {
            if(Gf.getEdgeWeight(P[i-1], P[i]) < bottleneck)
                bottleneck = Gf.getEdgeWeight(P[i-1], P[i]);
        }

        for(int i = 0; i < P.size() - 1; ++i)
        {
            Node* u = graph.getNode(P[i]->data);
            Node* v = graph.getNode(P[i+1]->data);

            flowMap[{u,v}] += bottleneck;
            flowMap[{v,u}] -= bottleneck;
        }



        update_residual(Gf, graph, flowMap);

        P = bfs(Gf, sourceGf, sinkGf);

//    for(int i = 0; i < P.size();++i)
//    {
//        std::cout << P[i]->data;
//    }
//        std::cout << std::endl;

    }

    return flowMap;
}


int main()
{
    MyGraph graph;

    // Example of finding a path in a graph between a source node and a destination node

    Node* source = graph.addNode("s");
    Node* v2 = graph.addNode("2");
    Node* v3 = graph.addNode("3");
    Node* v4 = graph.addNode("4");
    Node* v5 = graph.addNode("5");
    Node* sink = graph.addNode("t");

    graph.addEdge(source,v2,10);
    graph.addEdge(source,v3,10);
    graph.addEdge(v2,v3,2);
    graph.addEdge(v2,v4,4);
    graph.addEdge(v2,v5,8);
    graph.addEdge(v3,v5,9);
    graph.addEdge(v5,v4,6);
    graph.addEdge(v5,sink,10);
    graph.addEdge(v4,sink,10);

//    std::vector<Node*> path = bfs(graph, source, sink); // get a path from the node source to the node sink

//    for(int i = 1; i < path.size(); i++)
//    {
//        Node* u = path[i-1];
//        Node* v = path[i];

//        std::cout << '(' << u->data << ',' << v->data << ") w=" << graph.getEdgeWeight(u,v) << std::endl;
//    }

    flowMapping flowMap = FordFulkersonAlgo(graph, source, sink);

    for(auto flow : flowMap)
    {
        std::cout << "(" << flow.first.first->data << "," << flow.first.second->data << ") flow=" << flow.second << std::endl;
    }

    return 0;
}
