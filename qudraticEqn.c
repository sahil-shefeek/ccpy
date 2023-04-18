#include <stdio.h>
#include <math.h>
int main ()
{
    float a,b,c;
    printf("Enter the coeffecients of x^2 , x and the constant term :\n");
    scanf("%f%f%f",&a,&b,&c);
    float discriminant = (b * b) - (4 * a * c);
    float D = sqrt(discriminant) / (2 * a);
    float coeff = (-b) / (2 * a);
    if (discriminant == 0)
        printf("The roots are real and equal!\nx = %f\n",coeff);
    else if (discriminant > 0)
    {   
        float x1 = coeff + D;
        float x2 = coeff - D;
        printf("The roots are :\nx1 = %f\nx2 = %f\n",x1,x2);
    }
    else
    {   
        D = (sqrt( (4 * a * c) - (b * b) )) / (2 * a);
        printf("The roots are imaginary :\nx1 = %f + i%f\nx2 = %f - i%f\n",coeff,D,coeff,D);
    }
    return 0;

}