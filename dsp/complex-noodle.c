#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void print_complex(complex double z) {
        printf("%f+%f*i\n", creal(z), cimag(z));
}

void print_complex_arr(complex double *z, size_t len) {
        for (int i = 0; i < len; i++) {
          print_complex(z[i]);
        }
}

void complex_arithmetic(void) {
        complex double a = 1.0 + 2.0 * I;
        complex double b = 2.0 + 3.0 * I;

        print_complex(a + b);
        print_complex(a - b);
        print_complex(a * b);
        print_complex(a / b);
}

void dft(complex double *x, complex double *X, size_t len) {
        int N = len;
        for (int k = 0; k < len; k++) {
          for (int n = 0; n < len; n++) {
            X[k] += x[n] * cexp(-1 * ((I * 2 * M_PI) / N) * k * n);
          }
        }
}

static int get_even(complex double *x, size_t len, complex double **even) {
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

static int get_odd(complex double *x, size_t len, complex double **odd) {
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

int fft(complex double *x, size_t len, complex double **X) {

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

                if(get_factor(len, &factor)) {
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


static void tostring_binary(uint32_t a, char **bin)
{
        const size_t n = sizeof(a) * 8;
        *bin= malloc(sizeof(char) * (n+1));
        uint32_t mask = 1 << (n-1);
        for (int i = 0; i < n; i++) {
                (*bin)[i] = (a & mask) ? '1' : '0';
                mask = mask >> 1;
        }

        (*bin)[n] = '\0';
}


static void print_bits(uint32_t a)
{
    char *bin = NULL;
    tostring_binary(a, &bin);
    printf("%s\n", bin);
    free(bin);
}

static uint32_t rev(const uint32_t a, size_t len) {
        uint32_t num_of_bits = log2(len);
        uint32_t mask = 1 << (num_of_bits-1);
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
                            size_t len) {
  for (int i = 0; i < len; i++) {
      X[rev(i, len)] = x[i];
  }

  return 0;
}

int iterative_fft(const complex double *const x, complex double *X,
                  size_t len) {

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
                for (int j = 0; j < m/2; j++) {
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

int main(void) {
  const int num_samples = 8;

  complex double x[num_samples];
  complex double X_dft[num_samples];
  complex double *X_fft;

  complex double X_iter_fft[num_samples];

  double _Complex foo = 1.0 + 2.0 * I;
  // print_complex(foo);

  /* complex_arithmetic(); */

  for (int i = 0; i < num_samples; i++) {
    x[i] = 1.0 * i + 1.0 * i * I;
  }

  /* print_complex_arr(x, num_samples); */
  /* printf("-----------\n"); */

  /* complex double *even = get_even(x, num_samples); */
  /* print_complex_arr(even, (num_samples / 2) + 1); */

  /* printf("-----------\n"); */

  /* complex double *odd = get_odd(x, num_samples); */
  /* print_complex_arr(odd, num_samples / 2); */

  /* complex double *factor = get_factor(10); */
  /* print_complex_arr(factor, 10); */

  /* printf("-----------\n"); */

  /* dft(x, X_dft, num_samples); */
  /* print_complex_arr(X_dft, num_samples); */

  /* printf("-----------\n"); */

  fft(x, num_samples, &X_fft);
  print_complex_arr(X_fft, num_samples);
  free(X_fft);

  printf("-----------\n");

  /* print_complex_arr(x, num_samples); */
  /* printf("----------\n"); */
  /* bit_reverse_copy(x, X_iter_fft, num_samples); */
  iterative_fft(x, X_iter_fft, num_samples);
  print_complex_arr(X_iter_fft, num_samples);


  return 0;
}