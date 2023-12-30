#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct DynamicArray
{
    double *data;
    size_t size;
};

enum VarianceType
{
    SAMPLE,
    POPULATION
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
variance(struct DynamicArray arr, enum VarianceType type)
{
    double array_mean = mean(arr);
    double result = 0;

    for(size_t i = 0; i < arr.size; i++)
    {
        result += pow(arr.data[i] - array_mean, 2);
    }

    if (type == SAMPLE)
    {
        return result / (double)(arr.size - 1);
    }
    else if (type == POPULATION)
    {
        return result / (double)arr.size;
    }
    else
    {
        fprintf(stderr, "Invalid variance type\n");
        exit(EXIT_FAILURE);
    }
}

double
standard_deviation(struct DynamicArray arr, enum VarianceType type)
{
    if (type == SAMPLE)
    {
        return sqrt(variance(arr, SAMPLE));;
    }
    else if (type == POPULATION)
    {
        return sqrt(variance(arr, POPULATION));;
    }
    else
    {
        fprintf(stderr, "Invalid variance type\n");
        exit(EXIT_FAILURE);
    }
}

int
main()
{
    size_t initialSize = 5;

    struct DynamicArray my_array = create_dynamic_array(initialSize);

    for (size_t i = 0; i < my_array.size; ++i) {
        my_array.data[i] = 2 * (double)i;
    }

    /* for (size_t i = 0; i < my_array.size; ++i) { */
    /*     printf("%f\n", my_array.data[i]); */
    /* } */

    /* double test_mean = mean(my_array); */
    /* printf("%f\n", test_mean); */

    double s_variance = variance(my_array, SAMPLE);
    printf("%f\n", s_variance);

    double p_variance = variance(my_array, POPULATION);
    printf("%f\n", p_variance);

    double test_std_sample = standard_deviation(my_array, SAMPLE);
    printf("%f\n", test_std_sample);

    double test_std_pop = standard_deviation(my_array, POPULATION);
    printf("%f\n", test_std_pop);

    free_dynamic_array(&my_array);

    return 0;
}
