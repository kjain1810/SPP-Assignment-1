#include <stdio.h>

int min(int i, int j)
{
    if (i < j)
        return i;
    return j;
}

int max(int i, int j)
{
    if (i > j)
        return i;
    return j;
}

const int inf = 1e9;

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
        edges[a][0]--;
        edges[a][1]--;
    }
    for (int a = 0; a < V; a++)
    {
        dist[a] = (int *)malloc(V * sizeof(int));
        for (int b = 0; b < V; b++)
            dist[a][b] = inf;
        dist[a][a] = 0;
    }
}

void FW()
{
    for (int a = 0; a < E; a++)
        dist[edges[a][0]][edges[a][1]] = min(dist[edges[a][0]][edges[a][1]], edges[a][2]);
    for (int i = 0; i < V; i++)
        for (int k = 0; k < V; k++)
            for (int j = 0; j < V; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

int main()
{
    getinput();
    FW();
    for (int a = 0; a < V; a++)
    {
        for (int b = 0; b < V; b++)
            printf("%d ", dist[a][b] < inf ? dist[a][b] : -1);
        printf("\n");
    }
    return 0;
}