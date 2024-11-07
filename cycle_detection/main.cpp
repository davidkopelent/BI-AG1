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
bool has_cycle(const Graph<T> &G) {
    std::unordered_map<T, State> states;

    for (const auto &v: G.graph())
        states.insert({v.first, State::FRESH});

    for (const auto &v: G.graph()) {
        if (states[v.first] == State::FRESH && dfs(G, states, v.first))
            return true;
    }

    return false;
}

template<typename T>
bool dfs(const Graph<T> &G, std::unordered_map<T, State> &states, T v) {
    if (states[v] == State::OPEN) return true;
    if (states[v] == State::CLOSED) return false;
    states[v] = State::OPEN;

    for (const auto &w: G[v]) {
        if (dfs(G, states, w))
            return true;
    }

    states[v] = State::CLOSED;
    return false;
}

int main() {
    Graph<int> g1({
        {1, {2}},
        {2, {3}},
        {3, {}}
    });

    Graph<int> g2({
        {1, {2,3,5}},
        {2, {4}},
        {3, {}},
        {4, {1,5}},
        {5, {}}
    });

    Graph<int> g3({
        {1, {2,3,5}},
        {2, {}},
        {3, {}},
        {4, {1,5}},
        {5, {}}
    });

    Graph<int> g4({
        {1, {2,5}},
        {2, {3,4}},
        {3, {4}},
        {4, {}},
        {5, {4}}
    });

    Graph<int> g5({
        {1, {2,3}},
        {2, {1}},
        {3, {1}}
    });

    Graph<int> g6({
        {1, {2}},
        {2, {1}}
    });

    assert(has_cycle(g1) == false);
    assert(has_cycle(g2) == true);
    assert(has_cycle(g3) == false);
    assert(has_cycle(g4) == false);
    assert(has_cycle(g5) == true);
    assert(has_cycle(g6) == true);
    return EXIT_SUCCESS;
}
