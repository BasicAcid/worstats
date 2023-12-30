#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct DynamicArray {
    double *data;
    size_t size;
};

struct DynamicArray
create_dynamic_array(size_t size)
{
    struct DynamicArray arr;
    arr.data = (double *)malloc(size * sizeof(double));
    arr.size = size;
    return arr;
}

void
free_dynamic_array(struct DynamicArray *arr)
{
    free(arr->data);
    arr->size = 0;
}

double
mean(struct DynamicArray array)
{
    double sum = 0;

    for (size_t i = 0; i < array.size; ++i) {
        sum += array.data[i];
    }

    double mean = sum / (double)array.size;

    return mean;
}

/* float */
/* variance(float array[]) */
/* { */
/*     int size = sizeof(array) / sizeof(array[0]); */
/*     float array_mean = mean(array); */
/*     float result; */

/*     for (int i = 0; i < size; i++) { */
/*         result += (array[i] - array_mean)**2; */
/*     } */

/*     return result / size; */
/* } */

/* float */
/* standard_deviation(float array[]) */
/* { */
/*     return sqrt(variance(array)); */
/* } */

int
main()
{
    size_t initialSize = 10;

    struct DynamicArray myArray = create_dynamic_array(initialSize);

    for (size_t i = 0; i < myArray.size; ++i) {
        myArray.data[i] = 2.303984 * (double)i;
    }

    for (size_t i = 0; i < myArray.size; ++i) {
        printf("%f\n", myArray.data[i]);
    }

    free_dynamic_array(&myArray);

    return 0;
}
