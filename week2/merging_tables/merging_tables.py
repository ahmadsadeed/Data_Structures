# python3


"""
1. Think how to use disjoint set union with path compression and union by rank
heuristics to solve this problem.
2. To quickly find a height of a tree, we will keep the height of each subtree in
an array rank[1 . . . n]: rank[i ] is the height of the subtree whose root is i
3. for any node i , rank[i ] is equal to the height of the tree rooted at i
"""


class Database:
    def __init__(self, row_counts):
        self.row_counts = row_counts
        self.max_row_count = max(row_counts)
        n_tables = len(row_counts)

        # each tree with root i starts with rank 1 and its parent as i
        self.ranks = [1] * n_tables
        self.parents = list(range(n_tables))

    def merge(self, dst, src):
        # if symlink, find main table root
        src_parent = self.get_parent(src)
        dst_parent = self.get_parent(dst)

        if src_parent == dst_parent:
            return False

        # merge two components
        # use union by rank heuristic
        # update max_row_count with the new maximum table size
        if self.ranks[src_parent] > self.ranks[dst_parent]:
            self.parents[dst_parent] = src_parent
            # update row_counts and ranks
            self.row_counts[src_parent] = self.row_counts[src_parent] + self.row_counts[dst_parent]
            self.row_counts[dst_parent] = 0
            if self.row_counts[src_parent] > self.max_row_count:
                self.max_row_count = self.row_counts[src_parent]
        else:
            self.parents[src_parent] = dst_parent
            if self.ranks[src_parent] == self.ranks[dst_parent]:
                self.ranks[dst_parent] = self.ranks[dst_parent] + 1
            # update row_counts and ranks
            self.row_counts[dst_parent] = self.row_counts[dst_parent] + self.row_counts[src_parent]
            self.row_counts[src_parent] = 0
            if self.row_counts[dst_parent] > self.max_row_count:
                self.max_row_count = self.row_counts[dst_parent]

        return True

    def get_parent(self, table):
        # find parent and compress path using recursion
        if table != self.parents[table]:
            self.parents[table] = self.get_parent(self.parents[table])
        return self.parents[table]


def main():
    n_tables, n_queries = map(int, input().split())
    counts = list(map(int, input().split()))
    assert len(counts) == n_tables
    db = Database(counts)
    for i in range(n_queries):
        dst, src = map(int, input().split())
        db.merge(dst - 1, src - 1)
        print(db.max_row_count)


if __name__ == "__main__":
    main()


'''
Sample:

Input:
6 4
10 0 5 0 3 3
6 6
6 5
5 4
4 3

Output:
10
10
10
11

'''