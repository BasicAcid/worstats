#include <stdio.h>
#include <math.h>

float
mean(float array[])
{
    int size = sizeof(array) / sizeof(array[0]);
    float sum = 0.0;

    for (int i = 0; i < size; i++) {
        sum += array[i];
    }

    return sum/size;
}

float
variance(float array[])
{
    int size = sizeof(array) / sizeof(array[0]);
    float array_mean = mean(array);
    float result;

    for (int i = 0; i < size; i++) {
        result += (array[i] - array_mean)**2;
    }

    return result / size;
}

float
standard_deviation(float array[])
{
    return sqrt(variance(array));
}



int main()
{
    float my_array[] = {2, 8, 4, 12};

    mean(my_array, arraySize);
    return 0;
}
