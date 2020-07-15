#python3
import sys


class StackWithMax:
    def __init__(self):
        self.__stack = []
        self.__stack_max = []

    def push(self, a):
        self.__stack.append(a)
        # if __stack_max is empty, just add this value
        if len(self.__stack) == 1:
            self.__stack_max.append(a)
            return
        # add this value to __stack_max if it is a new max, else add old max
        if a > self.__stack_max[-1]:
            self.__stack_max.append(a)
        else:
            self.__stack_max.append(self.__stack_max[-1])

    def pop(self):
        assert(len(self.__stack))
        self.__stack.pop()
        self.__stack_max.pop()

    def max(self):
        assert(len(self.__stack))
        return self.__stack_max[-1]


if __name__ == '__main__':
    stack = StackWithMax()

    num_queries = int(sys.stdin.readline())
    for _ in range(num_queries):
        query = sys.stdin.readline().split()

        if query[0] == "push":
            stack.push(int(query[1]))
        elif query[0] == "pop":
            stack.pop()
        elif query[0] == "max":
            print(stack.max())
        else:
            assert 0
