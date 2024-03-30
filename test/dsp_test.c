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
#include <check.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "fft.h"

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

	dft(x, X, num_samples);

	for (int i = 0; i < NUM_SAMPLES; i++) {
		ck_assert(compare_complex_double(dft_results[i], X[i], 0.01));
	}
}

START_TEST(test_fft)
{
	const int num_samples = NUM_SAMPLES;
	double complex x[num_samples];
	double complex *X = NULL;

	fill_complex_testdata(x, num_samples);

	int ret = fft(x, &X, num_samples);
	ck_assert_int_eq(ret, 0);

	for (int i = 0; i < num_samples; i++) {
		ck_assert(compare_complex_double(dft_results[i], X[i], 0.01));
	}

	free(X);
}

START_TEST(test_fft_iter)
{
	const int num_samples = NUM_SAMPLES;
	double complex x[num_samples];
	double complex X[num_samples];

	fill_complex_testdata(x, num_samples);

	int ret = iterative_fft(x, X, num_samples);
	ck_assert_int_eq(ret, 0);

	for (int i = 0; i < num_samples; i++) {
		ck_assert(compare_complex_double(dft_results[i], X[i], 0.01));
	}
}

Suite *dsp_suite(void)
{
	Suite *s;

	TCase *dft;
	TCase *fft;
	TCase *fft_iter;

	s = suite_create("DSP Tests");

	dft = tcase_create("DFT");
	tcase_add_test(dft, test_dft);
	suite_add_tcase(s, dft);

	fft = tcase_create("FFT");
	tcase_add_test(fft, test_fft);
	suite_add_tcase(s, fft);

	fft_iter = tcase_create("Iterative FFT");
	tcase_add_test(fft_iter, test_fft_iter);
	suite_add_tcase(s, fft_iter);

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
