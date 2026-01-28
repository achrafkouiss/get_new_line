*This project has been created as part of the 42 curriculum by akouiss.*

# Get Next Line (GNL)

## Description

Get Next Line is a C function designed to read **one line at a time** from a given file descriptor. Each call to `get_next_line()` returns the next line in the file or input stream, including the newline character (`\n`) if it exists.

The purpose of this project is to develop a strong understanding of:

* **Static variables** in C.
* **Dynamic memory allocation** and safe memory management.
* Efficient **buffered file reading** without reading the entire file at once.
* Handling multiple file descriptors and edge cases in file input.

This project is a foundational exercise in building robust C programs and handling variable-sized input safely and efficiently.

---

## Features

* Reads from **any file descriptor** (file, standard input, etc.).
* Returns **lines incrementally**, so memory usage is minimized.
* Handles files of **arbitrary length**, including extremely large files.
* The returned string always contains the newline character, except at the **end of the file** if it doesn’t end with `\n`.
* **Bonus feature:** Supports **multiple file descriptors simultaneously**, allowing you to switch between reading different files without losing the current reading position of each.

---

## Algorithm

The implementation of `get_next_line()` is based on three main operations:

1. **Reading from the file descriptor:**

   * Allocate a temporary buffer of size `BUFFER_SIZE`.
   * Read data from the file into this buffer using `read()`.
   * Append this data to the static buffer for the file descriptor.
   * Stop reading when a newline character is found or the end of the file is reached.

2. **Extracting a line:**

   * Search for the newline character (`\n`) in the static buffer.
   * If found, allocate a new string for the line containing all characters up to and including the newline.
   * If no newline is found, the entire buffer is returned as the last line.

3. **Updating the static buffer:**

   * After extracting the line, remove the returned portion from the buffer, leaving the remaining characters for the next call.
   * This ensures that subsequent calls continue reading where the previous call stopped.

**Memory management:**

* Each returned line is dynamically allocated and must be freed by the caller.
* The static buffer persists between function calls but is freed if an error occurs or when the file descriptor is closed.

---

## Bonus Feature – Multiple File Descriptors

To support multiple file descriptors:

```c
static char *buffer[1024];
```

* Each file descriptor has its **own static buffer**.
* Reading from one file descriptor does not affect another.
* You can alternate calls between multiple descriptors safely:

```c
line1 = get_next_line(fd1);
line2 = get_next_line(fd2);
line3 = get_next_line(fd1);
```

This ensures full compliance with the bonus requirement of handling multiple descriptors.

---

## Instructions

### Compilation

Compile the project using the following command, adjusting `BUFFER_SIZE` as needed:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl_test
```

### Usage

Read a file line by line:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("example.txt", O_RDONLY);
    char *line;

    if (fd < 0)
        return 1;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

### Notes

* The function works for standard input (`fd = 0`) as well.
* Lines can be of **arbitrary length**, and the function dynamically adjusts memory to accommodate them.
* Avoid modifying the file while reading; doing so may cause undefined behavior.

---

## Implementation Details

* **Helper Functions:**

  * `ft_strlen` – calculate string length.
  * `ft_strchr` – locate a character in a string.
  * `ft_strdup` – duplicate a string.
  * `ft_strjoin` – concatenate two strings.
  * `ft_calloc` – allocate and zero-initialize memory.

* **Static Variable Reasoning:**

  * The static buffer keeps leftover data between calls.
  * This is critical for **incremental reading**, allowing the function to handle lines split across multiple `read()` calls.

* **Edge Cases Handled:**

  * Empty files.
  * Files without newline at the end.
  * Large buffer sizes or `BUFFER_SIZE` = 1.
  * File descriptors exceeding 1023 are rejected to prevent out-of-bounds errors.
