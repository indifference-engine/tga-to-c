/**
 * Allocates memory, halting execution with an error message should the
 * allocation fail.
 * @param description A description of the allocation (e.g. "a list of colors").
 * @param size The number of bytes to allocate.
 * @return A pointer to the allocated memory.
 */
void *malloc_or_throw(
    const char *description,
    const size_t size);
