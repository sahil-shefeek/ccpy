#include <stdio.h>
int main()
{
    int rows, cols;
    printf("Enter the number of rows and columns of matrix:\n");
    scanf("%d%d", &rows, &cols);

    int mat[rows][cols];
    printf("Enter the elements of matrix:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            scanf("%d", &mat[i][j]);
    }
    for (int i = 0, temp = 0; i < rows; i++, temp++)
    {

        for (int j = 0; j < cols; j++)
        {
            if (j >= temp)
                printf("%d\t", mat[i][j]);
            else
                printf("\t");
        }
        printf("\n");
    }
    return 0;
}