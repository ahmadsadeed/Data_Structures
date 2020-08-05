#include <algorithm>
#include <iostream>
#include <map>

#if defined(__unix__) || defined(__APPLE__)

#include <sys/resource.h>

#endif

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

int main_with_large_stack_space() {
    ios_base::sync_with_stdio(false);
    int nodes;
    cin >> nodes;
    map<int, Node> tree;
    int min = std::numeric_limits<int>::min();
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

int main(int argc, char **argv) {
#if defined(__unix__) || defined(__APPLE__)
    // Allow larger stack space
    const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0) {
        if (rl.rlim_cur < kStackSize) {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0) {
                std::cerr << "setrlimit returned result = " << result << std::endl;
            }
        }
    }
#endif

    return main_with_large_stack_space();
}
