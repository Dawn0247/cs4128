import matplotlib.pyplot as plt
n = int(input())
pts = []
xs = []
ys = []
ids = []

for i in range(n):
    x,y = [int(i) for i in input().split()]
    ids.append(i)
    xs.append(x)
    ys.append(y)

plt.scatter(xs, ys)

for i, txt in enumerate(ids):
    plt.annotate(txt, (xs[i], ys[i]))

plt.show()

