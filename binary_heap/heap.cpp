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

class Heap {
public:
    Heap() = default;

    void heapBuild(const std::vector<int> &P) {
        _heap.push_back(-1);

        for (size_t i = 0; i < P.size(); i++)
            _heap.push_back(P[i]);

        for (size_t i = floor(P.size()/2); i >= 1; i--) {
            bubbleDown(i);
        }
    }

    int heapExtractMin(void) {
        int min = _heap[ROOT];
        std::swap(_heap[ROOT], _heap[_heap.size()-1]);
        _heap.erase(_heap.end()-1);
        bubbleDown(ROOT);
        return min;
    }

    void heapInsert(int u) {
        _heap.push_back(u);
        bubbleUp(_heap.size()-1);
    }

    std::vector<int> heapSort(void) {
        std::vector<int> result;
        size_t n = _heap.size();
        std::vector<int> cache = _heap;

        for (size_t i = 1; i < n; i++)
            result.push_back(heapExtractMin());

        _heap = cache;
        return result;
    }

private:
    size_t ROOT = 1;
    size_t NO_SONS = 0;
    std::vector<int> _heap;

    size_t parent(size_t index) const {
        return floor(index/2);
    }

    bool hasBothSons(size_t index) const {
        return (2 * index + 1) < _heap.size();
    }

    bool hasLeftSon(size_t index) const {
        return 2 * index < _heap.size();
    }

    size_t leftSon(size_t index) const {
        return index * 2;
    }

    size_t rightSon(size_t index) const {
        return index * 2 + 1;
    }

    size_t son(size_t index) const {
        if (hasBothSons(index)) {
            return _heap[leftSon(index)] <= _heap[rightSon(index)] ? leftSon(index) : rightSon(index);
        } else if (hasLeftSon(index)) {
            return leftSon(index);
        }
        return NO_SONS;
    }

    void bubbleDown(size_t index) {
        size_t p = index;
        size_t s = son(index);

        if (s == NO_SONS || _heap[p] <= _heap[s])
            return;

        std::swap(_heap[p], _heap[s]);
        bubbleDown(s);
    }

    void bubbleUp(size_t index) {
        if (index == ROOT) return;
        size_t p = parent(index);

        if (_heap[p] <= _heap[index])
            return;

        std::swap(_heap[p], _heap[index]);
        bubbleUp(p);
    }
};

std::ostream& operator << (std::ostream &out, const std::vector<int> &P) {
    for (size_t i = 0; i < P.size(); i++)
        out << P[i] << (i + 1 == P.size() ? "" : ", ");
    return out;
}

int main(void) {
    Heap h;
    h.heapBuild({1, 5, 7, 2, 9, 4});
    std::cout << h.heapSort() << std::endl;
    h.heapInsert(8);
    h.heapInsert(6);
    h.heapInsert(3);
    std::cout << h.heapSort() << std::endl;
    return EXIT_SUCCESS;
}