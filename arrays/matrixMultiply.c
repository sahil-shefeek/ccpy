#include <stdio.h>
int main()
{
    int aRows, aCols, bRows, bCols;
    printf("Enter the number of columns and rows of first matrix:");
    scanf("%d%d", &aRows, &aCols);
    printf("Enter the number of columns and rows of second matrix:");
    scanf("%d%d", &bRows, &bCols);
    if (aCols == bRows)
    {
        int a[aRows][aCols], b[bRows][bCols], res[aCols][bRows];
        printf("Enter the elements of first matrix:");
        for (int i = 0; i < aRows; i++)
        {
            for (int j = 0; j < aCols; j++)
                scanf("%d", &a[i][j]);
        }
        printf("Enter the elements of second matrix:");
        for (int i = 0; i < bRows; i++)
        {
            for (int j = 0; j < bCols; j++)
                scanf("%d", &b[i][j]);
        }

        for (int i = 0; i < aRows; i++)
        {
            for (int j = 0; j < aCols; j++)
            {
                for (int k = 0; k < aCols; k++)
                {
                    res[i][k] += a[i][k] * b[k][i];
                }
            }
        }

        printf("Product is:\n");
        for (int i = 0; i < bRows; i++)
        {
            for (int j = 0; j < bCols; j++)
                printf("%d\t", b[i][j]);
            printf("\n");
        }
    }
}