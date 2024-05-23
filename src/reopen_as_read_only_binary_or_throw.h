/**
 * Re-opens a file as read-only binary, halting execution with an error message
 * should the operation fail.
 * @param description A description of the file being re-opened as binary
 *                    (e.g. "a list of colors").
 * @param file The file to re-open as binary.
 */
void reopen_as_read_only_binary_or_throw(
    const char *description,
    FILE *const file);
