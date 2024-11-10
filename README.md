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

  // Red plane, not linearized, row-major, starting in top left.  Opacity is not
  // pre-multiplied.
  { 255, 18, 137, 209, 64, 32 },

  // Green plane, not linearized, row-major, starting in top left.  Opacity is
  // not pre-multiplied.
  { 255, 18, 137, 209, 64, 32 },

  // Blue plane, not linearized, row-major, starting in top left.  Opacity is
  // not pre-multiplied.
  { 255, 18, 137, 209, 64, 32 },

  // Opacity plane, not linearized, row-major, starting in top left.
  { 255, 18, 137, 209, 64, 32 },
);
```

## Limitations

Currently, only RLE-encoded images with indexed colors are supported.

While there is basic test coverage for this utility, error cases currently lack
test coverage.  Details on these missing test cases can be found in the
[issue tracker](https://github.com/indifference-engine/tga-to-c/issues).

## Building

Execute `make` to build the executable, which will be placed at
[dist/tga_to_c](./dist/tga_to_c).

### Dependencies

- Make.
- MinGW-GCC for Windows, Clang for all other platforms.
- Bash.

## Tests

Execute `make test` to run the test suite.
