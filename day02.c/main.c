#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    int day_part = 1;
    if (argc > 1) {
        if (strcmp(argv[1], "2") != 0)
        {
            fprintf(stderr, "Invalid argument: '%s'\n", argv[1]);
            exit(EXIT_FAILURE);
        }
        day_part = atoi(argv[1]);
    }

    int num_valid_passwords = 0;
    int num_invalid_passwords = 0;

    char *password;
    char *line = NULL;
    size_t size;

    if (day_part == 1)
    {
        unsigned int min_count, max_count;
        char char_to_count;
        unsigned int char_counter;
        while (getline(&line, &size, stdin) != -1)
        {
            min_count = atoi(strsep(&line, "-"));
            max_count = atoi(strsep(&line, " "));
            char_to_count = (char)(strsep(&line, ":")[0]);
            line++;  // Skip space;
            password = strsep(&line, "\n");
            //fprintf(stdout, "%d-%d %c: %s\n", min_count, max_count, char_to_count, password);

            char_counter = 0;
            for (char* passwd_ptr = &password[0]; *passwd_ptr != '\0'; passwd_ptr++)
            {
                if (*passwd_ptr == char_to_count)
                {
                    char_counter++;
                }
            }
            if (min_count <= char_counter && char_counter <= max_count)
            {
                num_valid_passwords++;
            }
            else
            {
                num_invalid_passwords++;
            }
        }
    }
    else if (day_part == 2)
    {
        unsigned int pos1, pos2;
        char char_to_count;
        unsigned int char_counter;
        while (getline(&line, &size, stdin) != -1)
        {
            pos1 = atoi(strsep(&line, "-"));
            pos2 = atoi(strsep(&line, " "));
            char_to_count = (char)(strsep(&line, ":")[0]);
            line++;  // Skip space;
            password = strsep(&line, "\n");
            char_counter = 0;
            if (password[pos1 - 1] == char_to_count)
                char_counter++;
            if (password[pos2 - 1] == char_to_count)
                char_counter++;

            if (char_counter == 1)
            {
                num_valid_passwords++;
            }
            else
            {
                num_invalid_passwords++;
            }
        }
    }
    printf("Valid passwords according to the Official Toboggan Corporate Authentication System: %d\n", num_valid_passwords);
    return 0;
}


// vim: set expandtab shiftwidth=4 tabstop=4:
