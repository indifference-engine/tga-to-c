/**
 * Reads an unsigned short from a file, halting execution with an error message
 * should the operation fail.
 * @param description A description of what is being read
 *                    (e.g. "a sub-heading").
 * @param file The file from which to read an unsigned short.
 * @return The unsigned short read from the file.
 */
uint16_t read_u16_or_throw(
    const char *const description,
    FILE *const file);
