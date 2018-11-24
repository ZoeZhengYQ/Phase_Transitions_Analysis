# Phase_Transitions_Analysis

Author          : Yingqiao Zheng
Created         : September 28, 2018
Last Modified   : September 28, 2018

Affiliation     : Georgia Institute of Technology


Description
-------------

This assignment has two program:
1. The first program is to generate a K * K size grid, with every item colored with probability P, and uncolored with probability (1-P), and then out put the grid in adjacency list format to a txt file;
2. The second program is to first read the txt file from the first program and then compute the components in the adjacency list using DFS algorithm, also, average component size, max component size and the number of components is also computed. And all those result would be write to another txt file along with a histogram.


Note: A connected component (or just component) is defined as a subgraph of the original graph where there is a path between every pair of vertices in the subgraph, and there are no edges between a vertex in the component and any other vertex not in the component. The largest component of a graph is the component with the largest number of vertices. 


Statistics in the output file are:

- The number of components
- The average size (number of vertices) in a component
- The number of vertices in the largest component
- A histogram indicating the distribution of component sizes.


Installation
------------

To install the FIRST program, simply run

    gcc graphgen.c -std=c99 -o graphgen

To install the SECOND program, simply run

    gcc compute.c components.c -std=c99 -o components

Note: The -std=c99 flag is required on some C compilers
to allow variable declarations at arbitrary locations in
a function.



Execution
-----------

Assuming your executable for FIRST program is called "graphgen", run it using

    ./graphgen "size of grid K" "Probability P" "output topology path"

For example,

	./graphgen 100 0.40 topology_100_0.40.txt

This would generate a 100 * 100 grid, with colored probability 0.40, and would create a file and write the grid in adhacency list format in topology_100_0.40.txt



Assuming your executable for SECOND program is called "components", run it using

    ./components "input topology path" "output result path"

For example,

	./graphgen topology_100_0.40.txt result_100_0.40.txt

This would compute the input topology_100_0.40.txt file, and create a outfile named result_100_0.40.txt



