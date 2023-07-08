//  Sum of the series :
//   This code represents the series : 1 + 11 + 111 + 1111 + .... + n
//   where the limit 'n' is provided by user input (stdin).
//   The program finds the sum of the above the series upto 'n' terms.

#include <stdio.h>

int main()
{
    int n;
    printf("Enter the limit : ");
    scanf("%d", &n);
    printf("The series is :");
    int sum = 0, term = 0;
    for (int i = 0; i < n; i++)
    {
        term = term * 10 + 1;
        printf(" %d", term);
        if (i < n - 1)
            printf(" +");
        sum += term;
    }
    printf("\nThe sum of the series is : %d\n", sum);
    return 0;
}
