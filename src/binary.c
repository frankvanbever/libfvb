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
