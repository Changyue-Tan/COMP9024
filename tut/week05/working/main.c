#include <stdio.h>    // printf(), scanf()
#include <stdlib.h>   // malloc()
#include <string.h>   // memset()
#include <assert.h>   // assert()

#define NUM_OF_NODES  8
#define MAX_ID_LEN 127

typedef long STACK_ITEM_T;

typedef struct node {    
    struct node *next;
    STACK_ITEM_T item;
} StackNode;



// The type definition of our Stack (based on a linked list)
struct Stack {
    // the top element on stack; 
    // i.e., the first element in the linked list
    StackNode *top;    
    // number of elements on stack
    long n;
};

// Test whether the stack is empty
int StackIsEmpty(struct Stack *pStack) {
    return pStack->n == 0;
}

// Create a stack
struct Stack *CreateStack(void) {
    struct Stack *pStack;

    pStack = (struct Stack *) malloc(sizeof(struct Stack));
    assert(pStack != NULL);
    // empty stack
    pStack->n = 0;
    pStack->top = NULL;
    return pStack;
}


/*
    Release the heap space
 
                ----------            ----------         ----------         ----------      
  pStack -----> top         ------>     next      ------>  next      .....   next: NULL                           
                n                       item               item              item          
                ----------            ----------         ----------         ----------  
               struct Stack           StackNode          StackNode           StackNode   
                                        ^                 ^
                                        ^                 ^
                                        ^                 ^
                                        cur               tmp                        
 */
void ReleaseStack(struct Stack *pStack) {
    StackNode *cur = pStack->top;
    while(cur != NULL) {
        StackNode *tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    free(pStack);
}

/*
    Push an item onto/at the top of the stack.
 
                ----------            ----------         ----------         ----------      
  pStack -----> top         ------>     next      ------>  next      .....   next: NULL                           
                n                       item               item              item          
                ----------            ----------         ----------         ----------  
               struct Stack           StackNode          StackNode           StackNode   
                      

                         ----------
          pNode ---->     next    
                          item     
                         ----------
                        StackNode

 */
void StackPush(struct Stack *pStack, STACK_ITEM_T item) {
    StackNode *pNode = (StackNode *) malloc(sizeof(StackNode));
    assert(pNode);
    // save the item in the StackNode
    pNode->item = item;
    // Let the node pointed to by pNode be the first node in the linked list        
    pNode->next = pStack->top;    
    pStack->top = pNode;
    // increase the number of elements by 1
    pStack->n++;
}

/*
   Pop the top item from the stack.
               
   (1)  Before popping
                ----------            ----------         ----------         ----------      
  pStack -----> top         ------>     next      ------>  next      .....   next: NULL                           
                n                       item               item              item          
                ----------            ----------         ----------         ----------  
               struct Stack           StackNode          StackNode           StackNode  
                                       ^
                                       ^
                                       ^
                                StackNode *top  

   (2)  After popping
                ----------                               ----------          ----------      
  pStack ----->   top        ----------------------->     next        .....   next: NULL              
                   n                                      item                item    
                ----------                               ----------          ----------  
               struct Stack                              StackNode            StackNode   
                                    ----------
                                     next     
                                     item     
                                    ----------
                                    StackNode 
                                       ^
                                       ^
                                       ^
                                StackNode *top        
 */
STACK_ITEM_T StackPop(struct Stack *pStack) {
    assert(!StackIsEmpty(pStack));
    // let 'top' point to the first node in the linked list
    StackNode *top = pStack->top;
    // remove the first node from the linked list
    pStack->top = top->next;
    // decrease the number of elements by 1
    pStack->n--;
    // save the data in a local variable on call stack before calling free(pNode)
    STACK_ITEM_T item = top->item;
    // free the heap space
    free(top);  
    return item;
}

// Peek the top item without popping
STACK_ITEM_T StackPeek(struct Stack *pStack) {
    assert(!StackIsEmpty(pStack));

    STACK_ITEM_T item = pStack->top->item;
    return item;
}

void PrintStack(struct Stack *pStack) {
    StackNode *cur = pStack->top;
    printf("Stack: ");
    // free the heap space of all nodes in the queue
    while (cur != NULL) {
        printf("%ld", cur->item);
        cur = cur->next;
        if(cur) {
            printf(" --> ");
        }
    }
    printf("\n");
}


struct Graph{

    AdjMatrixElementTy *pAdjMatrix;
    struct GraphNode *pNodes;
    long n;
    int isDirected;
};

struct GraphNode {
    char name[MAX_ID_LEN + 1];
    int onstack;
};

#define  MatrixElement(pGraph, u, v)  (pGraph)->pAdjMatrix[(pGraph)->n * (u) + (v)]


static int IsLegalNodeNum(struct Graph *pGraph, long u) {
    return (u >= 0) && (u < pGraph->n); 
}

// Storing information of a graph node



// 0 <= u < n,  0 <= v < n
// ELement(u, v) is (n * u + v) elements away from Element(0, 0)

/*
    Create a graph which can contain n nodes
 */
struct Graph *CreateGraph(long n, int isDirected) {
    assert(n > 0);
    struct Graph *pGraph = (struct Graph *) malloc(sizeof(struct Graph));
    assert(pGraph);
    pGraph->pAdjMatrix = (AdjMatrixElementTy *) malloc(sizeof(AdjMatrixElementTy) * n * n);
    pGraph->pNodes = (struct GraphNode *) malloc(sizeof(struct GraphNode) * n);
    assert(pGraph->pAdjMatrix && pGraph->pNodes);
    memset(pGraph->pAdjMatrix, 0, sizeof(AdjMatrixElementTy) * n * n);
    memset(pGraph->pNodes, 0, sizeof(struct GraphNode) * n);
    pGraph->n = n;
    pGraph->isDirected = isDirected;
    
    return pGraph;
}

void ReleaseGraph(struct Graph *pGraph) {
    assert(pGraph);
    free(pGraph->pNodes);
    free(pGraph->pAdjMatrix);
    free(pGraph);
}


/*
    Add an undirected edge between u and v
 */

void GraphAddUndirectedEdge(struct Graph *pGraph, long u, long v, AdjMatrixElementTy val) {
    if (IsLegalNodeNum(pGraph, u) && IsLegalNodeNum(pGraph, v)) {
        MatrixElement(pGraph, u, v) = val;
        MatrixElement(pGraph, v, u) = val;
    }
}

/*
    Add a directed edge from u to v
 */
void GraphAddDirectedEdge(struct Graph *pGraph, long u, long v, AdjMatrixElementTy val) {
    if (IsLegalNodeNum(pGraph, u) && IsLegalNodeNum(pGraph, v)) {
        MatrixElement(pGraph, u, v) = val;
    }
}

/*
    Add a directed edge from u to v, or an undirected edge between u and v
 */
void GraphAddEdge(struct Graph *pGraph, long u, long v, AdjMatrixElementTy val) {
    if (pGraph->isDirected) {
        GraphAddDirectedEdge(pGraph, u, v, val);
    } else {
        GraphAddUndirectedEdge(pGraph, u, v, val);
    }

}

void GraphAddNode(struct Graph *pGraph, long u, char *name) {
    if (IsLegalNodeNum(pGraph, u)) {        
        snprintf(pGraph->pNodes[u].name, MAX_ID_LEN, "%s", name);
    }
}

// for debugging
void PrintGraph(struct Graph *pGraph) {
    printf("**********  The Adjacency Matrix ************* \n");
    for (long u = 0; u < pGraph->n; u++) {
        for (long v = 0; v < pGraph->n; v++) {
            printf("%ld ", (long) (MatrixElement(pGraph, u, v)));
        }
        printf("\n");
    }
    printf("\n****** Graph Nodes ********\n");
    for (long u = 0; u < pGraph->n; u++) {
        printf("Graph Node %ld: %s\n", u, pGraph->pNodes[u].name);
    }
    printf("\n");
}

#define FILE_NAME_LEN  255

void GenOneImage(struct Graph *pGraph, char *graphName, char *fileName, long seqNo, int *visited) {
    char dotFileName[FILE_NAME_LEN+1] = {0};
    char pngFileName[FILE_NAME_LEN+1] = {0};
    char command[(FILE_NAME_LEN+1)*4] = {0};
    
    snprintf(dotFileName, FILE_NAME_LEN, "%s_%04ld.dot", fileName, seqNo);
    snprintf(pngFileName, FILE_NAME_LEN, "%s_%04ld.png", fileName, seqNo);

    Graph2Dot(pGraph, dotFileName, graphName, pGraph->isDirected, 0, visited, 1);

    snprintf(command, FILE_NAME_LEN*4, "dot -T png %s -o %s", dotFileName, pngFileName);
    
    // Execute the command in a child process (fork() + exec() on Linux)
    system(command); 

}


// #if 0
/*
    Please complete the code in Q1-Q5:

    Q1:  create a data stack
    Q2:  push u onto the data stack
    Q3:  test whether the data stack is empty
    Q4:  push v onto the data stack
    Q5:  free the heap space occupied by the data stack

  */
void NonRecursiveDFS(struct Graph *pGraph, long u) {
    assert(IsLegalNodeNum(pGraph, u));
    static long cnt = 0;

    int *visited = (int *) malloc(sizeof(int) * pGraph->n);
    struct Stack *pStack = ______Q1______;
    assert(visited && pStack);

    for (long i = 0; i < pGraph->n; i++) {
        visited[i] = 0;
    }
    GenOneImage(pGraph, "dfs", "images/NonRecursiveDFS", cnt, visited);
    printf("\n\t\t\t\tpush %ld\n", u);
    ______Q2______;

    while (______Q3______) {
        printf("\n");
        PrintStack(pStack);
        STACK_ITEM_T curNodeId = StackPop(pStack);
        printf("\t\t\t\tpop %ld\n", curNodeId);
        if (!visited[curNodeId]) {
            visited[curNodeId] = 1;
            printf("\t\t\t\t\t\tvisiting %s\n", pGraph->pNodes[curNodeId].name);
            
            cnt++;
            GenOneImage(pGraph, "dfs", "images/NonRecursiveDFS", cnt, visited);             

            //for (long v = 0; v < pGraph->n; v++) {
            for (long v = pGraph->n - 1; v >= 0; v--) {
                if (MatrixElement(pGraph, curNodeId, v) == CONNECTED && !visited[v]) {
                    ______Q4______;
                    printf("\t\t\t\tpush %ld\n", v);
                }
            }            
        }
    }
    printf("\n");
    ______Q5______;
    free(visited);    
}
// #endif


static void DepthFirstSearch(struct Graph *pGraph, long u, int *visited) {
    visited[u] = 1;
    pGraph->pNodes[u].onstack = 1;
    printf("visiting %s\n", pGraph->pNodes[u].name);
    
    static long i = 0;
    i++; 
    GenOneImage(pGraph, "dfs", "images/RecursiveDFS", i, visited);      

    // recursively visit the adjacent nodes of u, if they have not been visited yet
    for(long v = 0; v < pGraph->n; v++) {
        if (MatrixElement(pGraph, u, v) == CONNECTED && !visited[v]) {
            DepthFirstSearch(pGraph, v, visited);
        }
    }
    pGraph->pNodes[u].onstack = 0;
}

void RecursiveDFS(struct Graph *pGraph, long u) {
    int *visited = (int *) malloc(pGraph->n * sizeof(int));
    //memset(visited, 0, sizeof(int) * pGraph->n);
    for (long v = 0; v < pGraph->n; v++) {
        visited[v] = 0;
        pGraph->pNodes[v].onstack = 0;
    }
    GenOneImage(pGraph, "dfs", "images/RecursiveDFS", 0, visited);
    DepthFirstSearch(pGraph, u, visited);
    printf("\n");
    free(visited);
}


/*
    Dot Files

1.  Directed graph with labels

    digraph ShortestGraph {    
    "3" -> {"0"} [label="4"]
    "3" -> {"4"} [label="2"]
    "0" -> {"2"} [label="3"]
    "0" -> {"4"} [label="4"]
    "4" -> {"2"} [label="4"]
    "4" -> {"6"} [label="5"]
    "2" -> {"5"} [label="5"]
    "1" -> {"2"} [label="2"]
    "1" -> {"5"} [label="2"]
    "6" -> {"5"} [label="5"]
    "6" -> {"7"} [label="3"]
    }

2. Undirected graph without labels

    graph DfsGraph {    
    "3" -- {"0"}
    "0" -- {"2"}
    "0" -- {"4"}
    "4" -- {"2"}
    "2" -- {"5"}
    "2" -- {"1"}
    "2" -- {"6"}
    "1" -- {"5"}
    "6" -- {"7"}
    }

3.  Once we get a dot file, we can convert it into a png file.

Week5$ dot -T png images/RecursiveDFS_0000.dot -o images/RecursiveDFS_0000.png   

 */

void Graph2Dot(struct Graph *pGraph, 
               char *filePath,
               char *graphName,
               int isDirectedGraph,
               int displayLabel,
               int *visited,
               int displayVisited) {
    FILE *dotFile = fopen(filePath, "w");
    /*
        FIXME:  check sanity of the parameters.
     */
    if (dotFile) {
        char *edgeConnectorStr = "";
        if (isDirectedGraph) {
            edgeConnectorStr = "->";
            fprintf(dotFile, "digraph %s {\n", graphName);
        } else {
            edgeConnectorStr = "--";
            fprintf(dotFile, "graph %s {\n", graphName);
        }

        for (long u = 0; u < pGraph->n; u++) {
            long vStart = u;
            if (isDirectedGraph) {
                vStart = 0;
            }
            for (long v = vStart; v < pGraph->n; v++) {
                long val = MatrixElement(pGraph, u, v);
                if (val) {
                    fprintf(dotFile, "\"%s\" %s {\"%s\"}", 
                            pGraph->pNodes[u].name, 
                            edgeConnectorStr, 
                            pGraph->pNodes[v].name);
                    if (displayLabel) {
                        fprintf(dotFile, " [label=\"%ld\"]", val);
                    }
                    fprintf(dotFile, "\n"); 
                }
            }
        }
        /*
        "0" [color=red]
         */
        // if (displayVisited && visited) {
        //     for (long i = 0; i < pGraph->n; i++) {
        //         if (visited[i]) {
        //             fprintf(dotFile, "\"%s\" [color=red]\n", pGraph->pNodes[i].name);
        //         }
        //     }
        // }

        // for (long i = 0; i < pGraph->n; i++) {
        //     if (displayVisited && visited && visited[i]) {
        //         fprintf(dotFile, "\"%s\" [color=red]\n", pGraph->pNodes[i].name);
        //     } else {
        //         fprintf(dotFile, "\"%s\"\n", pGraph->pNodes[i].name);
        //     }
        // }

        for (long i = 0; i < pGraph->n; i++) {
            if (displayVisited && visited && visited[i]) {
                if (pGraph->pNodes[i].onstack) {
                    fprintf(dotFile, "\"%s\" [color=red] [shape=box]\n", pGraph->pNodes[i].name);
                } else {
                    fprintf(dotFile, "\"%s\" [color=red]\n", pGraph->pNodes[i].name);
                }
            } else {
                if (pGraph->pNodes[i].onstack) {
                    fprintf(dotFile, "\"%s\"  [shape=box]\n", pGraph->pNodes[i].name);
                } else {
                    fprintf(dotFile, "\"%s\"\n", pGraph->pNodes[i].name);
                }
            }
        }

        fprintf(dotFile, "}\n");
        fclose(dotFile);
    }                
}

/*
    Q1:  create a data stack
    Q2:  push u onto the data stack
    Q3:  test whether the data stack is empty
    Q4:  push v onto the data stack
    Q5:  free the heap space occupied by the data stack
  */

void NonRecursiveDFS(struct Graph *pGraph, long u) {
    // assert(IsLegalNodeNum(pGraph, u));
    static long cnt = 0;

    int *visited = (int *) malloc(sizeof(int) * pGraph->n);
    // struct Stack *pStack = ______Q1______;
    struct Stack *pStack = CreateStack();
    assert(visited && pStack);

    for (long i = 0; i < pGraph->n; i++) {
        visited[i] = 0;
    }
    // GenOneImage(pGraph, "dfs", "images/NonRecursiveDFS", cnt, visited);
    printf("\n\t\t\t\tpush %ld\n", u);
    // ______Q2______;
    StackPush(pStack, u);

    // while (______Q3______) {
    while (StackIsEmpty(pStack)) {
        printf("\n");
        PrintStack(pStack);
        STACK_ITEM_T curNodeId = StackPop(pStack);
        printf("\t\t\t\tpop %ld\n", curNodeId);
        if (!visited[curNodeId]) {
            visited[curNodeId] = 1;
            printf("\t\t\t\t\t\tvisiting %s\n", pGraph->pNodes[curNodeId].name);
            
            cnt++;
            // GenOneImage(pGraph, "dfs", "images/NonRecursiveDFS", cnt, visited);             

            //for (long v = 0; v < pGraph->n; v++) {
            for (long v = pGraph->n - 1; v >= 0; v--) {
                if (MatrixElement(pGraph, curNodeId, v) == CONNECTED && !visited[v]) {
                    // ______Q4______;
                    StackPush(pStack, v);
                    printf("\t\t\t\tpush %ld\n", v);
                }
            }            
        }
    }
    printf("\n");
    // ______Q5______;
    ReleaseStack(pStack);
    free(visited);    
}

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

    PrintGraph(pGraph);

    long u = 3;

    printf("NonRecursiveDFS() starting from node %ld:\n", u);
    NonRecursiveDFS(pGraph, u);

    // ReleaseGraph(pGraph);

    return 0;
}



