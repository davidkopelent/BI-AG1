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
bool has_cycle_dfs(const Graph<T> &G) {
    std::unordered_map<T, State> states;

    for (const auto &v : G.graph())
        states[v.first] = State::FRESH;

    for (const auto &v : G.graph()) {
        if (states[v.first] == State::FRESH) {
            if (dfs(G, states, v.first, T{})) {
                return true;
            }
        }
    }

    return false;
}

template<typename T>
bool dfs(const Graph<T> &G, std::unordered_map<T, State> &states, T v, T parent) {
    states[v] = State::OPEN;

    for (const auto &neighbor : G[v]) {
        if (states[neighbor] == State::FRESH) {
            if (dfs(G, states, neighbor, v)) {
                return true;  // Nalezen cyklus
            }
        } else if (neighbor != parent) {
            return true;  // Nalezen cyklus (zpětná hrana)
        }
    }

    states[v] = State::CLOSED;
    return false;
}

template<typename T>
bool has_cycle_bfs(const Graph<T> &G) {
    std::unordered_map<T, State> states;

    for (const auto &v: G.graph())
        states[v.first] = State::FRESH;
    
    for (const auto &v: G.graph()) {
        if (states[v.first] == State::FRESH) {
            if (bfs(G, v.first, states))
                return true;
        }
    }

    return false;
}

template<typename T>
bool bfs(const Graph<T> &G, T s, std::unordered_map<T, State> &states) {
    std::deque<T> Q = {s};
    std::set<T> visited = {s};
    std::map<T, T> P;

    while (!Q.empty()) {
        T v = Q.front();
        Q.pop_front();

        for (const auto &u: G[v]) {
            if (states[u] == State::OPEN && u != P[v])
                return true;

            if (visited.count(u) == 0) {
                states[u] = State::OPEN;
                visited.insert(u);
                Q.push_back(u);
                P[u] = v;
            }
        }

        states[v] = State::CLOSED;
    }

    return false;
}

int main() {
    Graph<int> g1({
        {1, {2}},
        {2, {3}},
        {3, {1}}  // Tento graf má cyklus 1 -> 2 -> 3 -> 1
    });
    assert(has_cycle_dfs(g1) == true);
    assert(has_cycle_bfs(g1) == true);

    Graph<int> g2({
        {1, {2, 3, 5}},
        {2, {4}},
        {3, {}},
        {4, {1, 5}}, // Cyklus 1 -> 2 -> 4 -> 1
        {5, {}}
    });
    assert(has_cycle_dfs(g2) == true);
    assert(has_cycle_bfs(g2) == true);

    Graph<int> g3({
        {1, {2, 3, 5}},
        {2, {}},
        {3, {}},
        {4, {1, 5}}, // Tento graf má cyklus
        {5, {}}
    });
    assert(has_cycle_dfs(g3) == true);
    assert(has_cycle_bfs(g3) == true);

    Graph<int> g4({
        {1, {2, 5}},
        {2, {3, 4}},
        {3, {4}},
        {4, {}},    // Tento graf má cyklus
        {5, {4}}
    });
    assert(has_cycle_dfs(g4) == true);
    assert(has_cycle_bfs(g4) == true);

    Graph<int> g5({
        {1, {2, 3}},
        {2, {1}},   
        {3, {1}}   
    });
    assert(has_cycle_dfs(g5) == false);
    assert(has_cycle_bfs(g5) == false);

    Graph<int> g6({
        {1, {2}},
        {2, {1}}     
    });
    assert(has_cycle_dfs(g6) == false);
    assert(has_cycle_bfs(g6) == false);

    return EXIT_SUCCESS;
}
