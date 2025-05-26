#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "read_s8_or_throw.h"
#include "read_u8_or_throw.h"
#include "malloc_or_throw.h"
#include "throw.h"

uint8_t *read_rle_encoded_u8s_or_throw(
    const char *const description,
    FILE *const file,
    const size_t quantity)
{
  uint8_t *const output = malloc_or_throw(description, quantity);

  for (size_t index = 0; index < quantity;)
  {
    int instruction = read_s8_or_throw("next RLE instruction", file);

    if (instruction >= 0)
    {
      instruction++;

      if (index + instruction > quantity)
      {
        throw("Excess bytes in compressed data.");
      }
      else
      {
        while (instruction > 0)
        {
          const uint8_t value = read_u8_or_throw("a byte", file);
          output[index] = value;

          index++;
          instruction--;
        }
      }
    }
    else
    {
      instruction += 129;

      const uint8_t value = read_u8_or_throw("a byte to repeat", file);

      while (instruction > 0)
      {
        if (index < quantity)
        {
          output[index] = value;

          index++;
          instruction--;
        }
        else
        {
          throw("Excess bytes in compressed data.");
        }
      }
    }
  }

  return output;
}
