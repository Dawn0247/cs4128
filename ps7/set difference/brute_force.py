from itertools import combinations
MOD = 1e9 + 7
k = int(input())
for i in range(k):
    input()
    arr = [int(x) for x in input().split()]

    ssum = 0
    for i in range(2,len(arr)+1):
        for s in combinations(arr, i):
            ssum += (max(s) - min(s))

    print(int(ssum % MOD))
