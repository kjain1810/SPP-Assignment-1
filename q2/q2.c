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
int stride = 256;

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
    for (int k = 0; k < V; k++)
    {
        for (int i1 = 0; i1 < V; i1 += stride)
        {
            for (int i2 = 0; i2 < stride && i1 + i2 < V; i2++)
                for (int j1 = 0; j1 < stride && i1 + j1 < V; j1++)
                    dist[i1 + i2][i1 + j1] = min(dist[i1 + i2][i1 + j1], dist[i1 + i2][k] + dist[k][i1 + j1]);
            for (int i2 = 0; i2 < V; i2 += stride)
                if (i2 != i1)
                    for (int i3 = 0; i3 < stride && i2 + i3 < V; i3++)
                        for (int j1 = 0; j1 < stride && i1 + j1 < V; j1++)
                            dist[i2 + i3][i1 + j1] = min(dist[i2 + i3][i1 + j1], dist[i2 + i3][k] + dist[k][i1 + j1]);
            for (int i2 = 0; i2 < V; i2 += stride)
                if (i2 != i1)
                    for (int i3 = 0; i3 < stride && i1 + i3 < V; i3++)
                        for (int j1 = 0; j1 < stride && i2 + j1 < V; j1++)
                            dist[i1 + i3][i2 + j1] = min(dist[i1 + i3][i2 + j1], dist[i1 + i3][k] + dist[k][i2 + j1]);
            for (int i2 = 0; i2 < V; i2 += stride)
                if (i2 != i1)
                    for (int j1 = 0; j1 < V; j1 += stride)
                        if (j1 != i1)
                            for (int i3 = 0; i3 < stride && i2 + i3 < V; i3++)
                                for (int j2 = 0; j2 < stride && j1 + j2 < V; j2++)
                                    dist[i2 + i3][j1 + j2] = min(dist[i2 + i3][j1 + j2], dist[i2 + i3][k] + dist[k][j1 + j2]);
        }
    }
    // for (int a = 0; a < V; a += stride)
    // {
    //     // we first set the values of the (a, a)th BLOCK
    //     for (int e = 0; e < V; e++)
    //         for (int b = 0; b < stride && a + b < V; b++)
    //             for (int d = 0; d < stride && a + d < V; d++)
    //                 dist[a + b][a + d] = min(dist[a + b][a + d], dist[a + b][e] + dist[e][a + d]);
    //     // now, set the values of the tiles that are in the same row or column as this tile
    //     for (int e = 0; e < V; e++)
    //         for (int b = 0; b < V; b += stride)
    //             if (a != b)
    //                 for (int c = 0; c < stride && a + c < V; c++)
    //                     for (int d = 0; d < stride && b + d < V; d++)
    //                         dist[a + c][b + d] = min(dist[a + c][b + d], dist[a + c][e] + dist[e][b + d]);
    //     for (int e = 0; e < V; e++)
    //         for (int b = 0; b < V; b += stride)
    //             if (a != b)
    //                 for (int c = 0; c < stride && b + c < V; c++)
    //                     for (int d = 0; d < stride && a + d < V; d++)
    //                         dist[b + c][a + d] = min(dist[b + c][a + d], dist[b + c][e] + dist[e][a + d]);
    //     // now, the rest of the tiles
    //     for (int f = 0; f < V; f++)
    //         for (int b = 0; b < V; b += stride)
    //             if (b != a)
    //                 for (int c = 0; c < V; c += stride)
    //                     if (c != a)
    //                         for (int d = 0; d < stride && b + d < V; d++)
    //                             for (int e = 0; e < stride && c + e < V; e++)
    //                                 dist[b + d][c + e] = min(dist[b + d][c + e], dist[b + d][f] + dist[f][c + e]);
    // }
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