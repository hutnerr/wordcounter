/*
 * This is a command line utility to get information from txt files.
 * It will return the number of words, characters, and lines in the file.
 * 
 * @author Hunter Baker
 * @version 1.01
 * @date 2024-17-12 
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "filemetrics.h"

void usage();
void usage()
{
    printf("Usage: ./wordcnt <option> <input_file>\n");
    printf("Supported filetypes: .txt\n");
    printf("Options:\n");
    printf("  -w: count words (default)\n");
    printf("  -c: count characters\n");
    printf("  -l: count lines\n");
    printf("  -a: count all\n");
}

int main(int argc, char **argv)
{
    bool words = true; // since this is our default
    bool chars = false;
    bool lines = false;

    if (argc < 2)
    {
        printf("No file or arguments provided\n");
        usage();
        exit(EXIT_FAILURE);
    }

    // parse the inputs 
    int i;
    while ((i = getopt(argc, argv, "wcla")) != -1)
    {
        switch (i)
        {
        case 'w':
            words = true;
            break;
        case 'c':
            chars = true;
            break;
        case 'l':
            lines = true;
            break;
        case 'a':
            words = true;
            chars = true;
            lines = true;
            break;
        default:
            printf("Invalid option\n");
            usage();
            exit(EXIT_FAILURE);
        }
    }

    if (optind != argc - 1)
    {
        printf("No filename or extraneous input\n");
        usage();
        exit(EXIT_FAILURE);
    }

    char* filename = argv[optind];

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error: cannot open file\n");
        exit(EXIT_FAILURE);
    }

    // TODO: Do the spinny bar thing 
    printf("Read file. Counting now.\n");

    // get the data from the file
    int data[3];
    getData(file, data);

    if (words)
    {
        printf("Words:\t %d\n", data[0]);
    }

    if (chars)
    {
        printf("Chars:\t %d\n", data[1]);
    }

    if (lines)
    {
        printf("Lines:\t %d\n", data[2]);
    }

    fclose(file);
    return EXIT_SUCCESS;
}
