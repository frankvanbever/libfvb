/*
 *
 *  Copyright 2024 Frank Vanbever
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
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
