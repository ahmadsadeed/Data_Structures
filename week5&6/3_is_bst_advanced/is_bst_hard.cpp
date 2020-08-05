#include <algorithm>
#include <iostream>
#include <map>


using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::ios_base;

struct Node {
    int key;
    int left;
    int right;

    Node() : key(0), left(-1), right(-1) {}

    Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool IsBinarySearchTree( map<int, Node> &tree, const int node, const int min, const int max) {
    if (tree.find(node) == tree.end())
        return true;
    if ((tree[node].key < min) || (tree[node].key > max))
        return false;
    return IsBinarySearchTree(tree, tree[node].left, min, tree[node].key - 1) &&
    IsBinarySearchTree(tree, tree[node].right, tree[node].key, max);
}

int main() {
//    ios_base::sync_with_stdio(false);
    int nodes;
    cin >> nodes;
    map<int, Node> tree;
    int min = -1;
    int max = std::numeric_limits<int>::max();
    for (int i = 0; i < nodes; ++i) {
        int key, left, right;
        cin >> key >> left >> right;
        tree[i] = Node(key, left, right);
    }
    if (IsBinarySearchTree(tree, 0, min, max)) {
        cout << "CORRECT" << endl;
    } else {
        cout << "INCORRECT" << endl;
    }
    return 0;
}

