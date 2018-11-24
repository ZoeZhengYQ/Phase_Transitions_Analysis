//
//  compute.c
//  CSE6010_A2_yzheng394_Compute
//
//  Created by Yingqiao Zheng on 9/23/18.
//  Copyright © 2018 Yingqiao Zheng. All rights reserved.
//

#include "compute.h"

/*
 *  Function to add an edge to a specified vertex
 */
void add_edge(VertexNode *vertexEdges, int nodeID) {
    /* Check input parameter */
    if (vertexEdges == NULL) {
        printf("\nCould not add edge due to empty vertex!\n");
        return;
    }
    /* Allocate and set nextEdge */
    EdgeNode *tmpEdge = malloc(sizeof(EdgeNode));
    if (tmpEdge == NULL) {
        printf("\nMemory allocation for **adjList failed. Abort.\n");
        return;
    }
    tmpEdge -> edge = nodeID;
    tmpEdge -> nextEdge = NULL;
    
    /* Add edge behind the first vertex */
    if (vertexEdges -> firstEdge == NULL) {
        vertexEdges -> firstEdge = tmpEdge;
    }
    /* Add edge behind other edges */
    else {
        EdgeNode *tmpPtr = vertexEdges -> firstEdge;
        while (tmpPtr -> nextEdge != NULL) {
            tmpPtr = tmpPtr -> nextEdge;
        }
        tmpPtr -> nextEdge = tmpEdge;
    }
}


/*
 *  Function to print the adjacency List
 */
void print_adjList(VertexNode **adjList, int vertexNum) {
    if (adjList == NULL) {
        printf("\nEmpty Input Adjacency List!\n");
        return;
    }
    for (int i = 0; i < vertexNum; ++i) {
        /* Print vertex node */
        printf("%d ", adjList[i] -> vertex);
        
        /* See if the vertex has edges */
        if (adjList[i] -> firstEdge != NULL) {
            EdgeNode *tmpPtr = adjList[i] -> firstEdge;
            while (tmpPtr != NULL) {
                printf("%d ", tmpPtr -> edge);
                tmpPtr = tmpPtr -> nextEdge;
            }
        }
        printf("\n");
    }
}


/*
 *  Function to release memory allocated for the adjcency list
 */
void free_adjList(VertexNode **adjList, int vertexNum) {
    if (adjList == NULL) {
        printf("\nEmpty Input Adjacency List!\n");
        return;
    }
    
    for (int i = 0; i < vertexNum; ++i) {
        if (adjList[i] -> firstEdge != NULL) {
            EdgeNode *tmpPtr = adjList[i] -> firstEdge;
            free(adjList[i]);
            while (tmpPtr != NULL) {
                tmpPtr = tmpPtr -> nextEdge;
            }
        }
        else {
            free(adjList[i]);
        }
    }
    free(adjList);
}


/*
 *  DFS function
 */
int DFS_visit(VertexNode **adjList, int nodeID, bool *visited) {
    if (adjList == NULL) {
        printf("\nEmpty Input Adjacency List!\n");
        return 0;
    }
    
    static int count = 0;
    count++;
    // printf("count is %d\n", count);
    // printf("DFS %d ... \n", nodeID);
    visited[nodeID] = true;
    if (adjList[nodeID] -> firstEdge != NULL) {
        EdgeNode *tmpPtr = adjList[nodeID] -> firstEdge;
        while (tmpPtr != NULL) {
            if (!visited[tmpPtr -> edge]) {
                DFS_visit(adjList, (tmpPtr -> edge), visited);
            }
            tmpPtr = tmpPtr -> nextEdge;
        }
    }
    return count;
}


/*
 *  Function to compute all components in input graph
 */
Components *compute_components(VertexNode **adjList, int vertexNum) {
    if (adjList == NULL) {
        printf("\nEmpty Input Adjacency List!\n");
        return NULL;
    }
    bool *visited = NULL;
    Components *firstComponent = NULL;

    int count = 0;
    visited = (bool *)malloc(vertexNum * sizeof(bool));
    for (int i = 0; i < vertexNum; ++i) { visited[i] = false; }
    for (int i = 0; i < vertexNum; ++i) {
        if (!visited[i]) {
            count = DFS_visit(adjList, i, visited);
            Components *tmpComponent = (Components *)malloc(sizeof(Components));
            tmpComponent -> componentsNum = count;
            tmpComponent -> nextComponent = firstComponent;
            // printf(" %d \n", tmpComponent ->componentsNum);
            firstComponent = tmpComponent;
        }
    }
    Components *tmpPtr = firstComponent;
    while (tmpPtr -> nextComponent != NULL) {
        tmpPtr -> componentsNum -= tmpPtr -> nextComponent -> componentsNum;
        // printf(" %d ", tmpPtr -> componentsNum);
        tmpPtr = tmpPtr -> nextComponent;
    }
    // printf(" %d \n", tmpPtr -> componentsNum);
    
    return firstComponent;
}


/*
 *  Function to calculate components in the graph, including
 *  1. the largest component size
 *  2. average component size
 *  3. number of components in the graph
 *  4. histogram of components
 */
void calculate_and_print_to_file(Components *componentArray, FILE *ofp) {
    if (componentArray == NULL) {
        printf("\nEmpty Input Component Array!\n");
        return;
    }
    if (ofp == NULL) {
        printf("\nEmpty Output File Path!\n");
        return;
    }
    
    /* Calculate components */
    Components *tmpPtr = NULL;
    int max = 0;
    int sum = 0;
    int count = 0;
    double average = 0.0;
    
    tmpPtr = componentArray;
    while (tmpPtr != NULL) {
        if (max < tmpPtr -> componentsNum) {
            max = tmpPtr -> componentsNum;
        }
        sum += tmpPtr -> componentsNum;
        tmpPtr = tmpPtr -> nextComponent;
        count ++;
    }
    average = (double)sum / count;
    
    /* Print results to outfile */
    fprintf(ofp, "%d\n", count);
    fprintf(ofp, "%f\n", average);
    fprintf(ofp, "%d\n", max);
    
    /* Create histogram and print to outfile */
    while (1) {     // set 0 to turn off histogram, set 1 to turn on
        int histogram[max];
        memset(histogram, 0, sizeof(histogram));
        
        tmpPtr = componentArray;
        while (tmpPtr != NULL) {
            histogram[(tmpPtr -> componentsNum) - 1]++;
            tmpPtr = tmpPtr -> nextComponent;
        }
        
        for (int i = 0; i < max; ++i) {
            fprintf(ofp, "%d %d\n", i + 1, histogram[i]);
        }
        break;
    }
    
    /*
    for (int i = 0; i < max; ++i) {
        printf("%d %d\n", i + 1, histogram[i]);
    }
     */
    return;
}


/*
 *  Function to release memory allocated for component array
 */
void free_component_array(Components *componentArray) {
    Components *tmpPtr = NULL;
    tmpPtr = componentArray;
    while (tmpPtr != NULL) {
        componentArray = componentArray -> nextComponent;
        free(tmpPtr);
        tmpPtr = componentArray;
    }
    return;
}


/*
 *  Function to read graph and store it as adjacency list from input file
 */
VertexNode **read_graph_from_file(int *vertexNum, FILE *ifp) {
    if (vertexNum == NULL) {
        printf("\nEmpty input vertex number!\n");
        return NULL;
    }
    if (ifp == NULL) {
        printf("\nEmpty input file path.\n");
        return NULL;
    }
    char buf[BUFSIZE];
    VertexNode **adjList;
    int nodeID = 0;
    
    memset(buf, 0, sizeof(buf));
    fgets(buf, sizeof(buf), ifp);
    
    /* Read the first line of input file to get number of vetices */
    for (int i = 0; buf[i] != 10 && buf[i] != 32; ++i) {
        (*vertexNum) = (*vertexNum) * 10 + buf[i] - '0';
    }
    memset(buf, 0, sizeof(buf));
    
    /* Allocate memory for the vertex node and initialize */
    adjList = (VertexNode **)malloc((*vertexNum) * sizeof(VertexNode *));
    if (adjList == NULL) {
        printf("\nMemory allocation for **adjList failed. Abort.\n");
        return 0;
    }
    
    /* Read remaining lines of input file */
    for (int num = 0; num < (*vertexNum); ++num) {
        adjList[num] = (VertexNode *)malloc(sizeof(VertexNode));
        /* Place the vertex node */
        adjList[num] -> vertex = num;
        adjList[num] -> firstEdge = NULL;
        
        /* Read edges from file */
        fgets(buf, sizeof(buf), ifp);
        for (int i = 0; buf[i] != 10; ++i) {
            if (buf[i] != ' ') {
                nodeID = nodeID * 10 + buf[i] - '0';
            }
            /* Add edge when it is NOT the vertex node */
            if (buf[i] == ' ' && nodeID != num) {
                add_edge(adjList[num], nodeID);
            }
            if (buf[i] == ' ') { nodeID = 0; }
        }
    }
    return adjList;
}
