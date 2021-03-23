#include <stdio.h>
#include <stdlib.h>

#define min(a, b) (a > b ? b : a)

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
    for (register int k = 0; k < V; k++)
    {
        register int vk = k * V;
        for (register int i = 0; i < V; i++)
        {
            register int vi = i * V;
            register int x = dist[vi + k];
            if (x < inf)
            {
                register int j = V;
                while (--j)
                    dist[vi + j] = min(dist[vi + j], x + dist[vk + j]);
                dist[vi + j] = min(dist[vi + j], x + dist[vk + j]);
            }
        }
    }
}

int main()
{
    getinput();
    FW();
    for (int a = 0; a < V; a++)
    {
        register int AV = a * V;
        for (register int b = 0; b < V; b++)
            printf("%d ", dist[AV + b] < inf ? dist[AV + b] : -1);
        printf("\n");
    }
    return 0;
}