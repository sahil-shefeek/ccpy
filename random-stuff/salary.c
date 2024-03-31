#include <stdio.h>
int main ()
{
	float basicPay,DA,HRA;
	printf("Enter your basic payout :\n");
	scanf("%f",&basicPay);
	if (basicPay <= 25000)
	{
		DA = 0.1;
		HRA = 0.15;
	} 
	else if (basicPay <= 40000)
	{
		DA = 0.12;
		HRA = 0.18;
	}
	 else
	{	
		DA = 0.15;
		HRA = 0.2;
	}

	float grossSalary = basicPay + DA*basicPay + HRA*basicPay;
	printf("Your gross salary payout is : %f\n",grossSalary);
	return 0;


}
