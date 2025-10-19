#include <stdio.h>
#include <limits.h>

#define N 5  // Number of hosts/nodes

int minKey(int key[], int mstSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < N; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void printMST(int parent[], int graph[N][N]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < N; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

void broadcastTree(int graph[N][N]) {
    int parent[N];    // Array to store constructed MST
    int key[N];       // Key values used to pick minimum weight edge
    int mstSet[N];    // To represent set of vertices included in MST

    // Initialize all keys as infinite and mstSet[] as false
    for (int i = 0; i < N; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    // Start from the first host
    key[0] = 0;
    parent[0] = -1;  // First node is root of MST

    // Construct MST
    for (int count = 0; count < N - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = 1;

        for (int v = 0; v < N; v++) {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the broadcast tree / MST
    printMST(parent, graph);
}

int main() {
    int graph[N][N] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    broadcastTree(graph);

    return 0;
}
