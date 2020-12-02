#include <stdio.h>
#include <unistd.h>


#define BUFFER_SIZE 1024


int main(int argc, char* argv[])
{
    char buffer[BUFFER_SIZE];

    while (read(STDIN_FILENO, buffer, BUFFER_SIZE) != 0)
    {
    }
}


// vim: set expandtab shiftwidth=4 tabstop=4 :
