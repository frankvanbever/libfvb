#include <complex.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void dft(complex double *x, complex double *X, size_t len)
{
	int N = len;
	if (N == 0)
		return;
	for (int k = 0; k < len; k++) {
		X[k] = 0.0f;
		for (int n = 0; n < len; n++) {
			long double exponent = (-2.0L * M_PI * k * n) / N;
			X[k] += x[n] * cexp(I * exponent);
		}
	}
}

static int get_even(complex double *x, size_t len, complex double **even)
{
	size_t N = (len / 2) + (len % 2);

	*even = malloc(N * sizeof(complex double));
	if (*even == NULL) {
		return -1;
	}

	for (int i = 0; i < N; i++) {
		(*even)[i] = x[i * 2];
	}

	return 0;
}

static int get_odd(complex double *x, size_t len, complex double **odd)
{
	size_t N = len / 2;

	*odd = malloc(N * sizeof(complex double));
	if (*odd == NULL) {
		return -1;
	}

	for (int i = 0; i < N; i++) {
		(*odd)[i] = x[(i * 2) + 1];
	}

	return 0;
}

static int get_factor(int N, complex double **factor)
{
	*factor = malloc(N * sizeof(complex double));
	if (*factor == 0) {
		return -1;
	}

	for (int i = 0; i < N; i++) {
		(*factor)[i] = cexp(-2 * I * i * M_PI / N);
	}

	return 0;
}

int fft(complex double *x, size_t len, complex double **X)
{
	int ret = -1;
	complex double *x_even = NULL;
	complex double *x_odd = NULL;

	complex double *X_even = NULL;
	complex double *X_odd = NULL;

	complex double *factor = NULL;

	*X = malloc(len * sizeof(complex double));
	if (*X == NULL) {
		goto cleanup;
	}

	if (len == 1) {
		(*X)[0] = x[0];
		return 0;
	} else {
		if (get_even(x, len, &x_even)) {
			goto cleanup;
		}
		if (get_odd(x, len, &x_odd)) {
			goto cleanup;
		}

		if (fft(x_even, len / 2, &X_even)) {
			goto cleanup;
		}

		if (fft(x_odd, len / 2, &X_odd)) {
			goto cleanup;
		}

		if (get_factor(len, &factor)) {
			goto cleanup;
		}

		for (int i = 0; i < len; i++) {
			int index = i % (len / 2);
			(*X)[i] = X_even[index] + X_odd[index] * factor[i];
		}
	}

	ret = 0;

cleanup:
	if (x_even)
		free(x_even);
	if (x_odd)
		free(x_odd);
	if (X_even)
		free(X_even);
	if (X_odd)
		free(X_odd);
	if (factor)
		free(factor);

	return ret;
}

static uint32_t rev(const uint32_t a, size_t len)
{
	uint32_t num_of_bits = log2(len);
	uint32_t mask = 1 << (num_of_bits - 1);
	uint32_t reversed = 0;
	for (int i = 0; i < num_of_bits; i++) {
		if ((a & mask) != 0) {
			reversed = reversed | (1 << i);
		}
		mask = mask >> 1;
	}

	return reversed;
}

static int bit_reverse_copy(const complex double *const x, complex double *X,
			    size_t len)
{
	for (int i = 0; i < len; i++) {
		X[rev(i, len)] = x[i];
	}

	return 0;
}

int iterative_fft(const complex double *const x, complex double *X, size_t len)
{
	complex double w_m = 0.0;
	complex double w = 0.0;
	complex double t = 0.0;
	complex double u = 0.0;
	int m = 0;

	bit_reverse_copy(x, X, len);
	for (int s = 1; s <= log2(len); s++) {
		m = pow(2, s);
		w_m = cexp(-2 * M_PI * I / m);
		for (int k = 0; k < len; k += m) {
			w = 1.0;
			for (int j = 0; j < m / 2; j++) {
				t = w * X[k + j + m / 2];
				u = X[k + j];
				X[k + j] = u + t;
				X[k + j + m / 2] = u - t;
				w = w * w_m;
			}
		}
	}

	return 0;
}
