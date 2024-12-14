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

class HashTable {
public:
    HashTable(int size) {
        m_HashTable.resize(size, -2);
    }

    void openInsert(int x) {
        for (size_t i = 0; i < m_HashTable.size(); i++) {
            int h = hash(x,i);
            if (m_HashTable[h] == -2 || m_HashTable[h] == -1) {
                m_HashTable[h] = x;
                return;
            } 
        }
    }

    void openDelete(int x) {
        for (size_t i = 0; i < m_HashTable.size(); i++) {
            int h = hash(x,i);
            if (m_HashTable[h] == x) {
                m_HashTable[h] = -1;
                return;
            } 
        }
    }

    void printTable() const {
        for (const auto &e: m_HashTable) {
            if (e == -2) {
                std::cout << "-,";
            } else if (e == -1) {
                std::cout << "t,";
            } else {
                std::cout << e << ",";
            }
        }
        std::cout << "\n";
    }

private:
    std::vector<int> m_HashTable;

    int hash(int k, int i) const {
        int hash = (6*k+i*((3*k)%5+1))%m_HashTable.size();
        return hash;
    }
};

int main(void)
{
    HashTable h(13);
    h.openInsert(12);
    h.openInsert(64);
    h.openInsert(32);
    h.openInsert(38);
    h.openInsert(44);
    h.openInsert(26);

    h.openDelete(32);
    h.openDelete(12);

    h.openInsert(31);
    h.openInsert(13);

    h.printTable();
    return EXIT_SUCCESS;
}