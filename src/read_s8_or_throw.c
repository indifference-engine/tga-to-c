#include <stdint.h>
#include <stdio.h>
#include "throw.h"

uint8_t read_u8_or_throw(
    const char *const description,
    FILE *const file)
{
  uint8_t output;

  if (fread(&output, sizeof(uint8_t), 1, file) == 1)
  {
    return output;
  }
  else
  {
    throw("Failed to read %s.", description);
  }
}
