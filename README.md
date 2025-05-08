# Get Next Line (GNL) Project

## Overview
Get Next Line is a function that reads a line from a file descriptor. It's designed to efficiently read text files line by line. The project is implemented in C and follows the 42 coding standards.

## Features
- Read lines from any valid file descriptor
- Handle multiple file descriptors simultaneously (bonus)
- Memory efficient implementation
- Support for variable buffer sizes through the BUFFER_SIZE macro

## Implementation Details
The project consists of two versions:

### Mandatory Version
The mandatory implementation requires managing the saved buffer manually:
- `char *get_next_line(int fd, char **saved)`: Returns the next line from the file descriptor `fd` while managing a state through the `saved` parameter.
- Caller is responsible for initializing and freeing the `saved` buffer.

### Bonus Version
The bonus implementation can handle multiple file descriptors simultaneously:
- `char *get_next_line(int fd)`: Returns the next line from file descriptor `fd` without requiring external state management.
- Uses a static array to keep track of leftover data from each file descriptor.
- Supports up to OPEN_MAX file descriptors simultaneously.

## How to Build

### Mandatory Version
```bash
make
```

### Bonus Version
```bash
make bonus
```

## Usage Example

### Mandatory Version
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int fd;
    char *line;
    char *saved;
    
    if (argc != 2)
        return 1;
    
    saved = ft_strdup("");
    fd = open(argv[1], O_RDONLY);
    
    while ((line = get_next_line(fd, &saved)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    
    free(saved);
    close(fd);
    return 0;
}
```

### Bonus Version
```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int fd1, fd2;
    char *line;
    
    if (argc != 3)
        return 1;
    
    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[2], O_RDONLY);
    
    // Read alternately from both files
    while (1)
    {
        line = get_next_line(fd1);
        if (line)
        {
            printf("File 1: %s", line);
            free(line);
        }
        
        line = get_next_line(fd2);
        if (line)
        {
            printf("File 2: %s", line);
            free(line);
        }
        
        if (!line && !get_next_line(fd1))
            break;
    }
    
    close(fd1);
    close(fd2);
    return 0;
}
```

## Technical Approach
The implementation uses a buffer to read from the file descriptor and maintains leftover data between calls. It handles edge cases like:
- End of file
- Memory allocation failures
- Invalid file descriptors
- Various buffer sizes

## Note
This project is part of the 42 curriculum and demonstrates low-level I/O operations and memory management in C.