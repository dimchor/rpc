#pragma once

#include <stddef.h>
#include <stdlib.h>

#include "error.h"

typedef struct 
{
    int first;
    int second;
}
VECTOR_int_pair_t;

/*
    Prepare for trouble!
    And make it double!
*/
double VECTOR_mean(int const* vector, size_t size, VECTOR_error_t* err);

VECTOR_int_pair_t VECTOR_min_max(int const* vector, size_t size, VECTOR_error_t* err);

double* VECTOR_scalar_multiplication(int const* vector, size_t size, double d, VECTOR_error_t* err);
