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
