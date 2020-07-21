# python3


def build_heap(data):
    """Build a heap from ``data`` inplace.

    Returns a sequence of swaps performed by the algorithm.
    """
    # The following naive implementation just sorts the given sequence
    # using selection sort algorithm and saves the resulting sequence
    # of swaps. This turns the given array into a heap, but in the worst
    # case gives a quadratic number of swaps.
    #
    # TODO: replace by a more efficient implementation
    swaps = []
    for i in range(len(data)):
        for j in range(i + 1, len(data)):
            if data[i] > data[j]:
                swaps.append((i, j))
                data[i], data[j] = data[j], data[i]
    return swaps


class HeapBuilder:
    def __init__(self):
        self._data = []
        self._swaps = []
        self.data_size = 0
        self.max_size = 0

    def read(self):
        self.data_size = int(input())
        self.max_size = self.data_size
        self._data = list(map(int, input().split()))
        assert len(self._data) == self.data_size

    def write_response(self):
        print(len(self._swaps))
        for i, j in self._swaps:
            print(i, j)

    def generate_swaps(self):
        self._swaps.clear()
        for x in range(int(self.data_size/2), -1, -1):
            self.sift_down(x)

    def sift_down(self, i):
        max_index = i
        left = int(2 * i) + 1
        if (left < self.data_size) and (self._data[left] < self._data[max_index]):
            max_index = left

        right = int(2 * i) + 2
        if (right < self.data_size) and (self._data[right] < self._data[max_index]):
            max_index = right

        if i != max_index:
            self._data[i], self._data[max_index] = self._data[max_index], self._data[i]
            self._swaps.append((i, max_index))
            self.sift_down(max_index)


def main():
    heap = HeapBuilder()
    heap.read()
    heap.generate_swaps()
    heap.write_response()


if __name__ == "__main__":
    main()
