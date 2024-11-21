import matplotlib.pyplot as plt
n = int(input())
arr = [input() for i in range(n)]
x = [int(i.split()[0]) for i in arr]
y = [int(i.split()[1]) for i in arr]

fig,  ax = plt.subplots()
ax.scatter(x, y)

for i, pt in enumerate(zip(x,y)):
    ax.annotate(i, pt)

plt.show()