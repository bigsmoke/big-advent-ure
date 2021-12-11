#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef enum
{
    AOC_DAY_PART_1 = 1,
    AOC_DAY_PART_2 = 2
} aoc_day_part_t;
#define AOC_DAY_PART_DEFAULT AOC_DAY_PART_1


int main(int argc, char* argv[]) {
    int day_part = AOC_DAY_PART_1;
    if (argc > 1) {
        if (strcmp(argv[1], "1") != 0 && strcmp(argv[1], "2") != 0)
        {
            fprintf(stderr, "Invalid argument: '%s'\n", argv[1]);
            fprintf(stderr, "Usage: solve <part>\n\n    <part>   Part 1 or 2 of the day's puzzle [default: 1]\n");
            exit(EXIT_FAILURE);
        }
        day_part = atoi(argv[1]);
    }

    unsigned int measurement_counter = 0;
    unsigned int previous_measurement;
    unsigned int current_measurement;
    unsigned int num_increases = 0;

    size_t bytes_read;
    size_t chars_read;
    char* line_buffer;
    do {
        bytes_read = 0;
        line_buffer = NULL;
        chars_read = getline(&line_buffer, &bytes_read, stdin);

        if (measurement_counter > 0) {
            previous_measurement = current_measurement;
            if (previous_measurement < current_measurement) {
                num_increases++;
            }
        }
        measurement_counter++;
        current_measurement = atoi(line_buffer);

    } while (chars_read != -1);

    printf("%d", num_increases);
}

// vim: set expandtab shiftwidth=4 tabstop=4:
