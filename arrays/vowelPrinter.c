// Program assumes the given input is of lowercase

#include <stdio.h>

#include <stdio.h>

int main()
{
    int size;
    char arr[1000], vowels[5] = {'a', 'e', 'i', 'o', 'u'};
    printf("Enter the array size: ");
    scanf("%d", &size);
    printf("Enter the array elements (char):\n");

    for (int i = 0; i < size; i++)
        scanf(" %c", &arr[i]);

    printf("Vowels in the array: ");

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (arr[i] == vowels[j])
                printf("%c ", arr[i]);
        }
    }

    printf("\n");

    return 0;
}
