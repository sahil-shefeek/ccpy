#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define PI 3.141592

int main()
{
    int n, option, state;
    double deg, rad, term;
    do
    {
        printf("Enter the angle, 'x' (in degrees): ");
        scanf("%lf", &deg);
        printf("Enter the number of terms to compute (accuracy): ");
        scanf("%d", &n);

    choice:
        printf("Select operation : \n");
        printf("1. sin(x).\n2. cos(x).\n");
        scanf("%d", &option);
        double sum = 0;
        rad = deg * (PI / 180);

        switch (option)
        {
        case 1:
            for (int i = 0; i <= n; i++)
            {
                double fact = 1;
                for (int j = 1; j <= (2 * i + 1); j++)
                    fact *= j;
                term = pow(-1, i) * (pow(rad, 2 * i + 1) / fact);
                sum += term;
            }
            break;

        case 2:
            for (int i = 0; i <= n; i++)
            {
                double fact = 1;
                for (int j = 1; j <= (2 * i); j++)
                    fact *= j;
                term = pow(-1, i) * (pow(rad, 2 * i) / fact);
                sum += term;
            }
            break;

        default:
            printf("ERR: Invalid selection try again");
            goto choice;
        }

        printf("The calculated sum is: %lf\n", sum);
        printf("Perform another opration?\n1. Yes\n2. No\n");
        scanf("%d", &state);
        if (state == 2)
            return 0;
    } while (true);
}