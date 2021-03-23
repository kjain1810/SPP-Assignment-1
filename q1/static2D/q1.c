#include <stdio.h>
#include <stdlib.h>

int n;
int x[15], y[15];
int orderings[5][5];
long long arr[15][1000 * 1000];
int used = 5;

void input()
{
    scanf("%d", &n);
    for (int a = 0; a < n; a++)
    {
        scanf("%d%d", &x[a], &y[a]);
        for (int b = 0; b < x[a]; b++)
            for (int c = 0; c < y[a]; c++)
                scanf("%lld", &arr[a][b * y[a] + c]);
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

void mat_mul(int idx_arr1, int idx_arr2, int idx_ret, int direction)
{
    register int n = x[idx_ret] = x[idx_arr1];
    register int k = y[idx_ret] = y[idx_arr2];
    register int m = y[idx_arr1];
    for (int a = 0; a < n; a++)
        for (int b = 0; b < k; b++)
            arr[idx_ret][a * k + b] = 0;
    for (int c = 0; c < k; c++)
        for (int a = 0; a < n; a++)
        {
            register long long x = 0;
            int b = m;
            while (--b)
                x += arr[idx_arr1][a * m + b] * arr[idx_arr2][b + c * m];
            x += arr[idx_arr1][a * m + b] * arr[idx_arr2][b + c * m];

            // for (int b = 0; b < m; b++)
            //     x += arr[idx_arr1][a * m + b] * arr[idx_arr2][b + c * m];
            if (direction == 0)
                arr[idx_ret][a * k + c] += x;
            else
                arr[idx_ret][a + n * c] += x;
        }
}

int rec_mul(int i, int j, int direction)
{
    if (i == j)
    {
        int here = i;
        if (direction == 1)
        {
            here = used++;
            x[here] = x[i];
            y[here] = y[i];
            for (int a = 0; a < x[i]; a++)
                for (int b = 0; b < y[i]; b++)
                    arr[here][b * x[i] + a] = arr[i][a * y[i] + b];
        }
        return here;
    }
    int ret = used++;
    int arr1 = rec_mul(i, orderings[i][j], 0);
    int arr2 = rec_mul(orderings[i][j] + 1, j, 1);
    mat_mul(arr1, arr2, ret, direction);
    return ret;
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
                printf("%lld ", arr[0][a * y[0] + b]);
            printf("\n");
        }
        return 0;
    }
    setOrder();
    int idx = rec_mul(0, n - 1, 0);
    printf("%d %d\n", x[idx], y[idx]);
    for (int a = 0; a < x[idx]; a++)
    {
        for (int b = 0; b < y[idx]; b++)
            printf("%lld ", arr[idx][a * y[idx] + b]);
        printf("\n");
    }
    return 0;
}