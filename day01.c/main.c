#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


#define BUFFER_SIZE 1024


typedef struct {
    int *array;
    size_t used;
    size_t size;
} Expenses;

void expenses_list_init(Expenses *expenses, size_t initial_size)
{
    expenses->array = malloc(initial_size * sizeof(int));
    expenses->used = 0;
    expenses->size = initial_size;
}

void expenses_list_append(Expenses *expenses, int expense)
{
    if (expenses->used == expenses->size)
    {
        expenses->size += 1;
        expenses->array = realloc(expenses->array, expenses->size * sizeof(int));
    }
    expenses->array[expenses->used++] = expense;
}


int main(int argc, char *argv[])
{
    Expenses expenses;


    char buffer[BUFFER_SIZE];

    while (read(STDIN_FILENO, buffer, BUFFER_SIZE) != 0)
    {

    }
}


// vim: set expandtab shiftwidth=4 tabstop=4 :
