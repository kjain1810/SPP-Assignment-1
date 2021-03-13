#include <stdio.h>
#include <stdlib.h>

int n;
int *x, *y;
int ***arr;
int **orderings;

void input()
{
    scanf("%d", &n);
    x = (int *)malloc(n * sizeof(int));
    y = (int *)malloc(n * sizeof(int));
    arr = (int ***)malloc(n * sizeof(int **));
    orderings = (int **)malloc(n * sizeof(int *));
    for (int a = 0; a < n; a++)
    {
        scanf("%d%d", &x[a], &y[a]);
        arr[a] = (int **)malloc(x[a] * sizeof(int *));
        for (int b = 0; b < x[a]; b++)
        {
            arr[a][b] = (int *)malloc(y[a] * sizeof(int));
            for (int c = 0; c < y[a]; c++)
                scanf("%d", &arr[a][b][c]);
        }
        orderings[a] = (int *)malloc(n * sizeof(int));
    }
}

void setOrder() // n^3 == 125 operatiosn at most
{
    int cost[n][n];
    for (int a = 0; a < n; a++)
        cost[a][a] = 0;
    for (int len = 2; len <= n; len++)
    {
        for (int i = 0; i < n - len + 1; i++)
        {
            int j = i + len - 1;
            cost[i][j] = 1e9;
            for (int k = i; k <= j - 1; k++)
            {
                int here = cost[i][k] + cost[k + 1][j] + x[i] * y[k] * y[j];
                if (here < cost[i][j])
                {
                    cost[i][j] = here;
                    orderings[i][j] = k;
                }
            }
        }
    }
}

int **mat_mul(int **arr1, int **arr2, int n, int m, int k)
{
    int **res = (int **)malloc(n * sizeof(int *));
    for (int a = 0; a < n; a++)
    {
        res[a] = (int *)malloc(k * sizeof(int));
        for (int b = 0; b < k; b++)
            res[a][b] = 0;
    }
    for (int a = 0; a < n; a++)
        for (int b = 0; b < m; b++)
            for (int c = 0; c < k; c++)
                res[a][c] += arr1[a][b] * arr2[b][c];
    free(arr1);
    free(arr2);
    return res;
}

int **rec_mul(int i, int j)
{
    if (i == j)
        return arr[i];
    return mat_mul(rec_mul(i, orderings[i][j]), rec_mul(orderings[i][j] + 1, j), x[i], y[orderings[i][j]], y[j]);
}

int main()
{
    input();
    if (n == 1)
    {
        printf("%d %d\n", x[0], y[0]);
        for (int a = 0; a < x[0]; a++)
        {
            for (int b = 0; b < y[0]; b++)
                printf("%d ", arr[0][a][b]);
            printf("\n");
        }
        return 0;
    }
    setOrder();
    int **res = rec_mul(0, n - 1);
    printf("%d %d\n", x[0], y[n - 1]);
    for (int a = 0; a < x[0]; a++)
    {
        for (int b = 0; b < y[n - 1]; b++)
            printf("%d ", res[a][b]);
        printf("\n");
    }
    return 0;
}