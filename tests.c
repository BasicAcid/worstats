#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "main.h"

void
test_dabs()
{
    double x = -1.0;
    assert(dabs(x) == 1.0);
}

void
test_sqrt()
{
    assert( dabs(sqrt(2, 0.001) - 1.414216) < 1e-6);
}

void
test_pow()
{
    assert( pow(2, 3) == 8);
}

void test_mean()
{
    struct DynamicArray arr = create_dynamic_array(5);
    arr.data[0] = 1;
    arr.data[1] = 2;
    arr.data[2] = 3;
    arr.data[3] = 4;
    arr.data[4] = 5;

    double expected = 3;
    double actual = mean(arr);

    assert(dabs(expected - actual) < 0.00001);

    free(arr.data);
}

void test_variance()
{

}

void test_std()
{

}

void test_median()
{

}

void test_covariance()
{

}

void test_fact()
{

}

void test_sin()
{

}


void test_cos()
{

}

void test_tan()
{

}

void test_log()
{

}

void test_msr()
{

}

void test_mas()
{

}



void
tests()
{
    size_t initial_size = 6;
    struct DynamicArray my_array = create_dynamic_array(initial_size);
    struct DynamicArray my_array2 = create_dynamic_array(initial_size);

    my_array.data[0] = 0;
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
    my_array2.data[5] = 1;

    double test_mean = mean(my_array);
    printf("%f\n", test_mean);

    double s_variance = variance(my_array, SAMPLE);
    printf("%f\n", s_variance);

    double p_variance = variance(my_array, POPULATION);
    printf("%f\n", p_variance);

    double test_std_sample = standard_deviation(my_array, SAMPLE);
    printf("%f\n", test_std_sample);

    double test_std_pop = standard_deviation(my_array, POPULATION);
    printf("%f\n", test_std_pop);

    double test_msr = mean_square_error(my_array, my_array2);
    printf("%f\n", test_msr);

    //split_merge_sort(my_array);

    //merge_sort_dynamic(&my_array);

    //print_dynamic_array(my_array);

    //printf("%f\n", median(my_array));

    printf("%f\n", sqrt(5.0, 0.0001));

    /* printf("%f\n", covariance(my_array, my_array2, SAMPLE)); */

    free_dynamic_array(&my_array);
    free_dynamic_array(&my_array2);

    uniform_array(10);
}
