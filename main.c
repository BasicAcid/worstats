#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

struct DynamicArray
create_dynamic_array(size_t size)
{
    struct DynamicArray arr;
    arr.data = malloc(size * sizeof(arr));
    arr.size = size;
    return arr;
}

void
print_dynamic_array(struct DynamicArray arr)
{
    for(size_t i = 0; i < arr.size; i++)
        printf("%f\n", arr.data[i]);
}

void
free_dynamic_array(struct DynamicArray *arr)
{
    free(arr->data);
    arr->size = 0;
}

// Absolute value for doubles.
// TODO: find a better method.
double
dabs(double num)
{
    if (num < 0)
        return -num;
    else
        return num;
}

// Newton Raphson implementation
double
sqrt(double input, double epsilon)
{
    double x = input / 2;

    while(dabs(x * x - input) > epsilon)
        x = 0.5 * (x + input / x);

    return x;
}

double
pow(double value, double exponent)
{
    double result = 1;

    for(int i = 0; i < exponent; i++)
        result *= value;

    return result;
}

double
mean(struct DynamicArray arr)
{
    double sum = 0;

    for(size_t i = 0; i < arr.size; ++i)
        sum += arr.data[i];

    double mean = sum / (double)arr.size;

    return mean;
}

// TODO
// Implement geometric mean.

double
variance(struct DynamicArray arr, enum VarianceType type)
{
    double array_mean = mean(arr);
    double result = 0;

    for(size_t i = 0; i < arr.size; i++)
        result += pow(arr.data[i] - array_mean, 2);

    if(type == SAMPLE)
        return result / (double)(arr.size - 1);
    else
        return result / (double)arr.size;
}

double
standard_deviation(struct DynamicArray arr, enum VarianceType type)
{
    if(type == SAMPLE)
        return sqrt(variance(arr, SAMPLE), 0.001);
    else
        return sqrt(variance(arr, POPULATION), 0.001);
}

void
merge(double arr[], size_t left, size_t middle, size_t right)
{
    //printf("merge: left: %d, middle: %d, right: %d\n", (int)left, (int)middle, (int)right);

    size_t left_half_size = middle - left + 1;
    size_t right_half_size = right - middle;

    double temp_left[left_half_size];
    double temp_right[right_half_size];

    // Copy data to temporary array temp_left[].
    for(size_t i = 0; i < left_half_size; i++)
        temp_left[i] = arr[left + i];

    // Copy data to temporary array temp_right[].
    for(size_t j = 0; j < right_half_size; j++)
        temp_right[j] = arr[middle + 1 + j];

    // Merge the temporary arrays back into arr[left..right].
    size_t i = 0; // First subarray index.
    size_t j = 0; // Second subarray index.
    size_t k = left; // Merged subarray index.

    while(i < left_half_size && j < right_half_size)
    {
        if (temp_left[i] <= temp_right[j])
        {
            arr[k] = temp_left[i];
            i++;
        }
        else
        {
            arr[k] = temp_right[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of temp_left[].
    while(i < left_half_size)
    {
        arr[k] = temp_left[i];
        i++;
        k++;
    }

    // Copy the remaining elements of temp_right[].
    while(j < right_half_size)
    {
        arr[k] = temp_right[j];
        j++;
        k++;
    }
}

void
merge_sort(double arr[], size_t left, size_t right)
{
    if(left < right)
    {
        // Better?
        // size_t middle = left + (right - left) / 2;
        size_t middle = (left + right) / 2;

        // Sort halves.
        //printf("merge_sort: left: %d, middle: %d\n", (int)left, (int)middle);
        merge_sort(arr, left, middle);

        //printf("merge_sort: middle+1: %d, right: %d\n", (int)middle+1, (int)right);
        merge_sort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}

void
merge_sort_dynamic(struct DynamicArray *arr)
{
    if(arr->size > 1)
        merge_sort(arr->data, 0, arr->size - 1);
}

// TODO
// Implement quicksort

double
median(struct DynamicArray arr)
{
    // Full sorting is probably not necessary,
    // as we may need only the middle elements.
    merge_sort_dynamic(&arr);

    // If even size.
    if(!(arr.size % 2))
        return (arr.data[(arr.size / 2) - 1] + arr.data[arr.size / 2]) / 2;

    // If odd size.
    return arr.data[arr.size / 2];
}

double
covariance(struct DynamicArray arr1, struct DynamicArray arr2, enum VarianceType type)
{
    if(arr1.size != arr2.size)
    {
        fprintf(stderr, "Covariance error: Arrays are not of equal size:\n");
        fprintf(stderr, "arr1: %d, arr2: %d\n", (int)arr1.size, (int)arr2.size);
        exit(EXIT_FAILURE);
    }

    double mean_arr1 = mean(arr1);
    double mean_arr2 = mean(arr2);

    double result = 0;

    for(size_t i = 0; i < arr1.size; ++i)
        result += (arr1.data[i] - mean_arr1) * (arr2.data[i] - mean_arr2);

    if(type == SAMPLE)
        return result / (double)(arr1.size - 1);
    else
        return result / (double)(arr1.size);
}

unsigned int
fact(unsigned int x)
{
    unsigned int result = 1;

    for(unsigned int i = x; i >= 1; i--)
        result *= i;

    return result;
}

double
sin(double x)
{
    int precision = 15;
    double result = 0.0;
    double term = x;

    for(int i = 3; i <= precision; i = i + 2)
    {
        term = -term * x * x / ((i - 1) * i);
        result += term;
    }
    return result;
}

double
cos(double x)
{
    int precision = 15;
    double result = 0.0;
    double term = x;

    for(int i = 2; i <= precision; i = i + 2)
    {
        term = -term * x * x / ((i - 1) * i);
        result += term;
    }
    return result;
}

double
tan(double x)
{
    unsigned int precision = 15;
    double result = 0.0;
    double term;

    for(unsigned int i = 0; precision < i; ++i)
    {
        term = (2 * i + 1) * (pow(-1, i) * pow(x, 2 * i + 1)) / fact(2 * i + 1);
        result += term;
    }
    return result;
}

// TODO
/* double */
/* permutations(unsigned int a, unsigned int b) */
/* { */

/* } */

// TODO
/* double */
/* combinations() */
/* { */
/* } */

// TODO
/* double */
/* pearson() */
/* { */

/* } */

// TODO
// Add function that generate arrays of numbers based on
// probability distribution (uniform, normal, etc).

struct DynamicArray
uniform_array(long unsigned int size)
{
    struct DynamicArray arr;
    arr.data = malloc(size * sizeof(arr));
    arr.size = size;

    srand((unsigned int)time(NULL)); // Seed.

    for (long unsigned int i = 0; i < size; i++) {
        arr.data[i] = (double)rand() / RAND_MAX;
    }

    return arr;
}

// Natural log.
double
log(double x)
{
    int precision = 15;
    double result = x;
    double term = x;

    for (int i = 1; i <= precision; ++i) {
        result += term;
        term *= (x - 1.0) / i;
    }

    return result;
}

// TODO: box_muller_transform
/* void box_muller_transform(double u1, double u2) */
/* { */
/*     // log(u1); */
/* } */

double
mean_square_error(struct DynamicArray arr, struct DynamicArray arr2)
{
    double result = 0;

    for(unsigned int i = 0; i < arr.size; i++)
        result += (arr.data[i] - arr2.data[i]) * (arr.data[i] - arr2.data[i]);

    return result / (double)arr.size;
}

double
mean_absolute_error(struct DynamicArray arr, struct DynamicArray arr2)
{
    double result = 0;

    for(unsigned int i = 0; i < arr.size; i++)
        result += dabs(arr.data[i] - arr2.data[i]);

    return result / (double)arr.size;
}

int
main()
{
    test_dabs();
    test_sqrt();
    test_pow();
    test_mean();

    return 0;
}
