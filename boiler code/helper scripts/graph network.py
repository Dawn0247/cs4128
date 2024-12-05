import networkx as nx
import matplotlib.pyplot as plt
l = input()
n, m = [int(x) for x in l.split()]
e = []
minn = 1e18
maxn = 0
for i in range(m):
    u,v,w = [int(x) for x in input().split()]
    minn = min(minn, v, u)
    maxn = max(maxn, u, v)
    e.append([u,v,w])

G = nx.DiGraph()    
G.add_nodes_from(range(minn, maxn+1))
for u,v,w in e:
    G.add_edge(u, v, weight=w)

pos=nx.circular_layout(G)
nx.draw(G,pos, with_labels = True)
labels = nx.get_edge_attributes(G,'weight')
nx.draw_networkx_edge_labels(G,pos,edge_labels=labels)
plt.show()
