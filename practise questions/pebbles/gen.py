import random
random.seed(100)
n = 15
m = 100

for _ in range(m):
    
    for i in range(n):
        for j in range(n):
            print(random.randint(10,99), end = " ")
        print()