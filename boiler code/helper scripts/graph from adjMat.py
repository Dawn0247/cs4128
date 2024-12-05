import sys
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt

def main():
    # Read the adjacency matrix from stdin
    input_data = sys.stdin.read()
    adjacency_matrix = np.loadtxt(input_data.splitlines())

    # Create a graph from the adjacency matrix
    G = nx.from_numpy_matrix(adjacency_matrix, create_using=nx.DiGraph())

    # Draw the graph with edge labels to show weights
    pos = nx.spring_layout(G)  # Layout for better visualization
    nx.draw(G, pos, with_labels=True, node_color='lightblue', edge_color='gray', node_size=1000, font_size=10)
    edge_labels = nx.get_edge_attributes(G, 'weight')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)
    plt.title("Graph from Weighted Adjacency Matrix")
    plt.show()

if __name__ == "__main__":
    main()
