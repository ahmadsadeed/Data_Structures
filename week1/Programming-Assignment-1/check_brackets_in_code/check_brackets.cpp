#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Bracket {
    Bracket(char type, int position):
    type(type),
    position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];
        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket
            opening_brackets_stack.push(Bracket(next, position + 1));
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket
            if (opening_brackets_stack.empty()) {
                opening_brackets_stack.push(Bracket(next, position + 1));
                break;
            }
            Bracket bracket = opening_brackets_stack.top();
            if (bracket.Matchc(next)) {
                opening_brackets_stack.pop();
            } else {
                opening_brackets_stack.push(Bracket(next, position + 1));
                break;
            }
        }
    }

    // Printing answer, write your code here
    if (opening_brackets_stack.empty()) {
        cout << "Success" << endl;
    } else  {
        cout << opening_brackets_stack.top().position << endl;
    }

    return 0;
}


