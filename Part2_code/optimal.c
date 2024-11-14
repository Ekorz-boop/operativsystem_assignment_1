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

// --- Struct for page ---
typedef struct Page_struct {
    int adress;
    struct Page_struct* next_page;
} Page_struct;

// --- Variables for handling the double linked list (page list) ---
int list_length = 0;
Page_struct* first_page = NULL;
Page_struct* last_page = NULL;

// --- Helper functions ---



// --- Main function ---
int main(int argc, char *argv[]) {
    /*
    Main function for the beladys algorithm program.
    Calculates the minimum number of page faults for a sequence of memory references.
    */

    // Fail fast if too few arguments
    if (argc < 4) {
        // Print error message if too few arguments
        printf("To few args. Use no_phys_pages, page_size, and filename\n");
        // Return with error
        return 1;
    }
}
