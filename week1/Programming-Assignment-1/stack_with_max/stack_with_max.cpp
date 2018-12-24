#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <stack>

using std::cin;
using std::string;
using std::vector;
using std::cout;
using std::max_element;

class StackWithMax {
    std::stack<int> stack;
    std::stack<int> maxInStack;

public:

    void Push(int value) {
        stack.push(value);
        // check if it is the first element
        if (stack.size() == 1) {
            maxInStack.push(value);
            return;
        }

        if (value > maxInStack.top()) {
            maxInStack.push(value);
        } else {
            maxInStack.push(maxInStack.top());
        }
    }

    void Pop() {
        assert(stack.size());
        stack.pop();
        maxInStack.pop();
    }

    int Max() const {
        assert(stack.size());
        return maxInStack.top();
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(std::stoi(value));
        }
        else if (query == "pop") {
            stack.Pop();
        }
        else if (query == "max") {
            cout << stack.Max() << "\n";
        }
        else {
            assert(0);
        }
    }
    return 0;
}

