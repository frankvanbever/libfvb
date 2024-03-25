#ifndef DSP_UTIL_H
#define DSP_UTIL_H

#include <complex.h>
#include <stddef.h>

/**
 * Pretty print a complex number
 * @param      param
 * @return     Nothing
 */
void print_complex(double complex z);

/**
 * Pretty print a 1D array of complex numbers, each number on it's own line.
 * @param z    An array of complex doubles
 * @param len  The length of the array
 * @return     Nothing
 */
void print_complex_arr(double complex *z, size_t len);

#endif /* DSP_UTIL_H */
