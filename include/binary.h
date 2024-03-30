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
#ifndef FVB_BINARY_H
#define FVB_BINARY_H

#include <stdint.h>

/**
 * Convert uint32_t to binary string represenation
 * @param a    the 32 bit integer to be converted
 * @param bin  a double pointer to a string which will contain the binary
               representation of a. Must be freed.
 * @return     Nothing
 */
void u32_to_binary_str(uint32_t a, char **bin);

/**
 * Print the binary representation of a uint32_t to stdout
 * @param a    the 32 bit integer to be printed
 * @return     Nothing
 */
void u32_print_bits(uint32_t a);

#endif /* FVB_BINARY_H */
