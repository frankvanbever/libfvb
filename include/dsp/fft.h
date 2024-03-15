#ifndef FVB_FFT_H
#define FVB_FFT_H

#include <complex.h>
#include <stddef.h>

/**
 * Discrete Fourier Transform
 * @param x    An array of samples
 * @param X    The DFT output
 * @param len  The number of samples
 * @return     Nothing
 */
void dft(double complex *x, double complex *X, size_t len);

/**
 * Recursive Fast Fourier Transform
 *
 * @return     return type
 */
int fft(double complex *x, double complex **X, size_t len);
int iterative_fft(const double complex *const x, double complex *X, size_t len);

#endif /* FVB_FFT_H */
