#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define GRID_LINE_PATTERN_LENGTH 31
#define GRID_LINE_INPUT_LENGTH 32
#define TREE_CHAR '#'
#define OPEN_CHAR '.'


typedef enum
{
    PART_1 = 1,
    PART_2 = 2
} day_part_t;

typedef struct slope_run
{
    int x, y;
    int pattern_i;
    int direction_x, direction_y;
    int trees_encountered;
    int skip_next_line;
    day_part_t puzzle_part_filter;
} slope_run_t;


int main(int argc, char *argv[])
{
    slope_run_t runs[] = {
        { .x = 1, .y = 1, .pattern_i = 0, .direction_x = 1, .direction_y = 1, .trees_encountered = 0, .puzzle_part_filter = PART_2 },
        { .x = 1, .y = 1, .pattern_i = 0, .direction_x = 3, .direction_y = 1, .trees_encountered = 0, .puzzle_part_filter = PART_1 | PART_2 },
        { .x = 1, .y = 1, .pattern_i = 0, .direction_x = 5, .direction_y = 1, .trees_encountered = 0, .puzzle_part_filter = PART_2 },
        { .x = 1, .y = 1, .pattern_i = 0, .direction_x = 7, .direction_y = 1, .trees_encountered = 0, .puzzle_part_filter = PART_2 },
        { .x = 1, .y = 1, .pattern_i = 0, .direction_x = 1, .direction_y = 2, .trees_encountered = 0, .puzzle_part_filter = PART_2 },
    };
    int num_runs = sizeof(runs)/sizeof(runs[0]);

    int day_part = 1;
    if (argc > 1) {
        if (strcmp(argv[1], "1") != 0 && strcmp(argv[1], "2") != 0)
        {
            fprintf(stderr, "Invalid argument: '%s'\n", argv[1]);
            fprintf(stderr, "Usage: solve <part>\n\n    <part>   Part 1 or 2 of the day's puzzle [default: 1]\n");
            exit(EXIT_FAILURE);
        }
        day_part = atoi(argv[1]);
    }

    char *grid_line_pattern;
    grid_line_pattern = malloc(sizeof(char) * GRID_LINE_INPUT_LENGTH);  // We know the actual input lines don't exceed this size.
    int n;
    int line_no = 0;
    size_t line_length;
    size_t pattern_length;

    while (getline(&grid_line_pattern, &line_length, stdin) != -1)
    {
        pattern_length = strlen(grid_line_pattern) - 1;  // Exclude newline

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
            if ((runs[i].puzzle_part_filter & day_part) == 0)
                continue;

            if (runs[i].direction_y > 1 && ((line_no - 1) % runs[i].direction_y) != 0)
                continue;  // Skipping line because vertical direction > 1

            if (grid_line_pattern[runs[i].pattern_i] == TREE_CHAR)
                runs[i].trees_encountered++;

            runs[i].x += runs[i].direction_x;
            runs[i].pattern_i += runs[i].direction_x;
            if (runs[i].pattern_i >= pattern_length)
                runs[i].pattern_i = runs[i].pattern_i - pattern_length;
            runs[i].y += runs[i].direction_y;
        }
    }

    int product = 1;
    for (int i = 0; i < num_runs; i++)
    {
        if ((runs[i].puzzle_part_filter & day_part) == 0)
            continue;
        product *= runs[i].trees_encountered;
    }
    fprintf(stdout, "%d\n", product);

    return 0;
}


// vim: set expandtab shiftwidth=4 tabstop=4:
