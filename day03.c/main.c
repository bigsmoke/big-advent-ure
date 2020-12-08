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
    int n;
    int x = 1, y = 1;
    int pattern_i = 0;
    int direction_x = 3, direction_y = 1;
    int trees_encountered = 0;

    while ((n = read(STDIN_FILENO, &grid_line_pattern, GRID_LINE_INPUT_LENGTH)) != 0)
    {
        if (n == -1)
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
        // write(STDOUT_FILENO, grid_line_pattern, n);
        fprintf(stdout, "%d (%d), %d\n", x, pattern_i, y);

        if (grid_line_pattern[pattern_i] == TREE_CHAR)
        {
            trees_encountered++;
        }

        x += direction_x;
        pattern_i += direction_x;
        if (pattern_i >= GRID_LINE_PATTERN_LENGTH)
            pattern_i = pattern_i - GRID_LINE_PATTERN_LENGTH;
        y += direction_y;
    }

    fprintf(stdout, "%d\n", trees_encountered);
    return 0;
}


// vim: set expandtab shiftwidth=4 tabstop=4:
