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

int fibRec(int n) {
    if (n <= 2) return 1;
    return fibRec(n-1) + fibRec(n-2);
}

std::map<int, int> fib;

int fibMem(int n) {
    if (fib.find(n) != fib.end())
        return fib.at(n);

    if (n <= 2) fib[n] = 1;
    else fib[n] = fibMem(n-1) + fibMem(n-2);

    return fib.at(n);
}
 
int main(void) {
    int n;
    std::cin >> n;

    if (!std::cin.good()) 
        return EXIT_FAILURE;

    std::cout << n << "-th fibonacci number is: " << fibMem(n) << std::endl;
    return EXIT_SUCCESS;
}