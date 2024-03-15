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
