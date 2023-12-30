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
mean(struct DynamicArray arr)
{
    double sum = 0;

    for(size_t i = 0; i < arr.size; ++i)
    {
        sum += arr.data[i];
    }

    double mean = sum / (double)arr.size;

    return mean;
}

double
sample_variance(struct DynamicArray arr)
{
    double array_mean = mean(arr);
    double result = 0;

    for(size_t i = 0; i < arr.size; i++)
    {
        result += pow(arr.data[i] - array_mean, 2);
    }

    return result / (double)(arr.size - 1);
}

double
population_variance(struct DynamicArray arr)
{
    double array_mean = mean(arr);
    double result = 0;

    for(size_t i = 0; i < arr.size; i++)
    {
        result += pow(arr.data[i] - array_mean, 2);
    }

    return result / (double)arr.size;
}

/* float */
/* standard_deviation(float array[]) */
/* { */
/*     return sqrt(variance(array)); */
/* } */

int
main()
{
    size_t initialSize = 5;

    struct DynamicArray my_array = create_dynamic_array(initialSize);

    for (size_t i = 0; i < my_array.size; ++i) {
        my_array.data[i] = 2 * (double)i;
    }

    for (size_t i = 0; i < my_array.size; ++i) {
        printf("%f\n", my_array.data[i]);
    }

    double test_mean = mean(my_array);
    printf("%f\n", test_mean);

    double test_variance = sample_variance(my_array);
    printf("%f\n", test_variance);

    free_dynamic_array(&my_array);

    return 0;
}
