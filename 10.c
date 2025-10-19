#include <stdio.h>
#include <limits.h>

#define V 5  // Number of vertices in the graph

// Find the vertex with minimum distance value, from the set of vertices not yet included in shortest path tree
int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    return min_index;
}

// Print the constructed distance array
void printSolution(int dist[]) {
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Implementation of Dijkstra’s algorithm
void dijkstra(int graph[V][V], int src) {
    int dist[V];    // The output array. dist[i] will hold the shortest distance from src to i
    int sptSet[V];  // sptSet[i] will be true if vertex i is included in shortest path tree

    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update dist[v] only if is not in sptSet, there is an edge from u to v,
        // and total weight of path from src to v through u is smaller than current value of dist[v]
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // Print the constructed distance array
    printSolution(dist);
}

int main() {
    int graph[V][V] = {
        {0, 10, 20, 0, 0},
        {10, 0, 5, 16, 0},
        {20, 5, 0, 20, 1},
        {0, 16, 20, 0, 2},
        {0, 0, 1, 2, 0}
    };

    dijkstra(graph, 0);

    return 0;
}
