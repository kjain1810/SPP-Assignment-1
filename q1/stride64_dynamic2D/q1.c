#include <stdio.h>
#include <stdlib.h>

int n;
int *x, *y;
int **orderings;

long long **colarr;

int stride = 64;

void input()
{
    scanf("%d", &n);
    x = (int *)malloc(n * sizeof(int));
    y = (int *)malloc(n * sizeof(int));
    colarr = (long long **)malloc(n * sizeof(long long *));
    orderings = (int **)malloc(n * sizeof(int *));
    for (int a = 0; a < n; a++)
    {
        scanf("%d%d", &x[a], &y[a]);
        colarr[a] = (long long *)malloc(x[a] * y[a] * sizeof(long long));
        for (int b = 0; b < x[a]; b++)
        {
            for (int c = 0; c < y[a]; c++)
                scanf("%lld", &colarr[a][y[a] * b + c]);
        }
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
    for (int a1 = 0; a1 < n; a1 += stride)
        for (int c1 = 0; c1 < k; c1 += stride)
            for (int b1 = 0; b1 < m; b1 += stride)
                for (int a2 = 0; a2 < stride && a1 + a2 < n; a2++)
                    for (int c2 = 0; c2 < stride && c1 + c2 < k; c2++)
                    {
                        long long x = 0;
                        for (int b2 = 0; b2 < stride && b1 + b2 < m; b2++)
                            x += arr1[(a1 + a2) * m + b1 + b2] * arr2[(b1 + b2) * k + c1 + c2];
                        res[(a1 + a2) * k + c1 + c2] = x;
                    }
}

long long *mat_mul(long long *arr1, long long *arr2, int n, int m, int k)
{
    long long *res = (long long *)malloc(n * k * sizeof(long long));
    for (int a = 0; a < n; a++)
        for (int b = 0; b < k; b++)
            res[a * k + b] = 0;
    matmul_loops(arr1, arr2, res, n, m, k);
    free(arr1);
    free(arr2);
    return res;
}

long long *rec_mul(int i, int j)
{
    if (i == j)
        return colarr[i];
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
                printf("%lld ", colarr[0][x[0] * a + b]);
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
