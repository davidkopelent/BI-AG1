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
            if (u.second.empty()) {
                _graph.insert({u.first, {}});
                continue;
            }

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

    std::unordered_map<T, std::set<T>> graph(void) const {
        return _graph;
    }

private:
    std::unordered_map<T, std::set<T>> _graph;
};

template<typename T>
void bfs_graph(const Graph<T> &G) {
    size_t components = 1;
    std::set<T> visited;

    std::cout << "Graph contains these components:" << std::endl;
    for (const auto &v: G.graph()) {
        if (visited.count(v.first) == 0) {
            std::cout << "Component #" << components << " = {";
            bfs(G, visited, v.first);
            std::cout << "}\n";
            components++;
        }
    }
}

template<typename T>
void bfs(const Graph<T> &G, std::set<T> &visited, T s) {
    visited.insert(s);
    std::map<T, T> P; 
    std::map<T, size_t> D = {{s, 0}}; 
    std::deque<T> Q = {s};

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

        std::cout << u << (Q.empty() ? "" : ", ");
    }
}

int main() {
    Graph<int> g1({
        {1, {2}},
        {2, {3}},
        {3, {2}},
        {4, {5}},
        {5, {}}
    });
    bfs_graph(g1);

    Graph<int> g2({
        {1, {2}},
        {2, {3}},
        {3, {2}},
        {4, {5}},
        {5, {1}}
    });
    bfs_graph(g2);

    return EXIT_SUCCESS;
}
