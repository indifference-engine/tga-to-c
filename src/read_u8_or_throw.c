#include <stdint.h>
#include <stdio.h>
#include "throw.h"

int8_t read_s8_or_throw(
    const char *const description,
    FILE *const file)
{
  int8_t output;

  if (fread(&output, sizeof(int8_t), 1, file) == 1)
  {
    return output;
  }
  else
  {
    throw("Failed to read %s.", description);
  }
}
