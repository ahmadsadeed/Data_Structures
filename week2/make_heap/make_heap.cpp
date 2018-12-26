#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
private:
    vector<int> data_;
    vector< pair<int, int> > swaps_;
    int dataSize = 0;
    int dataMaxSize = 0;

    void WriteResponse() const {
        cout << swaps_.size() << "\n";
        for (int i = 0; i < swaps_.size(); ++i) {
            cout << swaps_[i].first << " " << swaps_[i].second << "\n";
        }
    }

    void ReadData() {
        int n;
        cin >> n;
        data_.resize(n);
        dataSize = (int) data_.size();
        dataMaxSize = (int) data_.size();
        for(int i = 0; i < n; ++i)
            cin >> data_[i];
    }

/*
    void GenerateSwaps() {
        swaps_.clear();
        // TODO: replace by a more efficient implementation
        for (int i = 0; i < data_.size(); ++i)
            for (int j = i + 1; j < data_.size(); ++j) {
                if (data_[i] > data_[j]) {
                    swap(data_[i], data_[j]);
                    swaps_.push_back(make_pair(i, j));
                }
        }
    }
*/

    void siftUp(int i) {
        while ((i > 1) && (data_[i/2] < data_[i])) {
            swap(data_[i/2], data_[i]);
            swaps_.push_back(make_pair((i/2), i));
            i = i/2;
        }
    }

    void siftDown(int i) {
        int maxIndex = i;
        int left = 2*i+1;
        if ((left < dataSize) && (data_[left] < data_[maxIndex])) {
            maxIndex = left;
        }

        int right = (2*i)+2;
        if ((right < dataSize) && (data_[right] < data_[maxIndex])) {
            maxIndex = right;
        }

        if (i != maxIndex) {
            swap(data_[i], data_[maxIndex]);
            swaps_.push_back(make_pair(i, maxIndex));
            siftDown(maxIndex);
        }
    }

    void insert(int p){
//        if (dataSize == dataMaxSize) {
//            return;
//        }
        dataSize = dataSize + 1;
        // last element is size-1
        data_[dataSize - 1] = p;
        siftUp(dataSize-1);
    }

    int extractMax() {
        int result = data_[0];
        data_[0] = data_[dataSize-1];
        dataSize = dataSize - 1;
        siftDown(0);
        return result;

    }

    void removeInt (int i) {
        data_[i] = std::numeric_limits<int>::max();
        siftUp(i);
        extractMax();
    }

    void changePriority(int i, int p) {
        int oldP = data_[i];
        data_[i] = p;
        if (p > oldP) {
            siftUp(i);
        } else {
            siftDown(i);
        }
    }

    void GenerateSwaps() {
        swaps_.clear();

        // A more efficient implementation
        for (int x = ((dataSize)/2); x >= 0 ; x--) {
            siftDown(x);
        }

    }

public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}

