#include <stddef.h>

// See for optimizations:
// https://youtu.be/443UNeGrFoM?si=4PzWk8W_bN0BQHEF&t=6325
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

struct DynamicArray create_dynamic_array(size_t size);
void print_dynamic_array(struct DynamicArray arr);
void free_dynamic_array(struct DynamicArray *arr);
double dabs(double num);
double sqrt(double input, double epsilon);
double pow(double value, double exponent);
double mean(struct DynamicArray arr);
double variance(struct DynamicArray arr, enum VarianceType type);
double standard_deviation(struct DynamicArray arr, enum VarianceType type);
void merge(double arr[], size_t left, size_t middle, size_t right);
void merge_sort(double arr[], size_t left, size_t right);
void merge_sort_dynamic(struct DynamicArray *arr);
double median(struct DynamicArray arr);
double covariance(struct DynamicArray arr1, struct DynamicArray arr2, enum VarianceType type);
unsigned int fact(unsigned int x);
double sin(double x);
double cos(double x);
double tan(double x);
struct DynamicArray uniform_array(long unsigned int size);
double log(double x);
double mean_square_error(struct DynamicArray arr, struct DynamicArray arr2);
double mean_absolute_error(struct DynamicArray arr, struct DynamicArray arr2);
