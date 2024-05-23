# TGA to C

Command-line utility to convert TGA files to C files.

## Usage

`tga_to_c MACRO_NAME variable_name path/to/first/include.h path/to/second/include.h < path/to/input.tga > path/to/output.c`

This will output a file similar to the following:

```c
#include "path/to/first/include.h"
#include "path/to/second/include.h"

MACRO_NAME
(
  variable_name,

  // Width of image in pixel columns.
  3,

  // Red plane as unit intervals, row-major, starting in top left.  Opacity is not pre-multiplied.
  { 0.3f, 0.7f, 0.8f, 0.7f, 0.2f, 0.4f },

  // Green plane as unit intervals, row-major, starting in top left.  Opacity is not pre-multiplied.
  { 0.3f, 0.7f, 0.8f, 0.7f, 0.2f, 0.4f },

  // Blue plane as unit intervals, row-major, starting in top left.  Opacity is not pre-multiplied.
  { 0.3f, 0.7f, 0.8f, 0.7f, 0.2f, 0.4f },

   // Opacity plane as unit intervals, row-major, starting in top left.
  { 0.3f, 0.7f, 0.8f, 0.7f, 0.2f, 0.4f }
);
```

## Building

Execute `make` to build the executable, which will be placed at
[dist/tga_to_c](./dist/tga_to_c).

### Dependencies

- Make.
- MinGW-GCC for Windows, Clang for all other platforms.
- Bash.

## Tests

Execute `make test` to run the test suite.
