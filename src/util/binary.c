#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "binary.h"

void u32_to_binary_str(uint32_t a, char **bin)
{
	const size_t n = sizeof(a) * 8;
	*bin = malloc(sizeof(char) * (n + 1));
	uint32_t mask = 1 << (n - 1);
	for (int i = 0; i < n; i++) {
		(*bin)[i] = (a & mask) ? '1' : '0';
		mask = mask >> 1;
	}

	(*bin)[n] = '\0';
}

void u32_print_bits(uint32_t a)
{
	char *bin = NULL;
	u32_to_binary_str(a, &bin);
	printf("%s\n", bin);
	free(bin);
}
