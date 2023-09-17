#include <stdio.h>
#include <stdlib.h>

int main() {
    int *a = (int *) malloc(sizeof(int));
    int *b = (int *) malloc(sizeof(int));

    printf("Enter any two numbers : ");
    scanf("%d%d", a, b);

    if (*a > *b)
        printf("%d is greater than %d\n", *a, *b);
    else
        printf("%d is greater than %d\n", *b, *a);
    free(a);
    free(b);
    return 0;
}