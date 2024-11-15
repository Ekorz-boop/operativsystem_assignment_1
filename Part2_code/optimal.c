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

// Function to find the page to replace based on the future references
int find_page_to_replace(int *pages, int num_pages, int *references, int ref_count, int current_index) {
    int farthest = -1;
    int replace_index = -1;

    for (int i = 0; i < num_pages; i++) {
        int j;
        for (j = current_index + 1; j < ref_count; j++) {
            if (pages[i] == references[j]) {
                if (j > farthest) {
                    farthest = j;
                    replace_index = i;
                }
                break;
            }
        }
        if (j == ref_count) { // Page not used again
            return i;
        }
    }
    return (replace_index != -1) ? replace_index : 0; // Default to first page if all are equally far
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s no_phys_pages page_size filename\n", argv[0]);
        return 1;
    }

    int no_phys_pages = atoi(argv[1]);
    int page_size = atoi(argv[2]);
    const char *filename = argv[3];

    printf("No physical pages = %d, page size = %d\n", no_phys_pages, page_size);
    printf("Reading memory trace from %s...", filename);

    // Read memory references from file
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    int references[MAX_REFERENCES];
    int ref_count = 0;
    unsigned long address;
    size_t line_size = 0;
    char *line;

    while (getline(&line, &line_size, file) != -1) {
        address = atoi(line);
        references[ref_count++] = address / page_size; // Convert address to page number
        if (ref_count >= MAX_REFERENCES) break;
    }
    fclose(file);
    printf("Read %d memory references\n", ref_count);

    // Simulate Optimal Page Replacement
    int *pages = (int *)malloc(no_phys_pages * sizeof(int));
    int num_pages = 0, page_faults = 0;

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
            page_faults++;
            if (num_pages < no_phys_pages) {
                pages[num_pages++] = page; // Add page if memory is not full
            } else {
                // Replace the page using Optimal Replacement Policy
                int replace_index = find_page_to_replace(pages, num_pages, references, ref_count, i);
                pages[replace_index] = page;
            }
        }
    }

    free(pages);

    printf("Result: %d page faults\n", page_faults);
    return 0;
}