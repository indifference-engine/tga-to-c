#include <stdint.h>
#include <stdio.h>
#include <stdint.h>
#include "read_u8_or_throw.h"
#include "malloc_or_throw.h"

uint8_t *read_u8s_or_throw(
    const char *const description,
    FILE *const file,
    const size_t quantity)
{
  uint8_t *const output = malloc_or_throw(description, sizeof(uint8_t) * quantity);

  for (size_t read = 0; read < quantity; read++)
  {
    output[read] = read_u8_or_throw(description, file);
  }

  return output;
}
