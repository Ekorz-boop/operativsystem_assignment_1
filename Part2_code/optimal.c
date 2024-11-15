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
#include <string.h>

#define MAX_REFERENCES 100000

// --- Helper functions ---
int find_optimal_page_replacement(int *pages, int num_phys_pages, int *access_sequence, int access_sequence_count, int current_index) {
    /*
    Finds the optimal page to replace in memory using the Optimal Replacement Policy (Bélády’s algorithm).
    The optimal page to replace is the one that will not be used again for the longest time in the future.
    Arguments:
    - pages: Array of page numbers currently in memory
    - num_phys_pages: Number of physical pages in memory
    - access_sequence: Array of memory references
    - access_sequence_count: Number of memory references
    - current_index: Index of the current memory reference in the access sequence
    Returns:
    - Index of the page to replace in the pages array
    */
    // Vars needed to keep track of the page with the longest distance to the next use
    int max_distance = -1;
    int current_output = -1;

    // Loop through all pages in memory
    for (int i = 0; i < num_phys_pages; i++) {
        // Variable to keep track of if the page is used again or not
        int next_use_index = access_sequence_count;

        // Loop through the rest of the access sequence to find the next use of the page
        for (int j = current_index + 1; j < access_sequence_count; j++) {
            if (pages[i] == access_sequence[j]) { // Page is used again (i.e. found in the access sequence)
                if (j > max_distance) {
                    // Set max distance to current distance (j)
                    max_distance = j;

                    // Set the current output to the index of the page in memory (i)
                    current_output = i;
                }
                // Before breaking, set the next use index to the current index so we can check if the page is used again
                next_use_index = j;
                break;
            }
        }
        // Check if page is ever used again or not (if the value is the same as the input count, it was not used again)
        if (next_use_index == access_sequence_count) {
            // Return the page that is never used again
            return i;
        }
    }

    // Check if the current output is -1 (i.e. no page was used again)
    if (current_output == -1) {
        // If no page was used again, return the last page in memory
        return num_phys_pages - 1;
    }

    // Return the page that is used the furthest in the future
    return current_output;
}


// --- Main program ---
int main(int argc, char *argv[]) {
    // Fail fast if too few arguments
    if (argc < 4) {
        // Print error message if too few arguments
        printf("To few args. Use no_phys_pages, page_size, and filename\n");
        // Return with error
        return 1;
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
        // Return with error
        return 1;
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
        // Return with error
        return 1;
    }

    size_t line_size = 0;
    char *line;
    int needed_array_size = 0;
    // Calculate how large the references array must be
    while (getline(&line, &line_size, input_file) != -1) {
        needed_array_size++;
    }
    // Reset file pointer so we can read the file again
    fseek(input_file, 0, SEEK_SET);

    // Set the references array to the correct size (should work for all sizes since we calculate it)
    int references[needed_array_size];

    // Set the vars for reading the file for real this time
    int ref_count = 0;
    unsigned long current_address;

    // Read the file and convert the addresses to page numbers
    while (getline(&line, &line_size, input_file) != -1) {
        // Convert the line to an int with atoi
        current_address = atoi(line);

        // Add the page number to the references array
        references[ref_count++] = current_address - (current_address % page_size_int);
    }
    fclose(input_file);
    printf("Read %d memory references\n", ref_count);

    // Simulate Optimal Page Replacement
    int *pages = (int *)malloc(no_phys_pages_int * sizeof(int));
    int num_pages = 0;
    int num_page_faults = 0;

    for (int i = 0; i < ref_count; i++) {
        int page = references[i];
        int found = 0;

        // Check if page is already in memory
        for (int j = 0; j < num_pages; j++) {
            if (pages[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) { // Page fault
            num_page_faults++;
            if (num_pages < no_phys_pages_int) {
                pages[num_pages++] = page; // Add page if memory is not full
            } else {
                // Replace the page using Optimal Replacement Policy
                int replace_index = find_optimal_page_replacement(pages, num_pages, references, ref_count, i);
                pages[replace_index] = page;
            }
        }
    }

    free(pages);

    printf("Result: %d page faults\n", num_page_faults);
    return 0;
}