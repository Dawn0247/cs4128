import networkx as nx
e = """0 1 10
0 2 10
1 2 2
1 3 4
1 4 8
2 4 9
3 5 10
4 3 6
4 5 10

"""
G = nx.DiGraph()
G.add_nodes_from(range(1, 7))
for l in e.strip().split('\n'):
    l = l.split()
    G.add_edge(int(l[0]), int(l[1]), weight=int(l[2]))

pos=nx.circular_layout(G)
nx.draw(G,pos, with_labels = True)
labels = nx.get_edge_attributes(G,'weight')
nx.draw_networkx_edge_labels(G,pos,edge_labels=labels)

