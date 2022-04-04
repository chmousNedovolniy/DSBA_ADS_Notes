#include <set>

// class works like easy-to-use set, which we utilize for extracting minimum values
template <typename T>
class PriorityQueue {
public:
    const T& getMin() const  // returns value of min key in pq
    {
        return _pq.begin()->second;
    }

    void update(const T& x, int oldWeight, int newWeight) // updates value of key x from oldWeight to newWeight
    {
        _pq.erase(_pq.find({oldWeight, x}));
        _pq.insert({newWeight, x});
    }

    void removeMin() // removes min key from pq
    {
        _pq.erase(_pq.begin());
    }

    void insert(const T& x, int weight) { // inserts pair {x, weight} into pq
        _pq.insert({weight, x});
    }

    bool empty() { // checks if pq is empty
        return !_pq.size();
    }

    void print() { // prints contents of pq
        for (auto pair: _pq)
            std::cout << '(' << pair.first << ',' << pair.second << ") ";
        std::cout << std::endl;
    }

private:
    std::set<std::pair<int, T>> _pq;
};
