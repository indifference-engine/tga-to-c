#include <stdint.h>
#include <stdio.h>
#include "read_u8_or_throw.h"

uint16_t read_u16_or_throw(
    const char *const description,
    FILE *const file)
{
  uint8_t first_byte = read_u8_or_throw(description, file);
  uint8_t second_byte = read_u8_or_throw(description, file);

  return first_byte | (second_byte << 8);
}
