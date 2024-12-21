#include <cassert>
#include <iomanip>
#include <cstdint>
#include <iostream>
#include <memory>
#include <limits>
#include <optional>
#include <algorithm>
#include <map>
#include <random>
#include <type_traits>
#include <compare>

std::map<int, int> vertices;

int avlMinVertices(int h) {
    if (vertices.find(h) != vertices.end())
        return vertices.at(h);

    if (h == 1) vertices[h] = 1;
    else if (h == 2) vertices[h] = 2;
    else vertices[h] = avlMinVertices(h-1) + avlMinVertices(h-2) + 1;

    return vertices.at(h);
}

int avlMaxVertices(int h) {
    return pow(2, h)-1;
}

void avlMinMaxVertices(int h) {
    std::cout << "Min: " << avlMinVertices(h) << std::endl;
    std::cout << "Max: " << avlMaxVertices(h) << std::endl;
}
 
int main(void) {
    int h;
    std::cout << "Zadejte počet hladin: " << std::endl;
    std::cin >> h;

    if (!std::cin.good()) 
        return EXIT_FAILURE;

    avlMinMaxVertices(h);
    return EXIT_SUCCESS;
}