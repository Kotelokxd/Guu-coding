#include <iostream>
#include <string>
using namespace std;

template <typename T>
class BinaryTree {
private:
    struct Node {
        T value;
        Node* left;
        Node* right;
        Node(T v) : value(v), left(nullptr), right(nullptr) {}
    };
    Node* root;

    Node* insert(Node* node, T v) {
        if (!node) return new Node(v);
        if (v < node->value)
            node->left = insert(node->left, v);
        else if (v > node->value)
            node->right = insert(node->right, v);
        return node;
    }

    bool find(Node* node, T v) const {
        if (!node) return false;
        if (v == node->value) return true;
        if (v < node->value) return find(node->left, v);
        return find(node->right, v);
    }

    Node* remove(Node* node, T v) {
        if (!node) return nullptr;
        if (v < node->value)
            node->left = remove(node->left, v);
        else if (v > node->value)
            node->right = remove(node->right, v);
        else {
            if (!node->left) {
                auto temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right) {
                auto temp = node->left;
                delete node;
                return temp;
            }
            auto min = node->right;
            while (min->left) min = min->left;
            node->value = min->value;
            node->right = remove(node->right, min->value);
        }
        return node;
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    string toString(Node* node) const {
        if (!node) return "";
        string s = toString(node->left);
        if (!s.empty()) s += " ";
        s += std::to_string(node->value);
        string right = toString(node->right);
        if (!right.empty()) s += " " + right;
        return s;
    }

    void printInOrder(Node* node, ostream& os) const {
        if (!node) return;
        printInOrder(node->left, os);
        os << node->value << " ";
        printInOrder(node->right, os);
    }

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { clear(); }

    void insert(T value) { root = insert(root, value); }
    bool find(T value) const { return find(root, value); }
    void remove(T value) { root = remove(root, value); }
    void clear() { clear(root); root = nullptr; }
    string toString() const { return toString(root); }

    friend ostream& operator<<(ostream& os, const BinaryTree& tree) {
        tree.printInOrder(tree.root, os);
        return os;
    }

    friend istream& operator>>(istream& is, BinaryTree& tree) {
        tree.clear();
        string line;
        if (!getline(is, line)) return is;

        size_t i = 0;
        while (i < line.size()) {
            while (i < line.size() && line[i] == ' ') ++i;
            if (i == line.size()) break;

            int val = 0;
            bool neg = false;
            if (i < line.size() && line[i] == '-') { neg = true; ++i; }
            while (i < line.size() && line[i] >= '0' && line[i] <= '9') {
                val = val * 10 + (line[i] - '0');
                ++i;
            }
            if (neg) val = -val;

            tree.insert(val);
        }
        return is;
    }
};

template <typename T>
void BinaryTree<T>::clear() {
    clear(root);
    root = nullptr;
}

int main() {
    BinaryTree<int> tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "Дерево: " << tree << "\n";
    cout << "toString: " << tree.toString() << "\n\n";

    cout << "Есть 40? " << (tree.find(40) ? "Да" : "Нет") << "\n";
    cout << "Есть 55? " << (tree.find(55) ? "Да" : "Нет") << "\n\n";

    tree.remove(30);
    cout << "После удаления 30: " << tree << "\n";

    cout << "\nВведите числа через пробел (например: 5 3 8 1 4):\n";
    BinaryTree<int> tree2;
    cin >> tree2;
    cout << "Прочитано: " << tree2 << "\n";

    return 0;
}
