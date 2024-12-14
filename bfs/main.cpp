#include <cassert>
#include <iomanip>
#include <cstdint>
#include <iostream>
#include <memory>
#include <limits>
#include <optional>
#include <algorithm>
#include <bitset>
#include <list>
#include <array>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <random>
#include <type_traits>
#include <compare>

enum State {
    NOTFOUND,
    OPENED,
    CLOSED
};

template<typename T>
class Graph {
public:
    Graph(const std::map<T, std::set<T>> &graph) {
        for (const auto &u : graph) {
            for (const auto &v : u.second)
                add_edge(u.first, v);
        }
    }

    void add_edge(const T &u, const T &v) {
        _graph[u].insert(v);
        _graph[v].insert(u);
    }

    const std::set<T>& operator[](const T &v) const {
        return _graph.at(v); 
    }

private:
    std::unordered_map<T, std::set<T>> _graph;
};

template<typename T>
void bfs(const Graph<T> &G, T s) {
    std::set<T> visited = {s};
    std::map<T, T> P; 
    std::map<T, size_t> D = {{s, 0}}; 
    std::deque<T> Q = {s};
    int outCount = 0;

    while (!Q.empty()) {
        T u = Q.front();
        Q.pop_front();

        for (const auto &v : G[u]) {
            if (visited.count(v) == 0) {
                Q.push_back(v);
                D[v] = D[u] + 1;
                P[v] = u;
                visited.insert(v);
            }
        }
    }
}

int main() {
    Graph<int> g({
        {1, {2}},
        {2, {3}},
        {3, {2}}
    });

    bfs(g, 1);
    return EXIT_SUCCESS;
}
