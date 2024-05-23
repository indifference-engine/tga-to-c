#include <stdio.h>
#ifdef __MINGW32__
#include <fcntl.h>
#endif
#include "reopen_as_write_only_binary_or_throw.h"
#include "throw.h"

void reopen_as_write_only_binary_or_throw(
    const char *description,
    FILE *const file)
{
#ifdef __MINGW32__
  if (_setmode(_fileno(file), O_BINARY) == -1)
#else
  if (freopen(NULL, "wb", file) == NULL)
#endif
  {
#ifdef errno
    throw("Failed to re-open %s as write-only binary (errno %d).", description, errno);
#else
    throw("Failed to re-open %s as write-only binary.", description);
#endif
  }
}
