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

static complex double *get_even(complex double *x, size_t len) {
        size_t N = (len / 2) + (len % 2);

        complex double *even = malloc(N * sizeof(complex double));

        for (int i = 0; i < N; i++) {
          even[i] = x[i * 2];
        }

        return even;
}

static complex double *get_odd(complex double *x, size_t len) {
        size_t N = len / 2;
        complex double *odd = malloc(N * sizeof(complex double));

        for (int i = 0; i < N; i++) {
          odd[i] = x[(i * 2) + 1];
        }

        return odd;
}

static complex double *get_factor(int N) {
        complex double *factor = malloc(N * sizeof(complex double));
        for (int i = 0; i < N; i++) {
          factor[i] = cexp(-2 * I * i * M_PI / N);
        }

        return factor;
}

complex double *fft(complex double *x, size_t len) {
        complex double *X = malloc(len * sizeof(complex double));

        complex double *x_even = NULL;
        complex double *x_odd = NULL;

        complex double *X_even = NULL;
        complex double *X_odd = NULL;

        if (len == 1) {
          return x;
        } else {
          x_even = get_even(x, len);
          x_odd = get_odd(x, len);

          X_even = fft(x_even, len / 2);
          X_odd = fft(x_odd, len / 2);

          complex double *factor = get_factor(len);

          for (int i = 0; i < len; i++) {
            int index = i % (len / 2);
            X[i] = X_even[index] + X_odd[index] * factor[i];
          }
        }

        return X;
}


static void tostring_binary(uint32_t a, char **bin)
{
        const size_t n = sizeof(a) * 8;
        printf("n is %zu\n", n);
        *bin= malloc(sizeof(char) * (n+1));
        uint32_t mask = 1 << (n-1);
        for (int i = 0; i < n; i++) {
                (*bin)[i] = (a & mask) ? '1' : '0';
                mask = mask >> 1;
        }

        (*bin)[n] = '\0';
}

static int rev(int a, size_t num_of_bits) {
        for (int i = 0; i < num_of_bits; i++) {
          int mask = 1 << i;
        }

        return 0;
}

/* static int bit_reverse_copy(const complex double *const x, complex double *X, */
/*                             size_t len) { */
/*   for (int i = 0; i < len; i++) { */
/*     X[rev(i)] = x[i]; */
/*   } */

/*   return 0; */
/* } */

/* int iterative_fft(const complex double *const x, complex double *X, */
/*                   size_t len) { */
/*   bit_reverse_copy(x, X, len); */
/*   for (int s = 1; s < log(len); s++) { */
/*     int m = 2 ^ s; */
/*     complex double w_m = cexp(-2 * M_PI / m); */
/*     for (int k = 0; k < len; k++) { */
/*       complex double w = 1.0; */
/*       for (int j = 0; j < m / 2 - 1; j++) { */
/*         complex double t = w * X[k + j + m / 2]; */
/*         complex double u = X[k + j]; */
/*         X[k + j] = u + t; */
/*         X[k + j + m / 2] = u - t; */
/*         w = w * w_m; */
/*       } */
/*     } */
/*   } */

/*   return 0; */
/* } */

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

  complex double *factor = get_factor(10);
  print_complex_arr(factor, 10);

  printf("-----------\n");

  dft(x, X_dft, num_samples);
  print_complex_arr(X_dft, num_samples);

  printf("-----------\n");

  X_fft = fft(x, num_samples);
  print_complex_arr(X_fft, num_samples);

  printf("-----------\n");

  /* iterative_fft(x, X_iter_fft, num_samples); */
  /* print_complex_arr(X_iter_fft, num_samples); */

  printf("%d\n", rev(5,3));

  char *binstr = NULL;
  tostring_binary(8, &binstr);
  printf("%s\n", binstr);
  free(binstr);

  tostring_binary(0xaaaa, &binstr);
  printf("%s\n", binstr);
  free(binstr);

  return 0;
}
