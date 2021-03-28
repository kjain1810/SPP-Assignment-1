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
int stride = 64;

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
    for (int i = 0; i < V; i++)
        for (int k = 0; k < V; k++)
            if (dist[i][k] != inf)
                for (int j = 0; j < V; j++)
                    if (dist[k][j] != inf)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

void FWI(int **A, int **B, int **C, int n)
{
    for (int a = 0; a < n; a++)
        for (int c = 0; c < n; c++)
        {
            if (B[a][c] < inf)
                for (int b = 0; b < n; b++)
                {
                    A[a][b] = min(A[a][b], B[a][c] + C[c][b]);
                    // printf("loop:: %d %d %d %d\n", a, c, b, A[a][b]);
                }
            // else
            // printf("inf: %d %d\n", a, c);
        }
}

void FWR(int **A, int **B, int **C, int n)
{
    // printf("rec: %d\n", n);
    if (n <= stride)
    {
        FWI(A, B, C, n);
        return;
    }
    int n2 = n / 2;
    int **A11, **A12, **A21, **A22;
    int **B11, **B12, **B21, **B22;
    int **C11, **C12, **C21, **C22;
    A11 = A;
    A21 = &A[n2];
    B11 = B;
    B21 = &B[n2];
    C11 = C;
    C21 = &C[n2];
    A12 = (int **)malloc(n2 * sizeof(int *));
    A22 = (int **)malloc(n2 * sizeof(int *));
    for (int a = 0; a < n2; a++)
        A12[a] = &A[a][n2];
    for (int a = n2; a < 2 * n2; a++)
        A22[a - n2] = &A[a][n2];
    B12 = (int **)malloc(n2 * sizeof(int *));
    B22 = (int **)malloc(n2 * sizeof(int *));
    for (int a = 0; a < n2; a++)
        B12[a] = &B[a][n2];
    for (int a = n2; a < 2 * n2; a++)
        B22[a - n2] = &B[a][n2];
    C12 = (int **)malloc(n2 * sizeof(int *));
    C22 = (int **)malloc(n2 * sizeof(int *));
    for (int a = 0; a < n2; a++)
        C12[a] = &C[a][n2];
    for (int a = n2; a < 2 * n2; a++)
        C22[a - n2] = &C[a][n2];
    FWR(A11, B11, C11, n2);
    FWR(A12, B11, C12, n2);
    FWR(A21, B21, C11, n2);
    FWR(A22, B21, C12, n2);
    FWR(A22, B22, C22, n2);
    FWR(A21, B22, C21, n2);
    FWR(A12, B12, C22, n2);
    FWR(A11, B12, C21, n2);
    if (n % 2)
    {
        for (int a = 0; a < n; a++)
            for (int b = 0; b < n; b++)
                dist[a][n - 1] = min(dist[a][n - 1], dist[a][b] + dist[b][n - 1]);
        for (int a = 0; a < n; a++)
            for (int b = 0; b < n; b++)
                dist[a][b] = min(dist[a][b], dist[a][n - 1] + dist[n - 1][b]);
        for (int a = 0; a < n; a++)
            for (int b = 0; b < n; b++)
                dist[n - 1][a] = min(dist[n - 1][a], dist[n - 1][b] + dist[b][a]);
    }
    // free(A12);
    // free(A22);
    // free(B12);
    // free(B22);
    // free(C12);
    // free(C22);
}

int main()
{
    getinput();
    for (int a = 0; a < E; a++)
        dist[edges[a][0]][edges[a][1]] = min(dist[edges[a][0]][edges[a][1]], edges[a][2]);
    // FW();
    FWR(dist, dist, dist, V);
    for (int a = 0; a < V; a++)
    {
        for (int b = 0; b < V; b++)
            printf("%d ", dist[a][b] < inf ? dist[a][b] : -1);
        printf("\n");
    }
    return 0;
}