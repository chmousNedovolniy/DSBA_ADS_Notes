#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <queue>

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

    void addDirectedEdge(Node* nodeSource, Node* nodeDest, int weight)
    {
        bool existsNodeSource = std::find(_nodes.begin(), _nodes.end(), nodeSource) != _nodes.end();
        bool existsNodeDest = std::find(_nodes.begin(), _nodes.end(), nodeDest) != _nodes.end();

        if (existsNodeSource && existsNodeDest)
        {
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


using Node = Graph<std::string>::Node;
using MyGraph = Graph<std::string>;

template <typename T>
void DFS(Graph<T>& graph, typename Graph<T>::Node* s)
{
    using Node = typename Graph<T>::Node;

    std::stack<Node*> stack;

    std::map<Node*,bool> visited;

    for(Node* node : graph.getNodes())
        visited[node] = false;

    stack.push(s);

    while(!stack.empty() )
    {
        Node* v = stack.top();
        stack.pop();

        if(! visited[v] )
        {
            std::cout << v->data << std::endl; // our "visit" is to print the value of the node

            visited[v] = true;

            for(Node* u : graph.getNeighbors(v))
                if(! visited[u] )
                    stack.push(u);
        }
    }
}

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
            if(isVisited(v,path) == false)
            {
                std::vector<Node*> newPath(path);
                newPath.push_back(v);
                q.push(newPath);
            }
        }

    }

    return path;
}

int main() {
    return 0;
}
