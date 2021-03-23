#include <stdio.h>
#include <stdlib.h>

int n;
int x[15], y[15];
int orderings[5][5];
long long arr[15][1000 * 1000], cost[5][5];
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
    for (int len = 2; len <= n; len++)
        for (int i = 0; i < n - len + 1; i++)
        {
            int j = i + len - 1;
            cost[i][j] = 1e18;
            orderings[i][j] = 1e9;
            for (int k = i; k <= j - 1; k++)
            {
                long long here = cost[i][k] + cost[k + 1][j] + (long long)(x[i] * y[k] * y[j]);
                if (here <= cost[i][j])
                {
                    cost[i][j] = here;
                    orderings[i][j] = k;
                }
            }
        }
}

int rec_mul(int i, int j, int direction)
{
    if (i == j)
    {
        register int here = i;
        if (direction == 1)
        {
            here = used++;
            x[here] = x[i];
            y[here] = y[i];
            for (register int a = 0; a < x[i]; a++)
            {
                register int AY = a * y[i];
                for (register int b = 0; b < y[i]; b++)
                    arr[here][b * x[i] + a] = arr[i][AY + b];
            }
        }
        return here;
    }
    int idx_ret = used++;
    int idx_arr1 = rec_mul(i, orderings[i][j], 0);
    int idx_arr2 = rec_mul(orderings[i][j] + 1, j, 1);
    register int n = x[idx_ret] = x[idx_arr1];
    register int k = y[idx_ret] = y[idx_arr2];
    register int m = y[idx_arr1];
    int amul = 1, cmul = 1;
    if (direction)
        cmul = n;
    else
        amul = k;
    for (int c = 0; c < k; c++)
    {
        register int CM = c * m;
        for (int a = 0; a < n; a++)
        {
            register int AM = a * m;
            register long long x = 0;
            register int b = m;
            while (--b)
                x += arr[idx_arr1][AM + b] * arr[idx_arr2][b + CM];
            x += arr[idx_arr1][AM + b] * arr[idx_arr2][b + CM];
            arr[idx_ret][a * amul + c * cmul] += x;
        }
    }
    return idx_ret;
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
        register int AY = a * y[idx];
        for (register int b = 0; b < y[idx]; b++)
            printf("%lld ", arr[idx][AY + b]);
        printf("\n");
    }
    return 0;
}