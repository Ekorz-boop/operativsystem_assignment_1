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
    /*
    Each Page_struct represents a page in memory.
    Attributes:
    - page_adress: The address of the page in memory
    - time_until_next_reference: The number of memory references until the next reference to this page
    */
    int page_adress;
    int time_until_next_reference;
} Page_struct;


// --- Helper functions ---
int find_optimal_replace(struct Page_struct **pages, int no_phys_pages) {
    /*
    Finds the index of the page that will be referenced the furthest in the future.
    Arguments:
    - pages: An array of Page_structs representing the pages in memory
    - no_phys_pages: The number of physical pages
    Returns:
    - The index of the page that will be referenced the furthest in the future
    */

    // Initialize both vars to NULL so we can check for failure later
    int max_time = NULL;
    int max_time_index = NULL;

    // Loop through all pages
    for (int i = 0; i < no_phys_pages; i++) {
        // If the page has not been referenced yet or if it will be referenced later than the current max time, update max time
        if (pages[i]->time_until_next_reference == -1 || pages[i]->time_until_next_reference > max_time) {
            max_time_index = i;
            max_time = pages[i]->time_until_next_reference;
        }
    }

    // Check for failure
    if (max_time == NULL || max_time_index == NULL) {
        printf("Error finding optimal replacement\n");
        return -1; // Return -1 to indicate failure (since both 0 and 1 are valid indexes these are not suitable for error handling)
    }
    return max_time_index;
}

void calculate_references(struct Page_struct** pages, struct Page_struct** access_sequence, int no_phys_pages,
int access_sequence_counter, int* num_pagefaults) {
    for (int i = 0; i < access_sequence_counter; i++) {
        bool is_found = false;
        for (int j = 0; j < no_phys_pages; j++) {
            if (pages[j]->page_adress == access_sequence[i]->page_adress) {
                is_found = true;
                free(pages[j]);
                pages[j] = access_sequence[i];
                break;
            }
        }

        // Case where the page was not found in memory (page fault)
        if (!is_found) {
            (*num_pagefaults)++;
            int replace_index = find_page_to_replace(pages, no_phys_pages);
            free(pages[replace_index]);
            pages[replace_index] = access_sequence[i];
        }

        // Loop through all pages and decrement the time until next reference since we have made a reference
        for (int j = 0; j < no_phys_pages; j++) {
            if (pages[j]->time_until_next_reference != -1) {
                pages[j]->time_until_next_reference--;
            }
        }
    }
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

    // Print the first two arguments as per instructions
    printf("No physical pages = %d, page size = %d\n", no_phys_pages_int, page_size_int);
    printf("Reading memory trace from %s... ", filename);

    // Open the file
    FILE *input_file = fopen(filename, "r");
    if (input_file == NULL) { // Check for read error
        printf("Error reading file\n");
        return 1;
    }


















    return 0;
}
