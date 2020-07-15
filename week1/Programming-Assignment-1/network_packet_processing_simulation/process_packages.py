# python3
from collections import namedtuple, deque


Request = namedtuple("Request", ["arrived_at", "time_to_process"])
Response = namedtuple("Response", ["was_dropped", "started_at"])


class Buffer:
    def __init__(self, size):
        self.size = size
        self.finish_time = deque(maxlen=size)

    def process(self, request):
        # pop packets from the front of the deque if their finish time is <= request.arrival_time
        while len(self.finish_time) != 0 and (self.finish_time[0] <= request.arrived_at):
            self.finish_time.popleft()

        # if deque in not full,
        if len(self.finish_time) < self.size:
            if len(self.finish_time) == 0:
                self.finish_time.append(request.arrived_at + request.time_to_process)
                return Response(False, request.arrived_at)
            else:
                # if the finish time for last packet in line is bigger than current packet's
                # arrival time, change the current packet's arrival time to the bigger value
                last_in_line = self.finish_time[-1]
                current = request.arrived_at
                if last_in_line > current:
                    current = last_in_line
                elif last_in_line == current:  # to make sure they are in order
                    current = last_in_line + 1
                
                self.finish_time.append(current + request.time_to_process)
                # return the updated arrival time
                return Response(False, current)

        elif len(self.finish_time) == self.size:  # if the deque is full, drop the packet
            return Response(True, 0)
        
        return Response(False, -1)


def process_requests(requests, buffer):
    responses = []
    for request in requests:
        responses.append(buffer.process(request))
    return responses


def main():
    buffer_size, n_requests = map(int, input().split())
    requests = []
    for _ in range(n_requests):
        arrived_at, time_to_process = map(int, input().split())
        requests.append(Request(arrived_at, time_to_process))

    buffer = Buffer(buffer_size)
    responses = process_requests(requests, buffer)

    for response in responses:
        print(response.started_at if not response.was_dropped else -1)


if __name__ == "__main__":
    main()
