# TGA to C

Command-line utility to convert TGA files to C files.

## Usage

`tga_to_c TEXTURE_MACRO_NAME variable_name REDS_MACRO_NAME RED_MACRO_NAME GREENS_MACRO_NAME GREEN_MACRO_NAME BLUES_MACRO_NAME BLUE_MACRO_NAME OPACITIES_MACRO_NAME OPACITY_MACRO_NAME path/to/first/include.h path/to/second/include.h < path/to/input.tga > path/to/output.c`

This will output a file similar to the following:

```c
#include "path/to/first/include.h"
#include "path/to/second/include.h"

TEXTURE_MACRO_NAME
(
  variable_name,

  // Width of image in pixel columns.
  3,

  // Red plane, not linearized, row-major, starting in top left.  Opacity is not
  // pre-multiplied.
  REDS_MACRO_NAME(
    RED_MACRO_NAME(255),
    RED_MACRO_NAME(18),
    RED_MACRO_NAME(137),
    RED_MACRO_NAME(209),
    RED_MACRO_NAME(64),
    RED_MACRO_NAME(32)
  ),

  // Green plane, not linearized, row-major, starting in top left.  Opacity is
  // not pre-multiplied.
  GREENS_MACRO_NAME(
    GREEN_MACRO_NAME(255),
    GREEN_MACRO_NAME(18),
    GREEN_MACRO_NAME(137),
    GREEN_MACRO_NAME(209),
    GREEN_MACRO_NAME(64),
    GREEN_MACRO_NAME(32)
  ),

  // Blue plane, not linearized, row-major, starting in top left.  Opacity is
  // not pre-multiplied.
  BLUES_MACRO_NAME(
    BLUE_MACRO_NAME(255),
    BLUE_MACRO_NAME(18),
    BLUE_MACRO_NAME(137),
    BLUE_MACRO_NAME(209),
    BLUE_MACRO_NAME(64),
    BLUE_MACRO_NAME(32)
  ),

  // Opacity plane, not linearized, row-major, starting in top left.
  OPACITIES_MACRO_NAME(
    OPACITY_MACRO_NAME(255),
    OPACITY_MACRO_NAME(18),
    OPACITY_MACRO_NAME(137),
    OPACITY_MACRO_NAME(209),
    OPACITY_MACRO_NAME(64),
    OPACITY_MACRO_NAME(32)
  )
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
