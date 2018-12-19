#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
        this->parent = NULL;
    }

    void setParent(Node *theParent) {
        parent = theParent;
        parent->children.push_back(this);
    }
};

int getHeight(Node &node){
// to print in order
//    for (int i = 0; i < node.children.size(); i++) {
//        getHeight(*node.children[i]);
//    }
    // 0  1 2 3 4 5 6 7 8 9 10
    // 4 -1 4 1 1 3 5 6 7 8
    // 4 -1 4 1 1 1 5 6 7 8
    // -1 0 4 0 3
    if (node.children.size() > 0) {
        vector<int> v;
        for (int i = 0; i < node.children.size(); i++) {
            int max = getHeight(*node.children[i]);
            v.push_back(max);
        }
        sort(v.begin(), v.end());

        return 1 + v[v.size()-1];
    } else if (node.children.size() == 0) {
        return 0;
    }
    return 0;
}


int main_with_large_stack_space() {
    std::ios_base::sync_with_stdio(0);
    int n;
    std::cin >> n;
    std::vector<Node> nodes;
    nodes.resize(n);
    int root = -1;
    for (int child_index = 0; child_index < n; child_index++) {
        int parent_index;
        std::cin >> parent_index;
        if (parent_index >= 0)
            nodes[child_index].setParent(&nodes[parent_index]);
        else root = child_index;
        nodes[child_index].key = child_index;
    }

    int maxHeight = 1 + getHeight(nodes[root]);
    std::cout << maxHeight << std::endl;
    return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
    // Allow larger stack space
    const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                std::cerr << "setrlimit returned result = " << result << std::endl;
            }
        }
    }

#endif
    return main_with_large_stack_space();
}


