#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "read_s8_or_throw.h"
#include "read_u8_or_throw.h"
#include "malloc_or_throw.h"
#include "throw.h"

uint8_t **read_rle_encoded_u8s_or_throw(
    const char *const description,
    FILE *const file,
    const size_t quantity_of_planes,
    const size_t quantity_per_plane)
{
  uint8_t *const temp = malloc_or_throw(description, quantity_of_planes * sizeof(uint8_t));
  uint8_t **const output = malloc_or_throw(description, quantity_of_planes * sizeof(uint8_t *));

  for (size_t plane_index = 0; plane_index < quantity_of_planes; plane_index++)
  {
    output[plane_index] = malloc_or_throw(description, quantity_per_plane * sizeof(uint8_t));
  }

  for (size_t byte_index = 0; byte_index < quantity_per_plane;)
  {
    int instruction = read_s8_or_throw("next RLE instruction", file);

    if (instruction >= 0)
    {
      instruction++;

      if (byte_index + instruction > quantity_per_plane)
      {
        throw("Excess bytes in compressed data.");
      }
      else
      {
        while (instruction > 0)
        {
          for (size_t plane_index = 0; plane_index < quantity_of_planes; plane_index++)
          {
            const uint8_t value = read_u8_or_throw("a byte", file);
            output[plane_index][byte_index] = value;
          }

          byte_index++;
          instruction--;
        }
      }
    }
    else
    {
      instruction += 129;

      for (size_t plane_index = 0; plane_index < quantity_of_planes; plane_index++)
      {
        temp[plane_index] = read_u8_or_throw("a byte to repeat", file);
      }

      while (instruction > 0)
      {
        if (byte_index < quantity_per_plane)
        {
          for (size_t plane_index = 0; plane_index < quantity_of_planes; plane_index++)
          {
            output[plane_index][byte_index] = temp[plane_index];
          }

          byte_index++;
          instruction--;
        }
        else
        {
          throw("Excess bytes in compressed data.");
        }
      }
    }
  }

  free(temp);

  return output;
}
