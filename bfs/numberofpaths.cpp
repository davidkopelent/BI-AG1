#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <vector>
#include <map>
#include <set>
#include <cassert>

enum State {
    FRESH,
    OPEN,
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
size_t number_of_paths(const Graph<T> &G, T s, T t) {
    return bfs(G, s, t);
}

template<typename T>
size_t bfs(const Graph<T> &G, T s, T t) {
    std::deque<T> Q = {s};
    std::set<T> visited = {s};
    std::map<T, size_t> number_of_paths;
    std::map<T, size_t> distance;
    distance[s] = 0;
    number_of_paths[s] = 1;

    while (!Q.empty()) {
        T v = Q.front();
        Q.pop_front();

        for (const auto &u: G[v]) {
            if (visited.count(u) == 0) {
                visited.insert(u);
                Q.push_back(u);
                distance[u] = distance[v] + 1;
                number_of_paths[u] = number_of_paths[v];
            } else if (distance[u] == distance[v] + 1) {
                number_of_paths[u] += number_of_paths[v];
            }
        }
    }

    return number_of_paths[t];
}

int main() {
    Graph<int> g1({
        {1, {2}},
        {2, {3}},
        {3, {4}},
        {4, {1}} 
    });

    assert(number_of_paths(g1, 1, 4) == 1);

    Graph<int> g2({
        {1, {2, 3}},
        {2, {4}},
        {3, {4}},
        {4, {}} 
    });

    assert(number_of_paths(g2, 1, 4) == 2);

    return EXIT_SUCCESS;
}
