#include <check.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "fft.h"
#include "dsp_util.h"

#define NUM_SAMPLES 8

static void fill_complex_testdata(double complex *x, size_t num_samples)
{
	for (int i = 0; i < num_samples; i++) {
		x[i] = 1.0 * i + 1.0 * i * I;
	}
}

static bool compare_complex_double(double complex a, double complex b,
				   double margin)
{
	bool equal = false;
	double remainder_real = fabs(creal(a) - creal(b));
	double remainder_imag = fabs(cimag(a) - cimag(b));

	if ((remainder_real <= margin) && (remainder_imag <= margin)) {
		equal = true;
	}

	return equal;
}

/*
 * Calculated using Python (numpy.fft).
 * See fft_results.py.
 */
static const double complex dft_results[] = {
	28 + 28I, -13.65685424949238 + 5.656854249492381I,
	-8 + 0I,  -5.656854249492381 - 2.3431457505076194I,
	-4 - 4I,  -2.3431457505076194 - 5.656854249492381I,
	0 - 8I,	  5.656854249492381 - 13.65685424949238I,
};

START_TEST(test_dft)
{
	const int num_samples = NUM_SAMPLES;
	double complex x[num_samples];
	double complex X[num_samples];

	fill_complex_testdata(x, num_samples);

	print_complex_arr(x, num_samples);
	printf("-----\n");

	dft(x, X, num_samples);

	print_complex_arr(X, num_samples);

	for (int i = 0; i < NUM_SAMPLES; i++) {
		ck_assert(compare_complex_double(dft_results[i], X[i], 0.01));
	}
}

Suite *dsp_suite(void)
{
	Suite *s;
	TCase *dft;

	s = suite_create("DSP Tests");

	dft = tcase_create("DFT");
	tcase_add_test(dft, test_dft);

	suite_add_tcase(s, dft);
	return s;
}

int main(void)
{
	int number_failed = 0;
	Suite *s = NULL;
	SRunner *sr;

	s = dsp_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
