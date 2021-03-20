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
int dist[2500 * 2500];

void getinput()
{
    scanf("%d%d", &V, &E);
    for (int a = 0; a < V; a++)
    {
        for (int b = 0; b < V; b++)
            dist[a * V + b] = inf;
        dist[a * V + a] = 0;
    }
    for (int a = 0; a < E; a++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        dist[(u - 1) * V + (v - 1)] = min(dist[(u - 1) * V + (v - 1)], w);
    }
}

void FW()
{
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
        {
            int x = dist[i * V + k];
            for (int j = 0; j < V; j++)
                dist[i * V + j] = min(dist[i * V + j], x + dist[k * V + j]);
        }
}

int main()
{
    getinput();
    FW();
    for (int a = 0; a < V; a++)
    {
        for (int b = 0; b < V; b++)
            printf("%d ", dist[a * V + b] < inf ? dist[a * V + b] : -1);
        printf("\n");
    }
    return 0;
}