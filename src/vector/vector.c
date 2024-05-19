#include "vector.h"

double VECTOR_mean(int const* vector, size_t size, VECTOR_error_t* err)
{
    if (!vector)
    {
        *err = NULL_VECTOR;
        return .0;
    }

    if (size < 1)
    {
        *err = INVALID_SIZE;
        return .0;
    }

    int sum = 0;
    for (size_t i = 0; i < size; ++i)
        sum += vector[i];

    *err = NO_ERROR;
    return (double) sum / size;
}

VECTOR_int_pair_t VECTOR_min_max(int const* vector, size_t size, VECTOR_error_t* err)
{
    if (!vector)
    {
        *err = NULL_VECTOR;
        return (VECTOR_int_pair_t){0, 0};
    }

    if (size < 1)
    {
        *err = INVALID_SIZE;
        return (VECTOR_int_pair_t){0, 0};
    }  
    
    VECTOR_int_pair_t r;

    // min
    r.first = *vector;

    //max
    r.second = *vector;

    for (size_t i = 1; i < size; ++i)
    {
        if (vector[i] < r.first)
            r.first = vector[i];

        if (vector[i] > r.second)
            r.second = vector[i];
    }

    *err = NO_ERROR;
    return r;
}

double* VECTOR_scalar_multiplication(int const* vector, size_t size, double d, VECTOR_error_t* err)
{
    if (!vector)
    {
        *err = NULL_VECTOR;
        return NULL;
    }

    if (size < 1)
    {
        *err = INVALID_SIZE;
        return NULL;
    }

    double* d_vector = malloc(size * sizeof(double));
    if (!d_vector)
    {
        *err = MALLOC_FAILURE;
        return NULL;
    }

    for (size_t i = 0; i < size; ++i)
        d_vector[i] = d * vector[i];

    *err = NO_ERROR;
    return d_vector;
}

bool_t xdr_VECTOR_error_t(XDR* xdrs, VECTOR_error_t* e)
{
    if (!xdr_int(xdrs, (int*) e))
        return FALSE;
    return TRUE;
}

bool_t xdr_VECTOR_int_pair_t(XDR* xdrs, VECTOR_int_pair_t* p)
{
    if (!xdr_int(xdrs, &p->first))
        return FALSE;
    if (!xdr_int(xdrs, &p->second))
        return FALSE;
    return TRUE;
}
