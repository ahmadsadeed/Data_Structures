#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

// shorten the pair<> type
typedef pair<int, long long> pairType;

class Heap {
public:
    vector<pairType> data_;
    int threadCount_ = 0;

    Heap(int threadCount) {
        threadCount_ = threadCount;
        for (int i = 0; i < threadCount; i++)
            data_.push_back(make_pair(i, 0));
    }

    bool comPair(pairType p1, pairType p2){
        if (p1.second != p2.second)
            return p1.second < p2.second;
        else
            return p1.first < p2.first;
    }

    void siftUp(int i) {
        while ((i > 1) && comPair(data_[i], data_[(i-1)/2])) {
            swap(data_[(i-1)/2], data_[i]);
            i = (i-1)/2;
        }
    }

    void siftDown(int i) {
        int maxIndex = i;
        int left = 2*i+1;
        if ((left < threadCount_) &&  comPair(data_[left], data_[maxIndex]))
            maxIndex = left;

        int right = (2*i)+2;
        if ((right < threadCount_) && comPair(data_[right], data_[maxIndex]))
            maxIndex = right;

        if (i != maxIndex) {
            swap(data_[i], data_[maxIndex]);
            siftDown(maxIndex);
        }
    }

    void changePriority(int i, long long p) {
        long long oldP = data_[i].second;
        data_[i] = make_pair(data_[i].first, p);
        if (p > oldP)
            siftUp(i);
        else
            siftDown(i);
        siftDown(i);
    }

    //    void GenerateSwapsMinHeap() {
    //        data_.clear();
    //        for (int x = (threadCount_/2); x >= 0 ; x--) {siftDown(x);}
    //    }
};

class JobQueue {
private:
    int num_workers_;
    vector<int> jobs_;
    vector<int> assigned_workers_;
    vector<long long> start_times_;

    void WriteResponse() const {
        for (int i = 0; i < jobs_.size(); ++i) {
            cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        }
    }

    void ReadData() {
        int m;
        cin >> num_workers_ >> m;
        jobs_.resize(m);
        for(int i = 0; i < m; ++i)
            cin >> jobs_[i];
    }

    void AssignJobs() {
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        Heap heap = Heap(num_workers_);
        for (int i = 0; i < jobs_.size(); i++) {
            assigned_workers_[i] = heap.data_[0].first;
            start_times_[i] = heap.data_[0].second;
            heap.changePriority(0, heap.data_[0].second + jobs_[i]);
        }
    }

public:
    void Solve() {
        ReadData();
        AssignJobs();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}
