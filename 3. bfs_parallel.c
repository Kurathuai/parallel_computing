#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_NODES 1000
#define MAX_EDGES 10000

typedef struct {
    int neighbors[MAX_EDGES];
    int neighbor_count;
} Node;

Node graph[MAX_NODES];
int visited[MAX_NODES];
int current_frontier[MAX_NODES];
int next_frontier[MAX_NODES];

int num_nodes = 6; 

void add_edge(int u, int v) {
    graph[u].neighbors[graph[u].neighbor_count++] = v;
    graph[v].neighbors[graph[v].neighbor_count++] = u;  
}

void bfs_parallel(int start) {
    int front_size = 1;
    int next_size = 0;
    visited[start] = 1;
    current_frontier[0] = start;

    printf("BFS Order: %d ", start);

    while (front_size > 0) {
        next_size = 0;

        #pragma omp parallel
        {
            int local_next[MAX_NODES];
            int local_count = 0;

            #pragma omp for nowait
            for (int i = 0; i < front_size; i++) {
                int u = current_frontier[i];

                for (int j = 0; j < graph[u].neighbor_count; j++) {
                    int v = graph[u].neighbors[j];

                    if (!visited[v]) {
                        int expected = 0;
                        if (__sync_bool_compare_and_swap(&visited[v], 0, 1)) {
                            printf("%d ", v);
                            local_next[local_count++] = v;
                        }
                    }
                }
            }
            #pragma omp critical
            {
                for (int k = 0; k < local_count; k++) {
                    next_frontier[next_size++] = local_next[k];
                }
            }
        }

        for (int i = 0; i < next_size; i++) {
            current_frontier[i] = next_frontier[i];
        }
        front_size = next_size;
    }

    printf("\n");
}

int main() {
    add_edge(0, 1);
    add_edge(0, 2);
    add_edge(1, 3);
    add_edge(2, 3);
    add_edge(3, 4);
    add_edge(4, 5);

    bfs_parallel(0);

    return 0;
}

