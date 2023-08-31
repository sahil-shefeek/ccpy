//  Patterns :
//  This code represents the pattern :
//      1
//     222
//    33333
//   4444444
//  555555555
// ....   ...n

#include <stdio.h>

int main()
{
    int rows;
    printf("Enter the number of rows: ");
    scanf("%d", &rows);

    for (int row = 0; row < rows; row++)
    {
        int element = 1;
        for (int col = 0; col <= row; col++)
        {
            printf("%d ", element);
            element = element * (row - col) / (col + 1);
        }
        printf("\n");
    }

    return 0;
}
