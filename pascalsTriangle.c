#include <stdio.h>

int main()
{
    int rows;

    printf("Enter the number of rows: ");
    scanf("%d", &rows);

    for (int i = 0; i < rows; i++)
    {
        int element = 1;
        for (int j = 0; j <= i; j++)
        {
            if (j > 0)
                element = element * (i - j + 1) / j;
            printf("%d ", element);
        }
        printf("\n");
    }

    return 0;
}
