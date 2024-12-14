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

struct Node {
    int val;
    std::shared_ptr<Node> left = nullptr;
    std::shared_ptr<Node> right = nullptr;

    Node(int _val)
        : val(_val)
    {}
};

class BVS {
public:
    BVS()
        : root(nullptr)
    {}

    bool insert_node(int val) {
        if (find(val, root)) return false;
        root = insert_node(val, root);
        return true;
    }

    bool delete_node(int val) {
        if (!find(val, root)) return false;
        root = delete_node(val, root);
        return true;
    }

    bool find(int val) const {
        return find(val, root);
    }

    bool find(int val, std::shared_ptr<Node> node) const {
        if (empty()) return false;
        if (val == node->val) return true;
        if (node->left && val < node->val) return find(val, node->left);
        if (node->right && val > node->val) return find(val, node->right);
        return false;
    }

    void print(void) const {
        int last = max(root);
        std::cout << "{";
        show(root, last);
        std::cout << "}\n";
    }

    int min(std::shared_ptr<Node> node) const {
        if (!node->left) return node->val;
        return min(node->left);
    }

    int max(std::shared_ptr<Node> node) const {
        if (!node->right) return node->val;
        return max(node->right);
    }

private:
    std::shared_ptr<Node> root;

    bool empty(void) const {
        return root == nullptr;
    }

    std::shared_ptr<Node> insert_node(int val, std::shared_ptr<Node> node) {
        if (!node) {
            node = std::make_shared<Node>(val);
            return node;
        }

        if (val < node->val) {
            node->left = insert_node(val, node->left);
            return node;
        } else if (val > node->val) {
            node->right = insert_node(val, node->right);
            return node;
        }

        return node;
    }

    std::shared_ptr<Node> delete_node(int val, std::shared_ptr<Node> node) {
        if (val == node->val) {
            if (!node->left && !node->right) {
                return nullptr;
            } else if (node->left && !node->right) {
                return node->left;
            } else if (!node->left && node->right) {
                return node->right;
            } else {
                int succ = min(node->right);
                node->val = succ;
                node->right = delete_node(succ, node->right);
                return node;
            }
        } else if (val < node->val) {
            node->left = delete_node(val, node->left);
            return node;
        } else if (val > node->val) {
            node->right = delete_node(val, node->right);
            return node;
        }

        return node;
    }

    void show(std::shared_ptr<Node> node, int last) const {
        if (!node) return;
        if (node->left) show(node->left, last);
        std::cout << node->val << (node->val != last ? ", " : "");
        if (node->right) show(node->right, last);
    }
};

int main(void) {
    BVS bvs;
    assert(bvs.insert_node(7) == true);
    assert(bvs.insert_node(3) == true);
    assert(bvs.insert_node(2) == true);
    assert(bvs.insert_node(5) == true);
    assert(bvs.insert_node(4) == true);
    assert(bvs.insert_node(7) == false);
    assert(bvs.insert_node(6) == true);
    assert(bvs.insert_node(1) == true);
    bvs.print();

    for (int i = 1; i < 8; i++)
        assert(bvs.find(i) == true);

    assert(bvs.delete_node(1) == true);
    assert(bvs.delete_node(1) == false);
    bvs.print();
    return EXIT_SUCCESS;
}