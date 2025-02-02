#include <stdio.h>    // printf()
#include <stdlib.h>   // system()
#include "Graph.h"


#define NUM_OF_NODES  8


int main(void) {
    // Create a directed graph with 8 nodes
    struct Graph *pGraph = CreateGraph(NUM_OF_NODES, 1);

    //char *nodeNames[NUM_OF_NODES] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    char *nodeNames[NUM_OF_NODES] = {"0", "1", "2", "3", "4", "5", "6", "7"};
    
    // Add nodes
    for (long u = 0; u < NUM_OF_NODES; u++) {
        GraphAddNode(pGraph, u, nodeNames[u]);
    }
    // edges: source node id, target node id, value of the edge
    long edges[][3] = {
        {3, 0, CONNECTED},
        {0, 2, CONNECTED},
        {0, 4, CONNECTED},
        {4, 2, CONNECTED},

        {2, 5, CONNECTED},
        {2, 1, CONNECTED},
        {2, 6, CONNECTED},
        {1, 5, CONNECTED},
        {6, 7, CONNECTED}, 
    }; 

    // Add edges
    for (long i = 0; i < sizeof(edges)/sizeof(edges[0]); i++) {
        GraphAddEdge(pGraph, edges[i][0], edges[i][1], edges[i][2]);
    }

    // PrintGraph(pGraph);

    // // create a sub-directory 'images' (if it is not present) in the current directory
    // system("mkdir -p images");
    // // remove the *.dot and *.png files in the directory 'images'
    // system("rm -f images/*.dot images/*.png");

    long u = 3;

    // printf("RecursiveDFS() starting from node %ld:\n\n", u);
    // RecursiveDFS(pGraph, u);

    printf("\n\nNonRecursiveDFS() starting from node %ld:\n", u);
    // printf("After completing the code in Q1-Q5 (Graph.c), please also uncomment line %d in %s:\n\n", (__LINE__ + 1), __FILE__);
    NonRecursiveDFS(pGraph, u);

    ReleaseGraph(pGraph);

    return 0;
}