#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // list of contacts
    map<int, string> contacts;
    map<int, string>::iterator found;
    for (size_t i = 0; i < queries.size(); ++i) {
        if (queries[i].type == "add") {
            bool was_founded = false;
            // if current in contacts, rewrite contact's name
            found = contacts.find(queries[i].number);
            if (found != contacts.end()) {
                found->second = queries[i].name;
                was_founded = true;
            }
            // otherwise, just add it
            if (!was_founded)
                contacts[queries[i].number] = queries[i].name;
        } else if (queries[i].type == "del") {
            found = contacts.find(queries[i].number);
            if (found != contacts.end()) {
                contacts.erase(found);
            }
        } else {
            string response = "not found";
            found = contacts.find(queries[i].number);
            if (found != contacts.end()) {
                response = found->second;
            }
            result.push_back(response);
        }
    }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}




