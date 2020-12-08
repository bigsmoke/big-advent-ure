#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


#define GRID_LINE_PATTERN_LENGTH 31
#define GRID_LINE_INPUT_LENGTH 32
#define TREE_CHAR '#'
#define OPEN_CHAR '.'


int main(int argc, char *argv[])
{
    char grid_line_pattern[GRID_LINE_INPUT_LENGTH];
    int bytes_read;
    // fcntl(stdin);
    while ((bytes_read = read(STDIN_FILENO, &grid_line_pattern, GRID_LINE_INPUT_LENGTH)) != 0)
    {
        if (bytes_read == -1)
        {
            if (errno == EINTR)
            {
                continue;
            }
            if (errno == EWOULDBLOCK || errno == EAGAIN)
            {
            }
            fputs(strerror(errno), stderr);
            break;
        }

        write(STDOUT_FILENO, grid_line_pattern, bytes_read);

    }

    return 0;
}

pthread_create(&thread, functie, arg);


// vim: set expandtab shiftwidth=4 tabstop=4:
