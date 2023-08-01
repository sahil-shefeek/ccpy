#include <stdio.h>
int main()
{
    int rows, cols, sum = 0;
    printf("Enter the number of rows and columns of matrix:\n");
    scanf("%d%d", &rows, &cols);

    int mat[rows][cols];
    printf("Enter the elements of matrix:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            scanf("%d", &mat[i][j]);
    }
    for (int i = 0; i < rows; i++)
    {

        for (int j = 0; j < cols; j++)
        {
            if (i == j)
                sum += mat[i][j];
        }
    }
    printf("Sum of Diagonal elements : %d\n", sum);
    return 0;
}