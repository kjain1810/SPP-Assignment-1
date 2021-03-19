#include <stdio.h>
#include <stdlib.h>

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
int stride = 3;

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

void FW_tiled()
{
    for (int a = 0; a < V; a += stride)
    {
        // printf("A = %d\n", a);
        // we first set the values of the (a, a)th BLOCK
        for (int b = 0; b < stride && a + b < V; b++)
            for (int d = 0; d < stride && a + d < V; d++)
            {
                // printf("\tsetting: %d %d\n", a + b, a + d);
                for (int e = 0; e < V; e++)
                    dist[a + b][a + d] = min(dist[a + b][a + d], dist[a + b][e] + dist[e][a + d]);
            }
        // now, set the values of the tiles that are in the same row or column as this tile
        for (int b = 0; b < V; b += stride)
            if (a != b)
                for (int c = 0; c < stride && a + c < V; c++)
                    for (int d = 0; d < stride && b + d < V; d++)
                    {
                        // printf("\tsetting: %d %d\n", a + c, b + d);
                        for (int e = 0; e < V; e++)
                            dist[a + c][b + d] = min(dist[a + c][b + d], dist[a + c][e] + dist[e][b + d]);
                    }
        for (int b = 0; b < V; b += stride)
            if (a != b)
                for (int c = 0; c < stride && b + c < V; c++)
                    for (int d = 0; d < stride && a + d < V; d++)
                    {
                        // printf("\tsetting: %d %d\n", b + c, a + d);
                        for (int e = 0; e < V; e++)
                            dist[b + c][a + d] = min(dist[b + c][a + d], dist[b + c][e] + dist[e][a + d]);
                    }
        // now, the rest of the tiles
        for (int b = 0; b < V; b += stride)
            if (b != a)
                for (int c = 0; c < V; c += stride)
                    if (c != a)
                        for (int d = 0; d < stride && b + d < V; d++)
                            for (int e = 0; e < stride && c + e < V; e++)
                            {
                                // printf("\tsetting: %d %d\n", b + d, c + e);
                                for (int f = 0; f < V; f++)
                                    dist[b + d][c + e] = min(dist[b + d][c + e], dist[b + d][f] + dist[f][c + e]);
                            }
    }
}

int main()
{
    getinput();
    for (int a = 0; a < E; a++)
        dist[edges[a][0]][edges[a][1]] = min(dist[edges[a][0]][edges[a][1]], edges[a][2]);
    FW_tiled();
    for (int a = 0; a < V; a++)
    {
        for (int b = 0; b < V; b++)
            printf("%d ", dist[a][b] < inf ? dist[a][b] : -1);
        printf("\n");
    }
    return 0;
}