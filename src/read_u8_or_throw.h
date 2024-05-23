/**
 * Reads an unsigned byte from a file, halting execution with an error message
 * should the operation fail.
 * @param description A description of what is being read
 *                    (e.g. "a sub-heading").
 * @param file The file from which to read an unsigned byte.
 * @return The unsigned byte read from the file.
 */
uint8_t read_u8_or_throw(
    const char *const description,
    FILE *const file);
