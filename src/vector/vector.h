#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <rpc/xdr.h>

#include "error.h"

typedef struct 
{
    int first;
    int second;
}
VECTOR_int_pair_t;

typedef enum 
{
    NO_ERROR,
    NULL_VECTOR,
    INVALID_SIZE,
    MALLOC_FAILURE
}
VECTOR_error_t;

/*
    Prepare for trouble!
    And make it double!
*/
double VECTOR_mean(int const* vector, size_t size, VECTOR_error_t* err);

VECTOR_int_pair_t VECTOR_min_max(int const* vector, size_t size, VECTOR_error_t* err);

double* VECTOR_scalar_multiplication(int const* vector, size_t size, double d, VECTOR_error_t* err);

bool_t xdr_VECTOR_error_t(XDR* xdrs, VECTOR_error_t* e);

bool_t xdr_VECTOR_int_pair_t(XDR* xdrs, VECTOR_int_pair_t* p);
