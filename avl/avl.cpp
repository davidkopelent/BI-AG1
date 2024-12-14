#ifndef __PROGTEST__
#include <cassert>
#include <cstdarg>
#include <iomanip>
#include <cstdint>
#include <iostream>
#include <memory>
#include <limits>
#include <optional>
#include <array>
#include <random>
#include <type_traits>

// We use std::set as a reference to check our implementation.
// It is not available in progtest :)
#include <set>

template <typename T>
struct Ref
{
    size_t size() const { return _data.size(); }

    const T *find(const T &value) const
    {
        auto it = _data.find(value);
        if (it == _data.end())
            return nullptr;
        return &*it;
    }

    bool insert(const T &value) { return _data.insert(value).second; }

    bool erase(const T &value) { return _data.erase(value); }

    auto begin() const { return _data.begin(); }

    auto end() const { return _data.end(); }

private:
    std::set<T> _data;
};

#endif

namespace config
{
    // Enable to check that the tree is AVL balanced.
    inline constexpr bool CHECK_DEPTH = true;

    // Disable if your implementation does not have parent pointers
    inline constexpr bool PARENT_POINTERS = true;
}

// TODO implement
template <typename T>
struct Tree
{
    ~Tree()
    {
        delete_tree(root);
    }

    struct Node
    {
        T value;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *parent = nullptr;
        int height = 0;
    };

    Node *root = nullptr;
    size_t nodes_total = 0;

    size_t size() const
    {
        return nodes_total;
    }

    const T *find(const T &value) const
    {
        Node *node = find_node(root, value);
        return node ? &node->value : nullptr;
    }

    bool insert(T value)
    {
        size_t current_size = nodes_total;

        Node *tmp = insert_node(root, value);
        if (current_size == nodes_total)
            return false;

        root = tmp;
        return true;
    }

    bool erase(const T &value)
    {
        if (find_node(root, value) == nullptr)
            return false;

        root = erase_node(root, value);
        nodes_total--;
        return true;
    }

    Node *find_node(Node *node, const T &value) const
    {
        if (node == nullptr)
            return nullptr;
        if (node->value == value)
            return node;
        return (value < node->value) ? find_node(node->left, value) : find_node(node->right, value);
    }

    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    int height(Node *node)
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int get_balance(Node *node)
    {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    Node *left_rotation(Node *x)
    {
        Node *y = x->right;
        Node *T1 = y->left;

        y->left = x;
        x->right = T1;

        if (T1)
            T1->parent = x;
        y->parent = x->parent;
        x->parent = y;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node *right_rotation(Node *y)
    {
        Node *x = y->left;
        Node *T1 = x->right;

        x->right = y;
        y->left = T1;

        if (T1)
            T1->parent = y;
        x->parent = y->parent;
        y->parent = x;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node *insert_node(Node *node, T value, Node *parent = nullptr)
    {
        if (!node)
        {
            Node *new_node = new Node();
            new_node->value = value;
            new_node->height = 1;
            new_node->parent = parent;
            nodes_total++;
            return new_node;
        }

        if (value < node->value)
        {
            node->left = insert_node(node->left, value, node);
        }
        else if (value > node->value)
        {
            node->right = insert_node(node->right, value, node);
        }
        else
        {
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = get_balance(node);

        if (balance > 1 && value < node->left->value)
        {
            return right_rotation(node);
        }
        if (balance < -1 && value > node->right->value)
        {
            return left_rotation(node);
        }
        if (balance > 1 && value > node->left->value)
        {
            node->left = left_rotation(node->left);
            return right_rotation(node);
        }
        if (balance < -1 && value < node->right->value)
        {
            node->right = right_rotation(node->right);
            return left_rotation(node);
        }

        return node;
    }

    Node *avl_min(Node *node)
    {
        if (node->left == nullptr)
            return node;
        return avl_min(node->left);
    }

    Node *erase_node(Node *node, T value)
    {
        if (!node)
            return node;

        if (value < node->value)
        {
            node->left = erase_node(node->left, value);
            if (node->left)
                node->left->parent = node;
        }
        else if (value > node->value)
        {
            node->right = erase_node(node->right, value);
            if (node->right)
                node->right->parent = node;
        }
        else
        {
            if (!node->left || !node->right)
            {
                Node *temp = node->left ? node->left : node->right;

                if (!temp)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                {
                    *node = *temp;
                }
                delete temp;
            }
            else
            {
                Node *temp = avl_min(node->right);
                node->value = temp->value;
                node->right = erase_node(node->right, temp->value);
                if (node->right)
                    node->right->parent = node;
            }
        }

        if (!node)
            return node;

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = get_balance(node);

        if (balance > 1 && get_balance(node->left) >= 0)
        {
            return right_rotation(node);
        }
        if (balance > 1 && get_balance(node->left) < 0)
        {
            node->left = left_rotation(node->left);
            return right_rotation(node);
        }
        if (balance < -1 && get_balance(node->right) <= 0)
        {
            return left_rotation(node);
        }
        if (balance < -1 && get_balance(node->right) > 0)
        {
            node->right = right_rotation(node->right);
            return left_rotation(node);
        }

        return node;
    }

    void delete_tree(Node *root)
    {
        if (root->left != nullptr)
            delete_tree(root->left);
        if (root->right != nullptr)
            delete_tree(root->right);
        delete root;
    }

    // Needed to test the structure of the tree.
    // Replace Node with the real type of your nodes
    // and implementations with the ones matching
    // your attributes.
    struct TesterInterface
    {
        // using Node = ...
        static const Node *root(const Tree *t) { return t->root; }
        // Parent of root must be nullptr, ignore if config::PARENT_POINTERS == false
        static const Node *parent(const Node *n) { return n->parent; }
        static const Node *right(const Node *n) { return n->right; }
        static const Node *left(const Node *n) { return n->left; }
        static const T &value(const Node *n) { return n->value; }
    };
};

#ifndef __PROGTEST__

struct TestFailed : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

std::string fmt(const char *f, ...)
{
    va_list args1;
    va_list args2;
    va_start(args1, f);
    va_copy(args2, args1);

    std::string buf(vsnprintf(nullptr, 0, f, args1), '\0');
    va_end(args1);

    vsnprintf(buf.data(), buf.size() + 1, f, args2);
    va_end(args2);

    return buf;
}

template <typename T>
struct Tester
{
    Tester() = default;

    void size() const
    {
        size_t r = ref.size();
        size_t t = tested.size();
        if (r != t)
            throw TestFailed(fmt("Size: got %zu but expected %zu.", t, r));
    }

    void find(const T &x) const
    {
        auto r = ref.find(x);
        auto t = tested.find(x);
        bool found_r = r != nullptr;
        bool found_t = t != nullptr;

        if (found_r != found_t)
            _throw("Find mismatch", found_r);
        if (found_r && *t != x)
            throw TestFailed("Find: found different value");
    }

    void insert(const T &x, bool check_tree_ = false)
    {
        auto succ_r = ref.insert(x);
        auto succ_t = tested.insert(x);
        if (succ_r != succ_t)
            _throw("Insert mismatch", succ_r);
        size();
        if (check_tree_)
            check_tree();
    }

    void erase(const T &x, bool check_tree_ = false)
    {
        bool succ_r = ref.erase(x);
        auto succ_t = tested.erase(x);
        if (succ_r != succ_t)
            _throw("Erase mismatch", succ_r);
        size();
        if (check_tree_)
            check_tree();
    }

    struct NodeCheckResult
    {
        const T *min = nullptr;
        const T *max = nullptr;
        int depth = -1;
        size_t size = 0;
    };

    void check_tree() const
    {
        using TI = typename Tree<T>::TesterInterface;
        auto ref_it = ref.begin();
        bool check_value_failed = false;
        auto check_value = [&](const T &v)
        {
            if (check_value_failed)
                return;
            check_value_failed = (ref_it == ref.end() || *ref_it != v);
            if (!check_value_failed)
                ++ref_it;
        };

        auto r = check_node(TI::root(&tested), decltype(TI::root(&tested))(nullptr), check_value);
        size_t t_size = tested.size();

        if (t_size != r.size)
            throw TestFailed(
                fmt("Check tree: size() reports %zu but expected %zu.", t_size, r.size));

        if (check_value_failed)
            throw TestFailed(
                "Check tree: element mismatch");

        size();
    }

    template <typename Node, typename F>
    NodeCheckResult check_node(const Node *n, const Node *p, F &check_value) const
    {
        if (!n)
            return {};

        using TI = typename Tree<T>::TesterInterface;
        if constexpr (config::PARENT_POINTERS)
        {
            if (TI::parent(n) != p)
                throw TestFailed("Parent mismatch.");
        }

        auto l = check_node(TI::left(n), n, check_value);
        check_value(TI::value(n));
        auto r = check_node(TI::right(n), n, check_value);

        if (l.max && !(*l.max < TI::value(n)))
            throw TestFailed("Max of left subtree is too big.");
        if (r.min && !(TI::value(n) < *r.min))
            throw TestFailed("Min of right subtree is too small.");

        if (config::CHECK_DEPTH && abs(l.depth - r.depth) > 1)
            throw TestFailed(fmt(
                "Tree is not avl balanced: left depth %i and right depth %i.",
                l.depth, r.depth));

        return {
            l.min ? l.min : &TI::value(n),
            r.max ? r.max : &TI::value(n),
            std::max(l.depth, r.depth) + 1, 1 + l.size + r.size};
    }

    static void _throw(const char *msg, bool s)
    {
        throw TestFailed(fmt("%s: ref %s.", msg, s ? "succeeded" : "failed"));
    }

    Tree<T> tested;
    Ref<T> ref;
};

void test_insert()
{
    Tester<int> t;

    for (int i = 0; i < 10; i++)
        t.insert(i, true);
    for (int i = -10; i < 20; i++)
        t.find(i);

    for (int i = 0; i < 10; i++)
        t.insert((1 + i * 7) % 17, true);
    for (int i = -10; i < 20; i++)
        t.find(i);
}

void test_erase()
{
    Tester<int> t;

    for (int i = 0; i < 10; i++)
        t.insert((1 + i * 7) % 17, true);
    for (int i = -10; i < 20; i++)
        t.find(i);

    for (int i = 3; i < 22; i += 2)
        t.erase(i, true);
    for (int i = -10; i < 20; i++)
        t.find(i);

    for (int i = 0; i < 10; i++)
        t.insert((1 + i * 13) % 17 - 8, true);
    for (int i = -10; i < 20; i++)
        t.find(i);

    for (int i = -4; i < 10; i++)
        t.erase(i, true);
    for (int i = -10; i < 20; i++)
        t.find(i);
}

enum RandomTestFlags : unsigned
{
    SEQ = 1,
    NO_ERASE = 2,
    CHECK_TREE = 4
};

void test_random(size_t size, unsigned flags = 0)
{
    Tester<size_t> t;
    std::mt19937 my_rand(24707 + size);

    bool seq = flags & SEQ;
    bool erase = !(flags & NO_ERASE);
    bool check_tree = flags & CHECK_TREE;

    for (size_t i = 0; i < size; i++)
        t.insert(seq ? 2 * i : my_rand() % (3 * size), check_tree);

    t.check_tree();

    for (size_t i = 0; i < 3 * size + 1; i++)
        t.find(i);

    for (size_t i = 0; i < 30 * size; i++)
        switch (my_rand() % 5)
        {
        case 1:
            t.insert(my_rand() % (3 * size), check_tree);
            break;
        case 2:
            if (erase)
                t.erase(my_rand() % (3 * size), check_tree);
            break;
        default:
            t.find(my_rand() % (3 * size));
        }

    t.check_tree();
}

int main()
{
    try
    {
        std::cout << "Insert test..." << std::endl;
        test_insert();

        std::cout << "Erase test..." << std::endl;
        test_erase();

        std::cout << "Tiny random test..." << std::endl;
        test_random(20, CHECK_TREE);

        std::cout << "Small random test..." << std::endl;
        test_random(200, CHECK_TREE);

        std::cout << "Big random test..." << std::endl;
        test_random(50'000);

        std::cout << "Big sequential test..." << std::endl;
        test_random(50'000, SEQ);

        std::cout << "All tests passed." << std::endl;
    }
    catch (const TestFailed &e)
    {
        std::cout << "Test failed: " << e.what() << std::endl;
    }
}

#endif