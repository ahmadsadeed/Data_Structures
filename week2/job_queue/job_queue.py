# python3

from collections import namedtuple

AssignedJob = namedtuple("AssignedJob", ["worker", "started_at"])


def assign_jobs(n_workers, jobs):
    # TODO: replace this code with a faster algorithm.
    result = []
    next_free_time = [0] * n_workers
    for job in jobs:
        next_worker = min(range(n_workers), key=lambda w: next_free_time[w])
        result.append(AssignedJob(next_worker, next_free_time[next_worker]))
        next_free_time[next_worker] += job

    return result


def compare(job1: AssignedJob, job2: AssignedJob):
    if job1.started_at != job2.started_at:
        return job1.started_at < job2.started_at
    else:
        return job1.worker < job2.worker


class Heap:
    def __init__(self, n_workers=0):
        self.n_workers = n_workers
        # give each thread a job by setting its start_time to 0
        self.threads = [AssignedJob(i, 0) for i in range(self.n_workers)]

    def sift_up(self, i):
        while (i > 1) and compare(self.threads[i], self.threads[(i - 1) / 2]):
            # swap with its parent if it is smaller than parent
            self.threads[(i-1) / 2], self.threads[i] = self.threads[i], self.threads[(i-1) / 2]
            i = (i-1) / 2

    def sift_down(self, i):
        max_index = i
        left = int(2 * i) + 1

        if (left < self.n_workers) and compare(self.threads[left], self.threads[max_index]):
            max_index = left

        right = int(2 * i) + 2
        if (right < self.n_workers) and compare(self.threads[right], self.threads[max_index]):
            max_index = right

        if i != max_index:
            self.threads[i], self.threads[max_index] = self.threads[max_index], self.threads[i]
            self.sift_down(max_index)

    def change_priority(self, i, p_new):
        old_p = self.threads[i].started_at
        self.threads[i] = AssignedJob(self.threads[i].worker, p_new)
        if p_new > old_p:
            self.sift_up(i)
        else:
            self.sift_down(i)
        self.sift_down(i)


class JobQueue:
    def __init__(self):
        self.n_workers = 0
        self.jobs = []
        self.threads: [AssignedJob] = []

    def read(self):
        self.n_workers, m = map(int, input().split())
        self.jobs = [0] * m
        self.jobs = list(map(int, input().split()))
        assert len(self.jobs) == m

    def write_response(self):
        for job in self.threads:
            print(job.worker, job.started_at)
    '''
    2 5
    1 2 3 4 5
    # there are 2 threads or workers and 5 jobs
    0 0
    1 0
    0 1
    1 2
    0 4
    '''
    def assign_jobs(self):
        self.threads = [AssignedJob(0, 0)] * len(self.jobs)
        heap = Heap(self.n_workers)
        for i in range(len(self.jobs)):
            self.threads[i] = AssignedJob(heap.threads[0].worker, heap.threads[0].started_at)
            # add new job
            heap.change_priority(0, heap.threads[0].started_at + self.jobs[i])


def main():
    queue = JobQueue()
    queue.read()
    queue.assign_jobs()
    queue.write_response()


if __name__ == "__main__":
    main()
