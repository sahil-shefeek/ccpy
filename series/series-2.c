//  Sum of the series :
//   This code represents the Taylor series expansion for cosine(x),
//       1 − (x^2)/2! + (x^4)/4! − (x^6)/6! ...
//   where the limit 'n' is provided by user input (stdin).
//   The program finds the sum of the above the series upto 'n' terms.

#include <stdio.h>
#include <math.h>
#define PI 3.141592

int main()
{
    int n;
    double deg, rad, term, sum = 0, fact = 1;
    printf("Taylor series expansion for cos(x).\n");
    printf("Enter the angle, 'x' (in degrees): ");
    scanf("%lf", &deg);
    printf("Enter the number of terms to compute (accuracy): ");
    scanf("%d", &n);
    rad = deg * (PI / 180);

    for (int i = 0; i <= n; i++)
    {
        double fact = 1;
        for (int j = 1; j <= i; j++)
            fact *= j;
        term = pow(-1, i) * (pow(rad, 2 * i) / fact);
        sum += term;
    }
    printf("The calculated sum is: %lf\n", sum);
    return 0;
}
