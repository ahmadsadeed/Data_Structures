# python3

import sys
import threading

sys.setrecursionlimit(10 ** 6)  # max depth of recursion
threading.stack_size(2 ** 27)  # new thread will get stack of such size


class TreeOrders:
    def __init__(self):
        self.n = -1
        self.key, self.left, self.right, self.result = [], [], [], []

    def read(self):
        """
        𝑘𝑒𝑦𝑖 is the key of the 𝑖-th vertex, 𝑙𝑒𝑓𝑡𝑖 is the index of the left
        child of the 𝑖-th vertex, and 𝑟𝑖𝑔ℎ𝑡𝑖 is the index of the right child of the
        𝑖-th vertex. If 𝑖 doesn’t have left or right child (or both),
        the corresponding 𝑙𝑒𝑓𝑡𝑖 or 𝑟𝑖𝑔ℎ𝑡𝑖 (or both) will be equal to −1 """
        self.n = int(sys.stdin.readline())
        self.key = [0 for _ in range(self.n)]
        self.left = [0 for _ in range(self.n)]
        self.right = [0 for _ in range(self.n)]
        for i in range(self.n):
            [a, b, c] = map(int, sys.stdin.readline().split())
            self.key[i] = a
            self.left[i] = b
            self.right[i] = c

    def in_order(self):
        self.result = []

        def in_order_traversal(node):
            if node == -1:
                return
            in_order_traversal(self.left[node])
            self.result.append(self.key[node])
            in_order_traversal(self.right[node])

        in_order_traversal(0)
        return self.result

    def pre_order(self):
        self.result = []

        def pre_order_traversal(node):
            if node == -1:
                return
            self.result.append(self.key[node])
            pre_order_traversal(self.left[node])
            pre_order_traversal(self.right[node])

        pre_order_traversal(0)
        return self.result

    def post_order(self):
        self.result = []

        def post_order_traversal(node):
            if node == -1:
                return
            post_order_traversal(self.left[node])
            post_order_traversal(self.right[node])
            self.result.append(self.key[node])

        post_order_traversal(0)
        return self.result


def main():
    tree = TreeOrders()
    tree.read()
    print(" ".join(str(x) for x in tree.in_order()))
    print(" ".join(str(x) for x in tree.pre_order()))
    print(" ".join(str(x) for x in tree.post_order()))


threading.Thread(target=main).start()

'''
5
4 1 2
2 3 4
5 -1 -1
1 -1 -1
3 -1 -1

1 2 3 4 5
4 2 1 3 5
1 3 2 5 4

'''