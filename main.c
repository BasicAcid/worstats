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
print_dynamic_array(struct DynamicArray arr)
{
    for(size_t i = 0; i < arr.size; i++)
    {
        printf("%f\n", arr.data[i]);
    }
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

    if(type == SAMPLE)
    {
        return result / (double)(arr.size - 1);
    }
    else if(type == POPULATION)
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
    else if(type == POPULATION)
    {
        return sqrt(variance(arr, POPULATION));;
    }
    else
    {
        fprintf(stderr, "Invalid variance type\n");
        exit(EXIT_FAILURE);
    }
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
    /* printf("Left: %d\n", (int)left); */
    /* printf("Right: %d\n", (int)right); */

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
covariance(struct DynamicArray arr1, struct DynamicArray arr2)
{
    // TODO: Check that sizes are equal!

    double mean_arr1 = mean(arr1);
    double mean_arr2 = mean(arr2);

    double result = 0;

    for(size_t i = 0; i < arr1.size; ++i) {
        result += (arr1.data[i] - mean_arr1) * (arr2.data[i] - mean_arr2);
    }

    // TODO:
    // This is for sample covariance, implement the enum flag to switch with population.
    return result / (double)(arr1.size - 1);
}

int
main()
{
    size_t initial_size = 6;
    struct DynamicArray my_array = create_dynamic_array(initial_size);
    struct DynamicArray my_array2 = create_dynamic_array(initial_size);

    my_array.data[0] = 1;
    my_array.data[1] = 2;
    my_array.data[2] = 3;
    my_array.data[3] = 4;
    my_array.data[4] = 5;
    my_array.data[5] = 6;

    my_array2.data[0] = 1;
    my_array2.data[1] = 2;
    my_array2.data[2] = 3;
    my_array2.data[3] = 4;
    my_array2.data[4] = 5;
    my_array2.data[5] = 53;

    /* for (size_t i = 0; i < my_array.size; ++i) { */
    /*     printf("%f\n", my_array.data[i]); */
    /* } */

    /* double test_mean = mean(my_array); */
    /* printf("%f\n", test_mean); */

    /* double s_variance = variance(my_array, SAMPLE); */
    /* printf("%f\n", s_variance); */

    /* double p_variance = variance(my_array, POPULATION); */
    /* printf("%f\n", p_variance); */

    /* double test_std_sample = standard_deviation(my_array, SAMPLE); */
    /* printf("%f\n", test_std_sample); */

    /* double test_std_pop = standard_deviation(my_array, POPULATION); */
    /* printf("%f\n", test_std_pop); */


    //split_merge_sort(my_array);

    //merge_sort_dynamic(&my_array);

    //print_dynamic_array(my_array);

    //printf("%f\n", median(my_array));

    printf("%f\n", covariance(my_array, my_array2));

    free_dynamic_array(&my_array);

    return 0;
}
