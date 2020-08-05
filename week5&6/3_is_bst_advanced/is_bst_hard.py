#!/usr/bin/python3

import sys
import threading
import math

sys.setrecursionlimit(10 ** 7)  # max depth of recursion
# had to increase stack to ** 27 from ** 25
threading.stack_size(2 ** 27)  # new thread will get stack of such size

tree = {}


def is_binary_search_tree(node, neg, pos):
    if node not in tree:
        return True
    # if current key is smaller than neg(left child) or larger than pos(right child)
    if tree[node][0] < neg or tree[node][0] > pos:
        return False
    # run on left and right children
    return is_binary_search_tree(tree[node][1], neg, tree[node][0] - 1) and \
           is_binary_search_tree(tree[node][2], tree[node][0], pos)


def main():
    nodes = int(sys.stdin.readline().strip())
    # the tree dictionary will include list of 3 elements each
    global tree
    neg_inf = -math.inf
    pos_inf = math.inf
    for i in range(nodes):
        tree[i] = list(map(int, sys.stdin.readline().strip().split()))
    if is_binary_search_tree(0, neg_inf, pos_inf):
        print("CORRECT")
    else:
        print("INCORRECT")


threading.Thread(target=main).start()

'''
7
4 1 2
2 3 4
6 5 6
1 -1 -1
3 -1 -1
5 -1 -1
7 -1 -1
'''