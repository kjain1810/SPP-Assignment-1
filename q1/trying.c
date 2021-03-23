#include <stdio.h>
#include <stdlib.h>

int *colmajor(int x, int y, int *arr)
{
    int *ret = (int *)malloc(x * y * sizeof(int));
    for (int a = 0; a < x; a++)
        for (int b = 0; b < y; b++)
            ret[b * x + a] = arr[a * y + b];
    return ret;
}
int main()
{
    int x, y;
    scanf("%d%d", &x, &y);
    int *arr = (int *)malloc(x * y * sizeof(int));
    for (int a = 0; a < x; a++)
        for (int b = 0; b < y; b++)
            scanf("%d", &arr[a * y + b]);
    for (int a = 0; a < x * y; a++)
        printf("%d ", arr[a]);
    printf("\n");
    arr = colmajor(x, y, arr);
    for (int a = 0; a < y; a++)
    {
        for (int b = 0; b < x; b++)
            printf("%d ", arr[a * x + b]);
        printf("\n");
    }
    for (int a = 0; a < x * y; a++)
        printf("%d ", arr[a]);
    printf("\n");
    return 0;
}