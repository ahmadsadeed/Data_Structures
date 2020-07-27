# python3
import random


# implement the Rabin–Karp’s algorithm.
def read_input():
    return input().rstrip(), input().rstrip()


def print_occurrences(output):
    print(' '.join(map(str, output)))


def poly_hash(text, prime, multiplier):
    ans = 0
    for c in reversed(text):
        ans = (ans * multiplier + ord(c)) % prime
    return ans


def pre_compute_hashes(text, pat_len, prime, multiplier):
    # sudo code at the end
    txt_len = len(text)
    indexes = [0] * (txt_len - pat_len + 1)
    s = text[-pat_len:]
    indexes[txt_len - pat_len] = poly_hash(s, prime, multiplier)
    y = 1
    for i in range(1, pat_len + 1):
        y = (y * multiplier) % prime

    for i in reversed(range(txt_len - pat_len)):
        key = multiplier * indexes[i + 1] + ord(text[i]) - y * ord(text[i + pat_len])
        while key < 0:
            key += prime
        indexes[i] = key % prime
    return indexes


# Rabin Karp
def get_occurrences(pattern, text):
    prime = 1000000007
    multiplier = random.randint(1, prime)
    pat_len = len(pattern)
    pat_hash = poly_hash(pattern, prime, multiplier)
    hashes = pre_compute_hashes(text, pat_len, prime, multiplier)
    output = []
    for i in range(len(text) - len(pattern) + 1):
        if pat_hash == hashes[i] and text[i:i + len(pattern)] == pattern:
            output.append(i)
    return output


def get_occurrences_fast(pattern, text):
    i = text.find(pattern)
    output = []
    while i != -1:
        output.append(i)
        i = text.find(pattern, i + 1)
    return output


if __name__ == '__main__':
    print_occurrences(get_occurrences(*read_input()))

'''
PrecomputeHashes(T, |P|, p, x):
    H ← array of length |T| − |P| + 1
    S ← T[ |T| − |P|..|T| − 1]
    H[ |T| − |P| ] ← PolyHash(S, p, x)
    y ← 1
    for i from 1 to |P|:
        y ← (y × x) mod p
    for i from |T| − |P| − 1 down to 0:
        H[ i ] ← (xH[ i + 1] + T[i ] − yT[ i + |P| ]) mod p
    return H
    
RabinKarp(T, P):
    p ← big prime, x ← random(1, p − 1)
    result ← empty list
    pHash ← PolyHash(P, p, x)
    for i from 0 to |T| − |P|:
        tHash ← PolyHash(T[i ..i+|P|−1], p, x)
        if pHash ̸= tHash:
            continue
        if AreEqual(T[i ..i + |P| − 1], P):
            result.Append(i)
    return result
'''