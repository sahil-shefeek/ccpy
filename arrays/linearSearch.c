#include <stdio.h>

int main()
{
    int element, size, arr[1000];
    printf("Enter the array size : ");
    scanf("%d", &size);
    printf("Enter the element to search : ");
    scanf("%d", &element);
    printf("Enter the array elements :\n");

    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    for (int i = 0; i < size; i++)
    {
        if (arr[i] == element)
        {
            printf("Found %d at index %d\n", element, i);
            return 0;
        }
    }
    printf("The entered element %d was not found in the given array.\n");
    return 0;
}