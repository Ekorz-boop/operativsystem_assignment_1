/*
--------- Task 20 ---------
Your task is to write a program that calculates the number of page faults for a sequence of memory references (i.e., the
memory reference trace in the .mem-files) when using the LRU (Least-Recently-Used) page replacement policy.
Your program shall take as input the number of physical pages, the page size, and the name of the trace file, see the example
below:

./lru no_phys_pages page_size filename

The program shall write the resulting number of page faults for that specific combination of number of pages and page size,
for either mp3d.mem or mult.mem.
Example execution:

mycomputer$ ./lru 4 256 mp3d.mem
No physical pages = 4, page size = 256
Reading memory trace from mp3d.mem... Read 100000 memory references
Result: 9218 page faults
*/

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {

}
