#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define BUFFER_SIZE 1024
#define EXPENSE_DIGITS 16
#define SOUGHT_SUM 2020


typedef long ExpenseValue;
typedef size_t LineNumber;

typedef struct Expense {
    struct Expense *next_greater_expense;
    ExpenseValue value;
    LineNumber line_number;
} Expense;

typedef struct {
    Expense *smallest_expense;
    Expense *greatest_expense;
    size_t num_expenses;
} OrderedExpenses;

void expenses_list_init(OrderedExpenses *expenses, size_t initial_size)
{
    expenses->num_expenses = 0;
    expenses->smallest_expense = NULL;
    expenses->greatest_expense = NULL;
}

void expenses_list_add(OrderedExpenses *expenses, ExpenseValue new_value, LineNumber line_number)
{
    Expense *current_expense = expenses->smallest_expense;  // Will be NULL if the list is empty.
    Expense *previous_expense = NULL;
    Expense *new_expense = (Expense*)malloc(sizeof(Expense));
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

char stdin_buffer_of_max_digit_size[EXPENSE_DIGITS];

int main(int argc, char *argv[])
{
    OrderedExpenses expenses;
    ExpenseValue value;
    char *digits;
    char *digits_end_ptr;
    int num_bytes_read;
    LineNumber line_number = 0;

    expenses_list_init(&expenses, 10);

    digits = malloc(EXPENSE_DIGITS);

    setvbuf(stdin, stdin_buffer_of_max_digit_size, _IOLBF, EXPENSE_DIGITS);

    while ((num_bytes_read = read(STDIN_FILENO, digits, EXPENSE_DIGITS)) != 0)
    {
        line_number++;
        errno = 0;
        value = strtol(digits, &digits_end_ptr, 10);
        if ((errno == ERANGE && (value == LONG_MAX || value == LONG_MIN))
                || (errno != 0 && value == 0))
        {
            perror("strtol()");
            exit(EXIT_FAILURE);
        }
        if (digits_end_ptr == digits)
        {
            fprintf(stderr, "No digits were found\n");
            exit(EXIT_FAILURE);
        }

        expenses_list_add(&expenses, value, line_number);
    }

    Expense* expense_i = expenses.smallest_expense;
    Expense* expense_j;
    do
    {
        expense_j = expenses.smallest_expense;
        do
        {
            if ((expense_i->value + expense_j->value) == SOUGHT_SUM)
            {
                fprintf(
                    stdout, "%d = %ld [line %ld] + %ld [line %ld]\n%ld * %ld = %ld\n",
                    SOUGHT_SUM,
                    expense_i->value, expense_i->line_number,
                    expense_j->value, expense_j->line_number,
                    expense_i->value, expense_j->value, expense_i->value * expense_j->value
                );
                exit(EXIT_SUCCESS);
            }
        }
        while ((expense_j = expense_j->next_greater_expense) != NULL);
    }
    while ((expense_i = expense_i->next_greater_expense) != NULL);

    fprintf(stderr, "No 2 expenses found that sum to %i\n", SOUGHT_SUM);
    exit(EXIT_FAILURE);
}


// vim: set expandtab shiftwidth=4 tabstop=4 :
