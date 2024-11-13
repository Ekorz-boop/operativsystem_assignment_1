/*
--------- Task 17 ---------
Your task is to write a program that calculates the number of page faults for a sequence of memory references (i.e., the
memory reference trace in the .mem-files) when using the FIFO (First-In-First-Out) page replacement policy.
Your program shall take as input the number of physical pages, the page size, and the name of the trace file, see the example
below:
./fifo no_phys_pages page_size filename

The program shall write the resulting number of page faults for that specific combination of number of pages and page size,
for either mp3d.mem or mult.mem.

Example execution:
mycomputer$ ./fifo 4 256 mp3d.mem
No physical pages = 4, page size = 256
Reading memory trace from mp3d.mem... Read 100000 memory references
Result: 11940 page faults
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    // Fail fast if too few arguments
    if (argc < 4) {
        // Print error message if too few arguments
        printf("To few args. Use no_phys_pages, page_size, and filename\n");
        // Exit with error code -1 (error)
        exit(-1);
    }

    // Grab the arguments
    char* no_phys_pages = argv[1];
    char* page_size = argv[2];
    char* filename = argv[3];

    // Convert arguments to correct types using atoi (ascii to int)
    int no_phys_pages_int = atoi(no_phys_pages);
    int page_size_int = atoi(page_size);
    // Check for invalid page size
    if (page_size_int <= 0 || no_phys_pages_int <= 0) {
        // Print error message
        printf("Invalid page size or invalid number of physical pages\n");
        // Exit with error code -1 (error)
        exit(-1);
    }

    // Print the first two arguments as per instructions
    printf("No physical pages = %d, page size = %d\n", no_phys_pages_int, page_size_int);

    // Print starting to read memory trace from filename as per instructions
    printf("Reading memory trace from %s... ", filename);

    // Open dat bad boi
    FILE *input_file = fopen(filename, "r");
    // Check for read error
    if (input_file == NULL) {
        // Print error message
        printf("Error reading file\n");
        // Exit with error code -1 (error)
        exit(-1);
    }

    // Set up remaining variables
    int num_pagefaults = 0;
    int num_memory_references = 0;
	size_t line_size = 0;
	char* line;
    size_t num_read_chars = 0;

    // Read the file line by line
    while ((num_read_chars = getline(&line, &line_size, input_file)) != -1) { // While there are lines to read
        // Grab adress from line
        int current_adress = atoi(line);
        // Calculate the page adress
        int page_adress = current_adress - (current_adress % page_size_int);
    }
}
