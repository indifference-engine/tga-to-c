#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "reopen_as_read_only_binary_or_throw.h"
#include "reopen_as_write_only_binary_or_throw.h"
#include "read_u8_or_throw.h"
#include "read_u8s_or_throw.h"
#include "read_u16_or_throw.h"
#include "read_s8_or_throw.h"
#include "write_or_throw.h"
#include "throw.h"
#include "malloc_or_throw.h"

int main(int argc, char **argv)
{
  (void)(argc);
  (void)(argv);

  if (argc < 3)
  {
    throw("At least 2 arguments are required (macro name and variable name).");
  }

  reopen_as_read_only_binary_or_throw("the input TGA file", stdin);
  reopen_as_write_only_binary_or_throw("the output C file", stdout);

  const uint8_t id_length = read_u8_or_throw("the ID length field", stdin);

  if (id_length != 0)
  {
    throw("ID length %d is unsupported (only 0).", id_length);
  }

  const uint8_t color_map_type = read_u8_or_throw("the color map type", stdin);

  if (color_map_type != 1)
  {
    throw("Color map type %d is unsupported (only 1).", color_map_type);
  }

  const uint8_t image_type = read_u8_or_throw("the image type", stdin);

  if (image_type != 9)
  {
    throw("Image type %d is unsupported (only 9).", image_type);
  }

  const uint16_t color_map_specification_first_entry_index = read_u16_or_throw("the first entry index from the color map specification", stdin);

  if (color_map_specification_first_entry_index)
  {
    throw("Color map specification first entry index %d is unsupported (only 0).", color_map_specification_first_entry_index);
  }

  const uint16_t color_map_specification_color_map_length = read_u16_or_throw("the color map length from the color map specification", stdin);

  if (color_map_specification_color_map_length < 1)
  {
    throw("Color map specification length %d is unsupported (must be at least 1).", color_map_specification_color_map_length);
  }

  const uint8_t color_map_specification_color_map_entry_size = read_u8_or_throw("the color map entry size from the color map specification", stdin);

  if (color_map_specification_color_map_entry_size != 32)
  {
    throw("Color map specification entry size %d is unsupported (only 32).", color_map_specification_color_map_entry_size);
  }

  const uint16_t image_specification_x_origin = read_u16_or_throw("the x origin from the image specification", stdin);

  if (image_specification_x_origin != 0)
  {
    throw("Image specification x origin %d is unsupported (only 0).", image_specification_x_origin);
  }

  const uint16_t image_specification_y_origin = read_u16_or_throw("the y origin from the image specification", stdin);

  if (image_specification_y_origin != 0)
  {
    throw("Image specification y origin %d is unsupported (only 0).", image_specification_y_origin);
  }

  const uint16_t image_specification_width = read_u16_or_throw("the width from the image specification", stdin);

  if (image_specification_width == 0)
  {
    throw("Image specification width %d is unsupported.", image_specification_width);
  }

  const uint16_t image_specification_height = read_u16_or_throw("the height from the image specification", stdin);

  if (image_specification_height == 0)
  {
    throw("Image specification height %d is unsupported.", image_specification_height);
  }

  const uint8_t image_specification_bits_per_pixel = read_u8_or_throw("the bits per pixel from the image specification", stdin);

  if (image_specification_bits_per_pixel != 8)
  {
    throw("Image specification bits per pixel %d is unsupported (only 8).", image_specification_bits_per_pixel);
  }

  const uint8_t image_specification_image_descriptor = read_u8_or_throw("the image descriptor from the image specification", stdin);

  if (image_specification_image_descriptor != 32)
  {
    throw("Image specification image descriptor %d is unsupported (only 32).", image_specification_image_descriptor);
  }

  const int color_map_size = (color_map_specification_color_map_length * color_map_specification_color_map_entry_size) / (sizeof(uint8_t) * 8);

  uint8_t *const color_map_data = read_u8s_or_throw("the color map", stdin, color_map_size);

  for (int index = 3; index < argc; index++)
  {
    write_or_throw("an include", stdout, "#include \"%s\"\n", argv[index]);
  }

  write_or_throw("the header", stdout, "%s%s\n(\n  %s,\n  %d,\n  {", argc > 3 ? "\n" : "", argv[1], argv[2], image_specification_width);

  uint8_t *const greens = malloc_or_throw("the green channel", sizeof(uint8_t) * image_specification_width * image_specification_height);
  uint8_t *const blues = malloc_or_throw("the blue channel", sizeof(uint8_t) * image_specification_width * image_specification_height);
  uint8_t *const opacities = malloc_or_throw("the red channel", sizeof(uint8_t) * image_specification_width * image_specification_height);

  int output_pixels = 0;

  while (output_pixels < image_specification_width * image_specification_height)
  {
    int8_t instruction = read_s8_or_throw("next RLE instruction", stdin);

    if (instruction >= 0)
    {
      instruction++;

      if (output_pixels + instruction > image_specification_width * image_specification_height)
      {
        throw("Excess pixels in compressed data.");
      }
      else
      {
        while (instruction > 0)
        {
          int offset = (read_u8_or_throw("a color map index", stdin) * color_map_specification_color_map_entry_size) / (sizeof(uint8_t) * 8);

          if (offset >= color_map_size)
          {
            throw("Out-of-range color map index in compressed data.");
          }

          greens[output_pixels] = color_map_data[offset + 1];
          blues[output_pixels] = color_map_data[offset];
          opacities[output_pixels] = color_map_data[offset + 3];

          write_or_throw("a red", stdout, "%s%s%d", output_pixels == 0 ? "" : ", ", output_pixels % image_specification_width == 0 ? "\n    " : "", color_map_data[offset + 2]);
          output_pixels++;
          instruction--;
        }
      }
    }
    else
    {
      instruction += 129;

      int offset = (read_u8_or_throw("the color map index to repeat", stdin) * color_map_specification_color_map_entry_size) / (sizeof(uint8_t) * 8);

      if (offset >= color_map_size)
      {
        throw("Out-of-range color map index in compressed data.");
      }

      while (instruction > 0)
      {
        if (output_pixels < image_specification_width * image_specification_height)
        {
          greens[output_pixels] = color_map_data[offset + 1];
          blues[output_pixels] = color_map_data[offset];
          opacities[output_pixels] = color_map_data[offset + 3];

          write_or_throw("a red", stdout, "%s%s%d", output_pixels == 0 ? "" : ", ", output_pixels % image_specification_width == 0 ? "\n    " : "", color_map_data[offset + 2]);
          output_pixels++;
          instruction--;
        }
        else
        {
          throw("Excess pixels in compressed data.");
        }
      }
    }
  }

  free(color_map_data);

  write_or_throw("the separator between the red and green planes", stdout, "\n  },\n  {");

  for (int pixel = 0; pixel < image_specification_width * image_specification_height; pixel++)
  {
    write_or_throw("a green", stdout, "%s%s%d", pixel == 0 ? "" : ", ", pixel % image_specification_width == 0 ? "\n    " : "", greens[pixel]);
  }
  free(greens);

  write_or_throw("the separator between the green and blue planes", stdout, "\n  },\n  {");

  for (int pixel = 0; pixel < image_specification_width * image_specification_height; pixel++)
  {
    write_or_throw("a blue", stdout, "%s%s%d", pixel == 0 ? "" : ", ", pixel % image_specification_width == 0 ? "\n     " : "", blues[pixel]);
  }
  free(blues);

  write_or_throw("the separator between the blue and opacity planes", stdout, "\n  },\n  {");

  for (int pixel = 0; pixel < image_specification_width * image_specification_height; pixel++)
  {
    write_or_throw("an opacity", stdout, "%s%s%d", pixel == 0 ? "" : ", ", pixel % image_specification_width == 0 ? "\n    " : "", opacities[pixel]);
  }
  free(opacities);

  write_or_throw("the footer", stdout, "\n  }\n);\n");

  return 0;
}
