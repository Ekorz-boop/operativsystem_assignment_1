/*
--------- Task 23 ---------
Your task is to write a program that calculates the minimum number of page faults for a sequence of memory references,
i.e., you should implement the Optimal page replacement policy (which is also known as Bélády’s algorithm).
Your program shall take as input the number of physical pages, the page size, and the name of the trace file, see the example
below:

./optimal no_phys_pages page_size filename

The program shall write the resulting number of page faults for that specific combination of number of pages and page size,
for either mp3d.mem or mult.mem.
Example execution:

mycomputer$ ./optimal 32 128 mp3d.mem
No physical pages = 32, page size = 128
Reading memory trace from mp3d.mem... Read 100000 memory references
Result: 824 page faults
*/


// --- Includes ---
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Struct so we can keep track of referencing times
typedef struct Page_struct {
    int page_adress;
    int time_until_next_reference;
} Page_struct;


// --- Helper functions ---
int prediction_function() {
    // Implement the prediction function here
    return 0;
}


// --- Main function ---
int main(int argc, char *argv[]) {

    // Fail fast if too few arguments
    if (argc < 4) {
        printf("Too few args. Use no_phys_pages, page_size, and filename\n");
        return 1;
    }

    // Grab the arguments from the command line
    char* no_phys_pages = argv[1];
    char* page_size = argv[2];
    char* filename = argv[3];

    // Convert arguments to int using atoi (ascii to int)
    int no_phys_pages_int = atoi(no_phys_pages);
    int page_size_int = atoi(page_size);
    if (page_size_int <= 0 || no_phys_pages_int <= 0) {
        printf("Invalid page size or invalid number of physical pages\n");
        return 1;
    }
    // Create array of pages with size no_phys_pages_int
    // FIXME: This should be an array of Page_structs ?

    // Print the first two arguments as per instructions
    printf("No physical pages = %d, page size = %d\n", no_phys_pages_int, page_size_int);
    printf("Reading memory trace from %s... ", filename);

    // Open the file
    FILE *input_file = fopen(filename, "r");
    if (input_file == NULL) { // Check for read error
        printf("Error reading file\n");
        return 1;
    }
}
