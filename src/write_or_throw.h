/**
 * Writes a string to a file, halting execution with an error message should the
 * operation fail.
 * @param description A description of what is being written
 *                    (e.g. "a sub-heading").
 * @param file The file to which to write.
 * @param fmt The format of the string.
 * @param ... Variables to be substituted into the string.
 */
void write_or_throw(
    const char *const description,
    FILE *const file,
    const char *const fmt,
    ...);
