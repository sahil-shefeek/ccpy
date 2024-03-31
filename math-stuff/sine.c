//  Sum of the series :
//   This code represents the Taylor series expansion for sine(x),
//       1 − (x^3)/3! + (x^5)/5! − (x^7)/7! ...
//   where the limit 'n' is provided by user input (stdin).
//   The program finds the sum of the above the series upto 'n' terms.

#include <stdio.h>
#include <math.h>
#define PI 3.141592

int main()
{
    int n;
    double deg, rad, term, sum = 0;
    printf("Taylor series expansion for sin(x).\n");
    printf("Enter the angle, 'x' (in degrees): ");
    scanf("%lf", &deg);
    printf("Enter the number of terms to compute (accuracy): ");
    scanf("%d", &n);
    rad = deg * (PI / 180);

    for (int i = 0; i <= n; i++)
    {
        double fact = 1;
        for (int j = 1; j <= (2 * i + 1); j++)
            fact *= j;
        term = pow(-1, i) * (pow(rad, 2 * i + 1) / fact);
        sum += term;
    }
    printf("The calculated sum is: %lf\n", sum);
    return 0;
}