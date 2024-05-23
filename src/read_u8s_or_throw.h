/**
 * Reads a number of unsigned bytes from a file, halting execution with an error
 * message should the operation fail.
 * @param description A description of what is being read
 *                    (e.g. "a sub-heading").
 * @param file The file from which to read unsigned bytes.
 * @param quantity The number of unsigned bytes to read from the file.
 * @return A pointer to newly allocated memory containing the read unsigned
 *         bytes.
 */
uint8_t *read_u8s_or_throw(
    const char *const description,
    FILE *const file,
    const size_t quantity);
