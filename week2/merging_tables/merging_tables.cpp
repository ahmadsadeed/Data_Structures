#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct DisjointSetsElement {
    int size, parent, rank;

    DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
    int size;
    int max_table_size;
    vector <DisjointSetsElement> sets;

    DisjointSets(int size): size(size), max_table_size(0), sets(size) {
        for (int i = 0; i < size; i++)
            sets[i].parent = i;
    }

    int getParent(int table) {
        // find parent and compress path
        DisjointSetsElement &element = sets[table];
        if (table != element.parent){
            element.parent = getParent(element.parent);
        }
        return element.parent;
    }

    void merge(int destination, int source) {
        int realDestination = getParent(destination);
        int realSource = getParent(source);
        if (realDestination != realSource) {
            // merge two components // use union by rank heuristic  // update max_table_size
            DisjointSetsElement &dest = sets[realDestination];
            DisjointSetsElement &src = sets[realSource];
            if (src.rank > dest.rank) {
                dest.parent = realSource;
                src.size = src.size + dest.size;
                if (src.size > max_table_size)
                    max_table_size = src.size;
                dest.size = 0;
            } else {
                src.parent = realDestination;
                dest.size = dest.size + src.size;
                if (dest.size > max_table_size)
                    max_table_size = dest.size;
                src.size = 0;
                if (src.rank == dest.rank)
                    (dest.rank)++;
            }

        }
    }
};

int main() {
    int numOfTables, mergeQueries;
    cin >> numOfTables >> mergeQueries;

    DisjointSets tables(numOfTables);
    for (auto &table : tables.sets) {
        cin >> table.size;
        tables.max_table_size = max(tables.max_table_size, table.size);
    }

    vector<int> maxSizes;
    for (int i = 0; i < mergeQueries; i++) {
        int destination, source;
        cin >> destination >> source;
        --destination;
        --source;

        tables.merge(destination, source);
        maxSizes.push_back(tables.max_table_size);
//        cout << tables.max_table_size << endl;
//        cout << "Parents: ";
//        for (auto &table : tables.sets) {
//            cout << (table.parent)+1 << " ";
//        }
//        cout << "\nRank:    ";
//        for (auto &table : tables.sets) {
//            cout << table.rank << " ";
//        }
//        cout << endl << endl;
    }
    for (int i  : maxSizes) {
        cout << i << endl;
    }

    return 0;
}

