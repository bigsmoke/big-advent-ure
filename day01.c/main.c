#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define BUFFER_SIZE 1024
#define EXPENSE_DIGITS 16
#define SOUGHT_SUM 2020


typedef long expense_value_t;
typedef size_t line_number_t;

typedef struct expense {
    struct expense *next_greater_expense;
    expense_value_t value;
    line_number_t line_number;
} expense_t;

typedef struct {
    expense_t *smallest_expense;
    expense_t *greatest_expense;
    size_t num_expenses;
} ordered_expenses_t;

void expenses_list_init(ordered_expenses_t *expenses, size_t initial_size)
{
    expenses->num_expenses = 0;
    expenses->smallest_expense = NULL;
    expenses->greatest_expense = NULL;
}

void expenses_list_add(ordered_expenses_t *expenses, expense_value_t new_value, line_number_t line_number)
{
    expense_t *current_expense = expenses->smallest_expense;  // Will be NULL if the list is empty.
    expense_t *previous_expense = NULL;
    expense_t *new_expense = (expense_t*)malloc(sizeof(expense_t));
    new_expense->value = new_value;
    new_expense->line_number = line_number;

    // Get the `current_expense` pointer to point to the first expense in the list with a value greater than
    // or equal to the value that we're adding:
    while (current_expense != NULL)
    {
        if (current_expense->value >= new_value) {
            break;
        }
        previous_expense = current_expense;
        current_expense = current_expense->next_greater_expense;
    }

    if (previous_expense != NULL)
    {
        // If there is a smaller expense than our newly added expense,
        // we insert ourselves in the list _after_ that expense.
        previous_expense->next_greater_expense = new_expense;
    }
    else
    {
        // If there's no smaller expense, we put ourselves at the start of the list.
        expenses->smallest_expense = new_expense;
    }

    new_expense->next_greater_expense = current_expense;

    if (current_expense == NULL)
    {
        // We found no existing expense greater in or equal to the new expense.
        expenses->greatest_expense = new_expense;
    }

    expenses->num_expenses++;
}

void expenses_list_seek_sum_parts(ordered_expenses_t *expenses, int sum_to_seek, int num_parts, expense_t **expense_iterators, int depth, expense_value_t *found_sum)
{
    expense_value_t sum;
    do
    {
        if (depth == num_parts - 1)
        {
            sum = 0;
            for (int part_i = 0; part_i < num_parts; part_i++)
            {
                sum += expense_iterators[part_i]->value;
            }
            if (sum == sum_to_seek)
            {
                *found_sum = sum;
                return;
            }
        }
        else
        {
            expense_iterators[depth + 1] = expenses->smallest_expense;
            expenses_list_seek_sum_parts(expenses, sum_to_seek, num_parts, expense_iterators, depth + 1, found_sum);
            if (*found_sum > 0) {
                return;
            }
        }
    }
    while ((expense_iterators[depth] = expense_iterators[depth]->next_greater_expense) != NULL);
}


char stdin_buffer_of_max_digit_size[EXPENSE_DIGITS];

int main(int argc, char *argv[])
{
    char *line_buffer;
    char *line_end_ptr;
    size_t line_size;
    ordered_expenses_t expenses;
    expense_value_t value;
    line_number_t line_number = 0;
    int sum_parts = 2;
    int day_part = 1;

    if (argc == 2) {
        day_part = atoi(argv[1]);
        if (day_part != 1 && day_part != 2) {
            fprintf(stderr, "Invalid argument: '%s'\n", argv[1]);
            fprintf(stderr, "Usage: solve <part>\n\n    <part>   Part 1 or 2 of the day's puzzle [default: 1]\n");
            exit(EXIT_FAILURE);
        }
    }

    if (day_part == 2)
        sum_parts = 3;

    expenses_list_init(&expenses, 10);

    line_buffer = malloc(EXPENSE_DIGITS);

    while (getline(&line_buffer, &line_size, stdin) != -1)
    {
        line_number++;
        errno = 0;
        value = strtol(line_buffer, &line_end_ptr, 10);
        if ((errno == ERANGE && (value == LONG_MAX || value == LONG_MIN))
                || (errno != 0 && value == 0))
        {
            perror("strtol()");
            exit(EXIT_FAILURE);
        }
        if (line_end_ptr == line_buffer)
        {
            fprintf(stderr, "No digits were found\n");
            exit(EXIT_FAILURE);
        }

        expenses_list_add(&expenses, value, line_number);
        memset(line_buffer, 0, EXPENSE_DIGITS);  // Clear buffer.
    }

    expense_t *expense_iterators[sum_parts];
    for (int part_i = 0; part_i < sum_parts; part_i++)
    {
        expense_iterators[part_i] = expenses.smallest_expense;
    }
    expense_value_t found_sum;
    expenses_list_seek_sum_parts(&expenses, SOUGHT_SUM, sum_parts, expense_iterators, 0, &found_sum);

    if (found_sum > 0) {
        expense_value_t product = 1;
        expense_value_t sum = 0;
        for (int part_i = 0; part_i < sum_parts; part_i++)
        {
            //fprintf(stdout, "%ld on line %ld\n", expense_iterators[part_i]->value, expense_iterators[part_i]->line_number);
            product *= expense_iterators[part_i]->value;
        }
        fprintf(stdout, "%ld\n", product);
        //fprintf(stdout, "%ld = sum\n", found_sum);
        exit(EXIT_SUCCESS);
    }
    else
    {
        fprintf(stderr, "No %d expenses found that sum to %d\n", sum_parts, SOUGHT_SUM);
        exit(EXIT_FAILURE);
    }
}


// vim: set expandtab shiftwidth=4 tabstop=4 :
