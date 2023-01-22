#ifndef ALGO_
#define ALGO_

#include <stdbool.h>

typedef struct Node_
{
    int data;
    int flag;
    struct Edge_ *edgeHead; //head of edge list
} Node,*pNode;

typedef struct Edge_{
    int weight;
    Node *endPoint;
    struct Edge_* next;
}Edge,*pEdge;

typedef struct Graph_
{
    int numNodes;
    int numEdges;
    pNode* Nodes;
}Graph,*pGraph;


Graph *functionA(char* func);
void functionB(pGraph graph, char* func);
void functionC(pGraph graph,char * func);
bool next_permutation(int *arr, int n);
void TSP(pGraph graph, int k, int *currNodes);
void fillNodesArray(pGraph graph, int n);
int dijkstra(Graph *graph, int src, int dest);
int compare(const void *a, const void *b);
void printGraph(pGraph graph);
void freeAll(Graph *p);
int minDistance(pNode *graphNodes, int dist[], int visited[], int V);
int factorial(int n);
int** TSPhelp(pGraph graph, int k, int *currNodes);
int * allShortToAnyV(pGraph graph, int nodeNum);
void freeTSP(int** arr, int k);
void freeNodesAll(Node **arr, int k);
void freeArray(Node** NodeArr , int k);




#endif