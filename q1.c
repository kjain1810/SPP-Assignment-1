#include <stdio.h>

int n;
int *x, *y;
int ***arr;

void input()
{
    scanf("%d", &n);
    x = (int *)malloc(n * sizeof(int));
    y = (int *)malloc(n * sizeof(int));
    arr = (int ***)malloc(n * sizeof(int **));
    for (int a = 0; a < n; a++)
    {
        scanf("%d%d", &x[a], &y[a]);
        arr[a] = (int **)malloc(x[a] * sizeof(int *));
        for (int b = 0; b < x; b++)
        {
            arr[a][b] = (int *)malloc(y[a] * sizeof(int));
            for (int c = 0; c < y; c++)
                scanf("%d", &arr[a][b][c]);
        }
    }
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
    return 0;
}