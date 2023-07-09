#include <stdio.h>

int main()
{
    int element, size, arr[1000], occurrence = 0;
    printf("Enter the array size : ");
    scanf("%d", &size);
    printf("Enter the element to find occurrences for : ");
    scanf("%d", &element);
    printf("Enter the array elements :\n");

    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    for (int i = 0; i < size; i++)
    {
        if (arr[i] == element)
            occurrence++;
    }

    if (occurrence)
        printf("The entered element %d occured %d times.\n", element, occurrence);
    else
        printf("ERR: The entered element %d was not found in the given array.\n", element);
    return 0;
}