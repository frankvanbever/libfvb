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
#include <complex.h>
#include <stddef.h>
#include <stdio.h>

void print_complex(complex double z)
{
	printf("%f+%f*i\n", creal(z), cimag(z));
}

void print_complex_arr(complex double *z, size_t len)
{
	for (int i = 0; i < len; i++) {
		print_complex(z[i]);
	}
}
