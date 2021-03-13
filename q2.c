#include <stdio.h>

const int INF = 1e9;

int V, E;
int **edges;
int **dist;

void getinput()
{
    scanf("%d%d", &V, &E);
    edges = (int **)malloc(E * sizeof(int *));
    dist = (int **)malloc(V * sizeof(int *));
    for (int a = 0; a < E; a++)
    {
        edges[a] = (int *)malloc(3 * sizeof(int));
        scanf("%d%d%d", &edges[a][0], &edges[a][1], &edges[a][2]);
    }
    for (int a = 0; a < V; a++)
        dist[a] = (int *)malloc(V * sizeof(int));
}

int main()
{
    getinput();
    return 0;
}