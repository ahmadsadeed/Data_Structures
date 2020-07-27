# python3


# Use the direct addressing scheme to solve this problem
class Query:
    def __init__(self, query):
        # add, find or delete query?
        self.type = query[0]
        self.number = int(query[1])
        if self.type == 'add':
            self.name = query[2]


def read_queries():
    n = int(input())
    return [Query(input().split()) for _ in range(n)]


def write_responses(result):
    print('\n'.join(result))


def process_queries(queries):
    result = []
    # list of contacts
    contacts = dict()
    for this in queries:
        if this.type == 'add':
            if this.number in contacts:
                contacts[this.number] = this.name
            else:
                contacts[this.number] = this.name
        elif this.type == 'del':
            if this.number in contacts:
                del contacts[this.number]
        else:
            if this.number in contacts:
                result.append(contacts[this.number])
            else:
                result.append('not found')
    return result


if __name__ == '__main__':
    write_responses(process_queries(read_queries()))
