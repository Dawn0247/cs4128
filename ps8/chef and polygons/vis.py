import matplotlib.pyplot as plt
n, m = [int(x) for x in input().strip().split()]
red_x = []
red_y = []
black_x = []
black_y = []
for i in range(n):
    x, y = input().strip().split()
    red_x.append(int(x))
    red_y.append(int(y))

for i in range(m):
    x, y = input().strip().split()
    black_x.append(int(x))
    black_y.append(int(y))


input() 


l = input()
l = l.strip().split()[1:]
red_x_used = []
red_y_used = []
for i in map(int, l):
    red_x_used.append(red_x[i-1])
    red_y_used.append(red_y[i-1])
    plt.annotate(i-1, (red_x[i-1], red_y[i-1]))

    
plt.scatter(red_x_used, red_y_used, color="red")
plt.scatter(black_x, black_y, color="black")
# for i, pt in enumerate(zip(red_x, red_y)):
#     plt.annotate(i, pt)

for i, pt in enumerate(zip(black_x, black_y)):
    plt.annotate(i, pt)


plt.show()