#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}


size_t hash_func(const string& s, const size_t prime, const size_t multiplier) {
    ull hash = 0;
    for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
        hash = (hash * multiplier + s[i]) % prime;
    return (hash + prime) % prime;
}

vector<int> precomputeHashes(const Data& input, const size_t prime, const size_t multiplier) {
    const string& s = input.pattern, t = input.text;
    size_t textSize = input.text.size();
    size_t patternSize = input.pattern.size();
    vector<int> indexes(textSize - patternSize + 1, 0);
    string S = input.text.substr(textSize - patternSize, textSize - 1);
    indexes[textSize-patternSize] = (int)hash_func(S, prime, multiplier);

    ull y = 1;
    for (int i = 1; i <= patternSize; i++) {
        y = (y * multiplier) % prime;
    }
    for (int i = textSize-patternSize-1; i >= 0; i--) {
        indexes[i] = (multiplier * indexes[i+1] + t[i] - y * t[i + patternSize]) % prime;
    }
    return indexes;
}

vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    static const size_t prime = 1000000007;
    srand(static_cast <unsigned int> (time(0)));
    static const size_t multiplier = (rand() % static_cast<int>(prime - 0 + 1));

    vector<int> hashes =  precomputeHashes(input, prime, multiplier);
    ull patternHash = hash_func(s, prime, multiplier);

    vector<int> ans;
    if (s.size() == t.size()) {
        if (patternHash != hashes[0]) {
            if (t == s) {
                ans.push_back(0);
            }
        }
    }
    for (int i = 0; i <= t.size() - s.size(); i++) {
        if (patternHash != hashes[i]) {
            continue;
        }
        //        cout << "pattern is: " << s<< " and hash: " << patternHash << endl;
        //        cout << "text is: " << t.substr(i, s.size() - 1) << " and hash: " << hashes[i] << endl;
        if (t.substr(i, s.size()) == s) {
            ans.push_back(i);
        }
    }
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}


