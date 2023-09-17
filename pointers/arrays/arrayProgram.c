//
// This program contains complex ideas based on arrays.
// All elements are assumed to be integers.
//

#include <stdio.h>
#include <stdlib.h>

int *create_int_array(int size) {
    int *arr = (int *) malloc((size) * sizeof(int));
    if (arr == NULL) {
        printf("ERR: Array creation failed!\n");
        exit(1);
    }
    return arr;
}


void enter_array_elements(int *arr, int size) {
    printf("Enter array elements :\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", arr + i);
    }
}

int ascending(int *a, int *b) {
    return (*a) - (*b);
}


int descending(int *a, int *b) {
    return (*b) - (*a);
}

void bubble_sort(int *arr, int size, int (*compare)(int *, int *)) {
    for (int i = 0; i <= size; i++) {
        for (int j = 0; j < size; j++)
            if (compare(arr + j, arr + j + 1) > 1) {
                int temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
    }
}

void print_array(int *arr, int size) {
    for (int i = 0; i < size; i++)
        printf("%d\t", *(arr + i));
}

int main() {
    int state, order, size, new_size;
    printf("Complex array program\n");
    printf("Enter the array size :\n");
    scanf("%d", &size);
    int *arr = create_int_array(size);
    enter_array_elements(arr, size);
    op:
    printf("Specify array operation :\n");
    printf("1. Bubble Sort\n2. Add more elements\n3. Exit\n");
    scanf("%d", &state);
    switch (state) {
        case 1:
            printf("Specify sort order :\n1. Ascending\n2. Descending\n");
            scanf("%d", &order);
            if (order == 1)
                bubble_sort(arr, size, ascending);
            if (order == 2)
                bubble_sort(arr, size, descending);
            break;
        case 2:
            printf("Enter number of elements to be added :\n");
            scanf("%d", &new_size);
            int *arr_new = realloc(arr, new_size);
            if (arr_new == NULL){
                printf("ERR: Failed to add new elements.\n");
                exit(1);
            }
            printf("Enter new array elements :\n");
            for (int i = size; i < new_size; i++)
                scanf("%d", arr_new + i);
            printf("Elements added successfully.\n");
            free(arr);
            goto op;
        case 3:
            exit(0);
        default:
            printf("Invalid choice!\nPlease try again.\n");
            goto op;

    }
    print_array(arr, size);
    free(arr);

    return 0;
}
