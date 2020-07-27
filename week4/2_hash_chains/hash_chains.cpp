#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector of unordered sets. Won't maintain insertion order
    vector<unordered_set<string>> sets;

    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return (hash % bucket_count + bucket_count) % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
        sets.resize(bucket_count);
    }

    static Query readQuery() {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    static void writeSearchResult(bool was_found) {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            unordered_set<string> & theSet = sets[query.ind];
            for (const string& s : theSet) {
                std::cout << s << " ";
            }
            std::cout << "\n";

        } else {
            unsigned long long hashVal = hash_func(query.s);
            unordered_set<string> & theSet = sets[hashVal];
            auto iter = theSet.find(query.s);
            if (query.type == "find")
                writeSearchResult(iter != theSet.end());
            else if (query.type == "add") {
                if (iter == theSet.end()) {
                    auto iterBegin = theSet.begin();
                    theSet.emplace_hint(iterBegin, query.s);
                }
            } else if (query.type == "del") {
                if (iter != theSet.end())
                    theSet.erase(iter);
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
// This won't pass the assignment. Unlike Python, C++ maps or sets don't keep insertion order
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
/*
 5
 12
 add world
 add HellO
 check 4
 find World
 find world
 del world
 check 4
 del HellO
 add luck
 add GooD
 check 2
 del good
 */


