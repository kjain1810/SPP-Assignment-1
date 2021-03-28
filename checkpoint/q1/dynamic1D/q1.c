#include <stdio.h>
#include <stdlib.h>

int n;
int *x, *y;
int **orderings;

// long long **colarr;
long long *arr;
int stride = 1000 * 1000;

void input()
{
    scanf("%d", &n);
    x = (int *)malloc(n * sizeof(int));
    y = (int *)malloc(n * sizeof(int));
    arr = (long long *)malloc(n * stride * sizeof(long long));
    orderings = (int **)malloc(n * sizeof(int *));
    for (int a = 0; a < n; a++)
    {
        scanf("%d%d", &x[a], &y[a]);
        for (int b = 0; b < x[a]; b++)
            for (int c = 0; c < y[a]; c++)
                scanf("%lld", &arr[a * stride + y[a] * b + c]);
        orderings[a] = (int *)malloc(n * sizeof(int));
    }
}

void setOrder() // n^3 == 125 operatiosn at most
{
    long long cost[n][n];
    for (int a = 0; a < n; a++)
        cost[a][a] = 0;
    for (int len = 2; len <= n; len++)
        for (int i = 0; i < n - len + 1; i++)
        {
            int j = i + len - 1;
            cost[i][j] = 1e18;
            orderings[i][j] = 1e9;
            for (int k = i; k <= j - 1; k++)
            {
                long long here = cost[i][k] + cost[k + 1][j] + (long long)(x[i] * y[k] * y[j]);
                if (here < cost[i][j])
                {
                    cost[i][j] = here;
                    orderings[i][j] = k;
                }
            }
        }
}

void matmul_loops(long long *arr1, long long *arr2, long long *res, int n, int m, int k)
{
    for (int a = 0; a < n; a++)
        for (int c = 0; c < k; c++)
        {
            long long x = 0;
            for (int b = 0; b < m; b++)
                x += arr1[a * m + b] * arr2[b * k + c];
            res[a * k + c] = x;
        }
}

long long *mat_mul(long long *arr1, long long *arr2, int n, int m, int k)
{
    long long *res = (long long *)malloc(n * k * sizeof(long long));
    for (int a = 0; a < n; a++)
        for (int b = 0; b < k; b++)
            res[a * k + b] = 0;
    matmul_loops(arr1, arr2, res, n, m, k);
    return res;
}

long long *rec_mul(int i, int j)
{
    if (i == j)
        return &arr[i * stride];
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
                printf("%lld ", arr[x[0] * a + b]);
            printf("\n");
        }
        return 0;
    }
    setOrder();
    long long *res = rec_mul(0, n - 1);
    printf("%d %d\n", x[0], y[n - 1]);
    for (int a = 0; a < x[0]; a++)
    {
        for (int b = 0; b < y[n - 1]; b++)
            printf("%lld ", res[a * y[n - 1] + b]);
        printf("\n");
    }
    return 0;
}