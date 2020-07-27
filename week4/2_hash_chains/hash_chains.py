# python3


class Query:
    def __init__(self, query):
        self.type = query[0]
        if self.type == 'check':
            self.ind = int(query[1])
        else:
            self.s = query[1]


class QueryProcessor:
    _multiplier = 263
    _prime = 1000000007

    def __init__(self, bucket_count):
        self.bucket_count = bucket_count
        # store strings in dictionaries inside list based on their hash-key
        self.bucket = [{} for _ in range(self.bucket_count)]

    def _hash_func(self, s):
        ans = 0
        for c in reversed(s):
            ans = (ans * self._multiplier + ord(c)) % self._prime
        return ans % self.bucket_count

    def write_search_result(self, was_found):
        print('yes' if was_found else 'no')

    def write_chain(self, chain):
        print(' '.join(chain))

    def read_query(self):
        return Query(input().split())

    def process_query(self, query):
        if query.type == "check":
            # use reverse order, because we append strings to the end of dict
            self.write_chain(reversed(list(cur for cur in (self.bucket[query.ind]))))
        else:
            key = self._hash_func(query.s)
            if query.type == 'find':
                if query.s in self.bucket[key].keys():
                    self.write_search_result(True)
                else:
                    self.write_search_result(False)
            elif query.type == 'add':
                if query.s not in self.bucket[key].keys():
                    self.bucket[key].update({query.s: None})
            else:  # if delete
                if query.s in self.bucket[key].keys():
                    self.bucket[key].pop(query.s)

    def process_queries(self):
        n = int(input())
        for i in range(n):
            self.process_query(self.read_query())


if __name__ == '__main__':
    buckets = int(input())
    proc = QueryProcessor(buckets)
    proc.process_queries()

'''
 5
 12
 add world
 add HellO
 check 4
 find World
 find world
 del world
 check 4
 del HellO
 add luck
 add GooD
 check 2
 del good
 
3
12
check 0
find help
add help
add del
add add
find add
find del
del del
find del
check 0
check 1
check 2
'''
