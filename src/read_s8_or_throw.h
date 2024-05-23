/**
 * Reads a signed byte from a file, halting execution with an error message
 * should the operation fail.
 * @param description A description of what is being read
 *                    (e.g. "a sub-heading").
 * @param file The file from which to read a signed byte.
 * @return The signed byte read from the file.
 */
int8_t read_s8_or_throw(
    const char *const description,
    FILE *const file);
