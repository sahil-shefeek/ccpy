#include <stdio.h>
int main()
{
    int rows, cols;
    printf("Enter the number of rows and columns of matrix:\n");
    scanf("%d%d", &rows, &cols);

    int mat1[rows][cols], mat2[rows][cols], sum[rows][cols];

    printf("Enter the elements of 1st matrix:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            scanf("%d", &mat1[i][j]);
    }
    printf("Enter the elements of 2nd matrix:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            scanf("%d", &mat2[i][j]);
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            sum[i][j] = mat1[i][j] + mat2[i][j];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            printf("%d ", sum[i][j]);
        printf("\n");
    }
}