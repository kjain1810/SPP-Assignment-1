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
int Vorig;
int **dist;
int stride = 64;

void getinput()
{
    scanf("%d%d", &Vorig, &E);
    V = 1;
    while (V < Vorig)
        V *= 2;
    dist = (int **)malloc(V * sizeof(int *));
    for (int a = 0; a < V; a++)
    {
        dist[a] = (int *)malloc(V * sizeof(int));
        for (int b = 0; b < V; b++)
            dist[a][b] = inf;
        dist[a][a] = 0;
    }
    for (int a = 0; a < E; a++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        dist[(u - 1)][(v - 1)] = min(dist[(u - 1)][(v - 1)], w);
    }
}

void FWI(int **A, int **B, int **C, int n)
{
    for (int a = 0; a < n; a++)
        for (int c = 0; c < n; c++)
            if (B[a][c] < inf)
                for (int b = 0; b < n; b++)
                    A[a][b] = min(A[a][b], B[a][c] + C[c][b]);
}

void FWR(int **A, int **B, int **C, int n)
{
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
    free(A12);
    free(A22);
    free(B12);
    free(B22);
    free(C12);
    free(C22);
}

int main()
{
    getinput();
    FWR(dist, dist, dist, V);
    for (int a = 0; a < Vorig; a++)
    {
        for (int b = 0; b < Vorig; b++)
            printf("%d ", dist[a][b] < inf ? dist[a][b] : -1);
        printf("\n");
    }
    return 0;
}