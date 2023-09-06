#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int src, dest, weight;
};

class Graph {
    int V, E;
    vector<Edge> edges;

public:
    Graph(int V, int E) {
        this->V = V;
        this->E = E;
    }

    void addEdge(int src, int dest, int weight) {
        Edge edge;
        edge.src = src;
        edge.dest = dest;
        edge.weight = weight;
        edges.push_back(edge);
    }

    void bellmanFord(int src) {
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        for (int i = 1; i <= V - 1; ++i) {
            for (const Edge& edge : edges) {
                int u = edge.src;
                int v = edge.dest;
                int weight = edge.weight;

                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }

        // Check for negative weight cycles
        for (const Edge& edge : edges) {
            int u = edge.src;
            int v = edge.dest;
            int weight = edge.weight;

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                cout << "Graph contains a negative weight cycle." << endl;
                return;
            }
        }

        // Print shortest distances
        cout << "Vertex \t Distance from Source" << endl;
        for (int i = 0; i < V; ++i) {
            cout << i << "\t" << dist[i] << endl;
        }
    }
};

int main() {
    int V = 5; // Number of vertices
    int E = 8; // Number of edges
    Graph graph(V, E);

    // Add edges with weights
    graph.addEdge(0, 1, -1);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 2);
    graph.addEdge(1, 4, 2);
    graph.addEdge(3, 2, 5);
    graph.addEdge(3, 1, 1);
    graph.addEdge(4, 3, -3);

    int source = 0; // Source vertex

    graph.bellmanFord(source);

    return 0;
}

