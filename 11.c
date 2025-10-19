#include <stdio.h>

#define INF 9999
#define N 4  // Number of nodes

void distanceVector(int graph[N][N]) {
    int distance[N][N]; // distance[i][j] holds shortest distance from i to j
    int i, j, k;

    // Initialize distance with direct graph weights
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            distance[i][j] = graph[i][j];

    // Distance Vector update until no change occurs (Bellman-Ford like)
    int updated;
    do {
        updated = 0;
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                for (k = 0; k < N; k++) {
                    if (distance[i][k] + distance[k][j] < distance[i][j]) {
                        distance[i][j] = distance[i][k] + distance[k][j];
                        updated = 1;
                    }
                }
            }
        }
    } while (updated);

    // Print routing table for each node
    for (i = 0; i < N; i++) {
        printf("\nRouting table for node %d:\n", i);
        printf("Destination\tCost\n");
        for (j = 0; j < N; j++) {
            if (distance[i][j] == INF)
                printf("%d\t\t%s\n", j, "INF");
            else
                printf("%d\t\t%d\n", j, distance[i][j]);
        }
    }
}

int main() {
    // Graph with weights denoting delay between nodes (0 means no direct link except self)
    int graph[N][N] = { {0, 1, 4, INF},
                        {1, 0, 2, 6},
                        {4, 2, 0, 3},
                        {INF, 6, 3, 0} };

    distanceVector(graph);

    return 0;
}
