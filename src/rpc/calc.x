%#include "../vector/vector.h"
%#include "../vector/error.h"

struct input_vector {
    int y<>;
};

struct output_mean {
    double mean;
    VECTOR_error_t err;
};

struct output_min_max {
    VECTOR_int_pair_t pair;
    VECTOR_error_t err;
};

struct input_scalar_multiplication {
    double a;
    int y<>;
};

struct output_scalar_multiplication {
    double y<>;
    VECTOR_error_t err;
};

program CALC_PROG {
    version CALC_VERS {
        output_mean MEAN(input_vector) = 1;
        output_min_max MIN_MAX(input_vector) = 2;
        output_scalar_multiplication SCALAR_MULTIPLICATION(input_scalar_multiplication) = 3;
    } = 1;
} = 0x23451111;
