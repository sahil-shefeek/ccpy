#include <stdio.h>
#include <stdlib.h>

int main() {
    int *a = (int *) malloc(sizeof(int));
    int *b = (int *) malloc(sizeof(int));
    int *c = (int *) malloc(sizeof(int));

    printf("Enter any three numbers : ");
    scanf("%d%d%d", a, b, c);

    if (*a > *b) {
        if (*a > *c)
            printf("%d is largest\n", a);
        else
            printf("%d is largest\n", c);
    } else {
        if (*b > *c)
            printf("%d is largest\n", b);
        else
            printf("%d is largest\n", c);
    }

    free(a);
    free(b);
    free(c);

    return 0;
}