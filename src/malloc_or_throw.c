#include <stdlib.h>
#include "malloc_or_throw.h"
#include "throw.h"

void *malloc_or_throw(const char *description, const size_t size)
{
  void *const output = malloc(size);

  if (output == NULL)
  {
    throw("Failed to allocate %u byte%s for %s.", size, size == 1 ? "" : "1", description);
  }

  return output;
}
