#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


#define GRID_LINE_PATTERN_LENGTH 31
#define GRID_LINE_INPUT_LENGTH 32
#define TREE_CHAR '#'
#define OPEN_CHAR '.'


typedef struct slope_run
{
    int x, y;
    int pattern_i;
    int direction_x, direction_y;
    int trees_encountered;
    int skip_next_line;
} slope_run_t;


int main(int argc, char *argv[])
{
    slope_run_t runs[] = {
        { .x = 1, .y = 1, .pattern_i = 0, .direction_x = 1, .direction_y = 1, .trees_encountered = 0 },
        { .x = 1, .y = 1, .pattern_i = 0, .direction_x = 3, .direction_y = 1, .trees_encountered = 0 },  // same as part 1
        { .x = 1, .y = 1, .pattern_i = 0, .direction_x = 5, .direction_y = 1, .trees_encountered = 0 },
        { .x = 1, .y = 1, .pattern_i = 0, .direction_x = 7, .direction_y = 1, .trees_encountered = 0 },
        { .x = 1, .y = 1, .pattern_i = 0, .direction_x = 1, .direction_y = 2, .trees_encountered = 0 }
    };
    int num_runs = 5;

    char grid_line_pattern[GRID_LINE_INPUT_LENGTH];
    int n;
    int line_no = 0;

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
        line_no++;
        // write(STDOUT_FILENO, grid_line_pattern, n);

        for (int i = 0; i < num_runs; i++)
        {
            if (runs[i].direction_y > 1 && ((line_no - 1) % runs[i].direction_y) != 0)
                continue;  // Skipping line because vertical direction > 1

            if (grid_line_pattern[runs[i].pattern_i] == TREE_CHAR)
                runs[i].trees_encountered++;

            runs[i].x += runs[i].direction_x;
            runs[i].pattern_i += runs[i].direction_x;
            if (runs[i].pattern_i >= GRID_LINE_PATTERN_LENGTH)
                runs[i].pattern_i = runs[i].pattern_i - GRID_LINE_PATTERN_LENGTH;
            runs[i].y += runs[i].direction_y;
        }
    }

    int product = 1;
    for (int i = 0; i < num_runs; i++)
    {
        fprintf(stdout, "%d\n", runs[i].trees_encountered);
        product *= runs[i].trees_encountered;
    }
    fprintf(stdout, "%d\n", product);

    return 0;
}


// vim: set expandtab shiftwidth=4 tabstop=4:
