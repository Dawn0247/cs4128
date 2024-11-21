import random
k = random.randint(1,5)
n = random.randint(1000, 10000)
print(k)
for i in range(k):
    print(n)
    data = [str(random.randint(0,1000000000)) for i in range(n)]
    print(" ".join(data))