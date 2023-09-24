#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *size = (int *)malloc(sizeof(int));
    printf("Enter array size :");
    scanf("%d", size);
    int *arr = (int *)malloc((*size) * sizeof(int));
    
}