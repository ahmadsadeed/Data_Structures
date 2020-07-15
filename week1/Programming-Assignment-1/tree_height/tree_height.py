# python3

import sys
import threading
import math

sys.setrecursionlimit(10 ** 7)  # max depth of recursion
threading.stack_size(2 ** 27)  # new thread will get stack of such size


class Node(object):
    def __init__(self, key=-math.inf):
        self.key = key
        self.parent = None
        self.children = []

    def add_child(self, child):
        self.children.append(child)

    def add_parent(self, parent):
        self.parent = parent
        parent.add_child(self)


class TreeHeight:
    def __init__(self):
        self.size = 0
        self.raw_data = []
        self.root = -1
        self.nodes = []
        self.max_height = 0

    def read(self):
        self.size = int(sys.stdin.readline())
        self.raw_data = list(map(int, sys.stdin.readline().split()))

    # create tree from self.raw_data into self.nodes list
    # child index:  0  1 2 3 4
    # parent index: 4 -1 4 1 1
    def grow_tree(self):
        for i in range(self.size):
            self.nodes.append(Node())

        for child in range(self.size):
            parent = self.raw_data[child]
            if parent >= 0:
                self.nodes[child].add_parent(self.nodes[parent])
            else:
                self.root = child
            self.nodes[child].key = child
        # compute the max_height attribute
        self.set_tree_height()

    def set_tree_height(self):
        self.max_height = 1 + self.compute_height(self.nodes[self.root])

    def compute_height(self, node: Node):
        if len(node.children) > 0:
            heights = []
            for i in range(len(node.children)):
                height = self.compute_height(node.children[i])
                heights.append(height)

            return 1 + max(heights)
        elif len(node.children) == 0:
            return 0

        return 0

    def compute_height_slow(self):
        # Replace this code with a faster implementation
        max_height = 0
        for vertex in range(self.size):
            height = 0
            i = vertex
            while i != -1:
                height += 1
                i = self.raw_data[i]
            max_height = max(max_height, height)
        return max_height


def main():
    tree = TreeHeight()
    tree.read()
    tree.grow_tree()
    print(tree.max_height)


# if __name__ == '__main__':
#     main()

threading.Thread(target=main).start()
