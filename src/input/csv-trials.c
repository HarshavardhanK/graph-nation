#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char** argv) {

    if(argc < 2) {
        printf("Enter arguments..\n");
        return -1;
    }

    FILE* file = fopen(argv[1], "r");

    //weights only between 0 and 9

    while(1) {

        char next = fgetc(file);

        if(next == EOF)
            break;

        if(next != ',' && next != '\n')
            printf("%c ", next);

        if(next == '\n') {
            printf("\n");
        }

    }

    return 0;
}