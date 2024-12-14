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

// We use std::vector as a reference to check our implementation.
// It is not available in progtest :)
#include <vector>

template <typename T>
struct Ref
{
    bool empty() const { return _data.empty(); }
    size_t size() const { return _data.size(); }

    const T &operator[](size_t index) const { return _data.at(index); }
    T &operator[](size_t index) { return _data.at(index); }

    void insert(size_t index, T value)
    {
        if (index > _data.size())
            throw std::out_of_range("oops");
        _data.insert(_data.begin() + index, std::move(value));
    }

    T erase(size_t index)
    {
        T ret = std::move(_data.at(index));
        _data.erase(_data.begin() + index);
        return ret;
    }

    auto begin() const { return _data.begin(); }
    auto end() const { return _data.end(); }

private:
    std::vector<T> _data;
};

#endif

namespace config
{
    inline constexpr bool PARENT_POINTERS = true;
    inline constexpr bool CHECK_DEPTH = true;
}

// TODO implement
template <typename T>
struct Array
{
    Array()
        : root(nullptr), nodes_total(0)
    {
    }

    ~Array()
    {
        delete_tree(root);
    }

    struct Node
    {
        T value;
        size_t index;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *parent = nullptr;
        int height = 0;
        Node(T _value, size_t _index, Node *_parent, int _height)
            : value(_value), index(_index), parent(_parent), height(_height)
        {
        }
    };

    bool empty() const
    {
        return nodes_total == 0;
    }

    size_t size() const
    {
        return nodes_total;
    }

    const T &operator[](size_t index) const
    {
        if (index < 0 || index > nodes_total)
            throw std::out_of_range("Out of range!");

        Node *node = find_by_index(root, index);
        if (node == nullptr)
            throw std::out_of_range("Out of range!");

        return node->value;
    }

    T &operator[](size_t index)
    {
        if (index < 0 || index > nodes_total)
            throw std::out_of_range("Out of range!");

        Node *node = find_by_index(root, index);
        if (node == nullptr)
            throw std::out_of_range("Out of range!");

        return node->value;
    }

    void insert(size_t index, T value)
    {
        if (index < 0 || index > nodes_total)
            throw std::out_of_range("Out of range!");

        Node *check = find_by_index(root, index);
        if (check != nullptr) {
            if (check->index > root->index)
                update_indexes_insert(root->right, index);
            else
                update_indexes_insert(root, index);
        }

        Node *tmp = insert_node(root, index, value);
        nodes_total++;
        root = tmp;
    }

    T erase(size_t index)
    {
        if (index < 0 || index > nodes_total)
            throw std::out_of_range("Out of range!");

        Node *node = find_by_index(root, index);
        if (node == nullptr)
            throw std::out_of_range("Out of range!");

        T value = node->value;
        root = erase_node(root, index);
        update_indexes_erase(root, index);
        nodes_total--;
        return value;
    }

    Node *find_by_index(Node *node, size_t index) const
    {
        if (node == nullptr)
            return nullptr;
        if (node->index == index)
            return node;
        return (index < node->index) ? find_by_index(node->left, index) : find_by_index(node->right, index);
    }

    void update_indexes_insert(Node *node, size_t index)
    {
        if (node == nullptr)
            return;
        if (node->index >= index) {
            node->index++;
            update_indexes_insert(node->left, index);
        }
        update_indexes_insert(node->right, index);
    }

    void update_indexes_erase(Node *node, size_t index)
    {
        if (node == nullptr)
            return;
        if (node->index >= index)
            node->index--;
        update_indexes_erase(node->left, index);
        update_indexes_erase(node->right, index);
    }

    Node *min(Node *node)
    {
        if (node->left == nullptr)
            return node;
        return min(node->left);
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

    Node *insert_node(Node *node, size_t index, T value, Node *parent = nullptr)
    {
        if (!node)
        {
            Node *new_node = new Node(value, index, parent, 1);
            return new_node;
        }

        if (index < node->index)
            node->left = insert_node(node->left, index, value, node);
        else if (index > node->index)
            node->right = insert_node(node->right, index, value, node);
        else if (index == node->index)
            return node;

        return balance(node);
    }

    Node *erase_node(Node *node, size_t index)
    {
        if (!node)
            return node;

        if (index < node->index)
        {
            node->left = erase_node(node->left, index);
            if (node->left)
                node->left->parent = node;
        }
        else if (index > node->index)
        {
            node->right = erase_node(node->right, index);
            if (node->right)
                node->right->parent = node;
        }
        else if (index == node->index)
        {
            // Node with one or no children
            if (node->left == nullptr || node->right == nullptr)
            {
                Node *tmp = node->left ? node->left : node->right;
                delete node;
                return tmp;
            }

            // Node with two children
            Node *tmp = min(node->right);
            node->index = tmp->index;
            node->value = tmp->value;
            node->right = erase_node(node->right, tmp->index);
            if (node->right)
                node->right->parent = node;
        }

        if (node == nullptr)
            return nullptr;

        return balance(node);
    }

    Node *balance(Node *node)
    {
        node->height = 1 + max(height(node->left), height(node->right));
        int balance = get_balance(node);

        if (balance > 1 && get_balance(node->left) >= 0)
            return right_rotation(node);

        if (balance > 1 && get_balance(node->left) < 0)
        {
            node->left = left_rotation(node->left);
            return right_rotation(node);
        }

        if (balance < -1 && get_balance(node->right) <= 0)
            return left_rotation(node);

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

    struct TesterInterface
    {
        static const Node *root(const Array *t) { return t->root; }
        static const Node *parent(const Node *n) { return n->parent; }
        static const Node *right(const Node *n) { return n->right; }
        static const Node *left(const Node *n) { return n->left; }
        static const T &value(const Node *n) { return n->value; }
    };

    Node *root;
    size_t nodes_total;
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

    size_t size() const
    {
        bool te = tested.empty();
        size_t r = ref.size();
        size_t t = tested.size();
        if (te != !t)
            throw TestFailed(fmt("Size: size %zu but empty is %s.",
                                 t, te ? "true" : "false"));
        if (r != t)
            throw TestFailed(fmt("Size: got %zu but expected %zu.", t, r));
        return r;
    }

    const T &operator[](size_t index) const
    {
        const T &r = ref[index];
        const T &t = tested[index];
        if (r != t)
            throw TestFailed("Op [] const mismatch.");
        return t;
    }

    void assign(size_t index, T x)
    {
        ref[index] = x;
        tested[index] = std::move(x);
        operator[](index);
    }

    void insert(size_t i, T x, bool check_tree_ = false)
    {
        ref.insert(i, x);
        tested.insert(i, std::move(x));
        size();
        if (check_tree_)
            check_tree();
    }

    T erase(size_t i, bool check_tree_ = false)
    {
        T r = ref.erase(i);
        T t = tested.erase(i);
        if (r != t)
        {
            std::cout << r << " vs " << t << std::endl;
            throw TestFailed(fmt("Erase mismatch at %zu.", i));
        }
        size();
        if (check_tree_)
            check_tree();
        return t;
    }

    void check_tree() const
    {
        using TI = typename Array<T>::TesterInterface;
        auto ref_it = ref.begin();
        bool check_value_failed = false;
        auto check_value = [&](const T &v)
        {
            if (check_value_failed)
                return;
            check_value_failed = (ref_it == ref.end() || *ref_it != v);
            // std::cout << *ref_it << " " << v << std::endl;
            if (!check_value_failed)
                ++ref_it;
        };

        size();

        check_node(TI::root(&tested), decltype(TI::root(&tested))(nullptr), check_value);

        if (check_value_failed)
            throw TestFailed(
                "Check tree: element mismatch");
    }

    template <typename Node, typename F>
    int check_node(const Node *n, const Node *p, F &check_value) const
    {
        if (!n)
            return -1;

        using TI = typename Array<T>::TesterInterface;
        if constexpr (config::PARENT_POINTERS)
        {
            if (TI::parent(n) != p)
                throw TestFailed("Parent mismatch.");
        }

        auto l_depth = check_node(TI::left(n), n, check_value);
        check_value(TI::value(n));
        auto r_depth = check_node(TI::right(n), n, check_value);

        if (config::CHECK_DEPTH && abs(l_depth - r_depth) > 1)
            throw TestFailed(fmt(
                "Tree is not avl balanced: left depth %i and right depth %i.",
                l_depth, r_depth));

        return std::max(l_depth, r_depth) + 1;
    }

    static void _throw(const char *msg, bool s)
    {
        throw TestFailed(fmt("%s: ref %s.", msg, s ? "succeeded" : "failed"));
    }

    Array<T> tested;
    Ref<T> ref;
};

void test_insert()
{
    Tester<int> t;

    for (int i = 0; i < 10; i++)
        t.insert(i, i, true);
    for (int i = 0; i < 10; i++)
        t.insert(i, -i, true);
    for (size_t i = 0; i < t.size(); i++)
        t[i];

    for (int i = 0; i < 5; i++)
        t.insert(15, (1 + i * 7) % 17, true);
    for (int i = 0; i < 10; i++)
        t.assign(2 * i, 3 * t[2 * i]);
    for (size_t i = 0; i < t.size(); i++)
        t[i];
}

void test_erase()
{
    Tester<int> t;

    for (int i = 0; i < 10; i++)
        t.insert(i, i, true);
    for (int i = 0; i < 10; i++)
        t.insert(i, -i, true);

    for (size_t i = 3; i < t.size(); i += 2)
        t.erase(i, true);
    for (size_t i = 0; i < t.size(); i++)
        t[i];

    for (int i = 0; i < 5; i++)
        t.insert(3, (1 + i * 7) % 17, true);
    for (size_t i = 1; i < t.size(); i += 3)
        t.erase(i, true);

    for (int i = 0; i < 20; i++)
        t.insert(3, 100 + i, true);

    for (int i = 0; i < 5; i++)
        t.erase(t.size() - 1, true);
    for (int i = 0; i < 5; i++)
        t.erase(0, true);

    for (int i = 0; i < 4; i++)
        t.insert(i, i, true);
    for (size_t i = 0; i < t.size(); i++)
        t[i];
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
    {
        size_t pos = seq ? 0 : my_rand() % (i + 1);
        t.insert(pos, my_rand() % (3 * size), check_tree);
    }

    t.check_tree();

    for (size_t i = 0; i < t.size(); i++)
        t[i];

    for (size_t i = 0; i < 30 * size; i++)
        switch (my_rand() % 7)
        {
        case 1:
        {
            if (!erase && i % 3 == 0)
                break;
            size_t pos = seq ? 0 : my_rand() % (t.size() + 1);
            t.insert(pos, my_rand() % 1'000'000, check_tree);
            break;
        }
        case 2:
            if (erase)
                t.erase(my_rand() % t.size(), check_tree);
            break;
        case 3:
            t.assign(my_rand() % t.size(), 155 + i);
            break;
        default:
            t[my_rand() % t.size()];
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

        std::cout << "Bigger random test..." << std::endl;
        test_random(5'000);

        std::cout << "Bigger sequential test..." << std::endl;
        test_random(5'000, SEQ);

        std::cout << "All tests passed." << std::endl;
    }
    catch (const TestFailed &e)
    {
        std::cout << "Test failed: " << e.what() << std::endl;
    }
}

#endif
