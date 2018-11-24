//
//  compute.h
//  CSE6010_A2_yzheng394_Compute
//
//  Created by Yingqiao Zheng on 9/23/18.
//  Copyright © 2018 Yingqiao Zheng. All rights reserved.
//

#ifndef compute_h
#define compute_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define BUFSIZE 65536

/* Struct define */
typedef struct node{
    int edge;
    struct node* nextEdge;
}EdgeNode;

typedef struct{
    int vertex;
    EdgeNode* firstEdge;
}VertexNode;

typedef struct components{
    int componentsNum;
    struct components *nextComponent;
}Components;

/* Function declaration */
int  DFS_visit(VertexNode **adjList, int nodeID, bool *visited);
void add_edge(VertexNode *vertexEdges, int nodeID);
void print_adjList(VertexNode **adjList, int vertexNum);
void calculate_and_print_to_file(Components *componentArray, FILE *ofp);
void free_adjList(VertexNode **adjList, int vertexNum);
void free_component_array(Components *componentArray);
Components *compute_components(VertexNode **adjList, int vertexNum);
VertexNode **read_graph_from_file(int *vertexNum, FILE *ifp);

#endif /* compute_h */
