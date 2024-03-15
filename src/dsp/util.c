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
