//  Code represents the qn :
//  Q.  While puschasing certain items, a discount of 10%
//      is offered it the quantity purchased is more than 1000.
//      WAP to calculate the total expenses. Quantity purchased and amount per quantity is user provided (stdin).

#include <stdio.h>
int main()
{
    int qty;
    float amt, Total;

    printf("Enter the quantity of item purchased : ");
    scanf("%d", &qty);
    printf("Enter the price per item : ");
    scanf("%f", &amt);
    Total = qty * amt;
    if (Total > 1000)
        Total -= (Total * 0.1);
    printf("Your total is : %f\n", Total);
    return 0;
}