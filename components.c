//
//  main.c
//  CSE6010_A2_yzheng394_Compute
//
//  Created by Yingqiao Zheng on 9/22/18.
//  Copyright © 2018 Yingqiao Zheng. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "compute.h"


int main(int argc, const char * argv[]) {
    FILE *ifp;              // Input file path
    FILE *ofp;              // Output file path
    int  vertexNum = 0;     // Number of vertex in the input graph
    VertexNode **adjList = NULL;        // Adjacency list read from input file
    Components *componentArray = NULL;  // Array of components of the graph
    
    ifp = fopen(argv[1], "r");
    ofp = fopen(argv[2], "w");
    
    /* Read adjacency list from file */
    adjList = read_graph_from_file(&vertexNum, ifp);
    fclose(ifp);
    
    // print_adjList(adjList, vertexNum);
    
    /* Compute components using DFS */
    componentArray = compute_components(adjList, vertexNum);
    
    /* Calculate components and print the results to outfile */
    calculate_and_print_to_file(componentArray, ofp);
    
    /* Release memory allocated for adjcency list and component list */
    free_adjList(adjList, vertexNum);
    free_component_array(componentArray);
    fclose(ofp);
    
    return 0;
}
