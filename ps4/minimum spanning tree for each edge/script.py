a = """1 2 3
1 3 1
1 4 5
2 3 2
2 5 3
3 4 2
4 5 4
"""
for line in a.split('\n'):
    line = [int(i) for i in line.strip().split()]
    print(f"debug(lca({line[0]-1}, {line[1]-1}));")