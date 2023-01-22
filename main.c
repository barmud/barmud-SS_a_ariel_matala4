#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "algo.h"
#include "nodes.h"
#include "edges.h"
#define false 0
#define true 1

int main(int argc, char const *argv[])
{

    pGraph graph = NULL;
    char *func = (char *)calloc(sizeof(char), 1);
    *func = getc(stdin);

    while (*func != EOF && *func != ' ' && *func != '\n')
    {
        if (*func == 'A')
        {
            if (graph!=NULL)
            {
                freeAll(graph);
                graph = NULL;
            }
            
            graph = functionA(func);
        }
        if (*func == 'B')
        {
            functionB(graph, func);
        }

        if (*func == 'D')
        {
            functionC(graph, func);
        }

        if (*func == 'S')
        {
            if (getc(stdin) == '\n')
                break; // skip the space
            int src = getc(stdin) - '0';
            if (src == '\n')
                break;
            getc(stdin); // skip the space
            int dest = getc(stdin) - '0';
            int shortestPath = dijkstra(graph, src, dest);
            printf("Dijsktra shortest path: %d\n", shortestPath);
        }

        if (*func == 'T')
        {
            getc(stdin); // skip the space;
            int k = 0;
            k = getc(stdin) - '0';
            int *vertex = (int *)calloc(sizeof(int) , k);
            for (int i = 0; i < k; ++i)
            {
                getc(stdin);
                vertex[i] = 0;                   // skip the space;
                vertex[i] = getc(stdin) - '0'; // getting vertex
            }
            TSP(graph, k, vertex);
            char temp = getc(stdin); // skip the space;
            if (temp != EOF && temp != ' ' && temp != '\n')
            {
                getc(stdin);
            }
            if (temp == '\n')
            {
                *func = temp;
            }
            else
            {
                *func = getc(stdin);
            }
            free(vertex);
        }
    }
    freeAll(graph);
    free(func);
}

Graph *functionA(char *func)
{
    Graph *graph = (Graph *)calloc(sizeof(Graph), 1);
    getc(stdin); // skip the space;

    int numNodes = (int)(getc(stdin) - '0');
    fillNodesArray(graph, numNodes);
    graph->numNodes = numNodes;
    char c = getc(stdin);
    pEdge *edgeCurr;

    while (c != EOF && c != 'S' && c != 'D' && c != 'B' && c != 'A' && c != 'T') // keep looping until end of file.
    {

        if (c != 'n')
            c = getc(stdin); // got 'n' or EOF
        getc(stdin);         // skip the space

        c = getc(stdin); // the first vertex we work on.

        edgeCurr = &(graph->Nodes)[c - '0']->edgeHead;
        getc(stdin); // skip the space

        c = getc(stdin); // endpoint

        while (c != EOF && c != 'n' && c != 'S' && c != 'D' && c != 'B' && c != 'A' &&
               c != 'T') // looping for each vertex.
        {
            *edgeCurr = newEdgeValue();
            graph->numEdges++;

            getc(stdin); // skip the space
            int i = (int)(c - '0');
            (*edgeCurr)->endPoint = (graph->Nodes[i]);

            c = getc(stdin); // getting the weight
            (*edgeCurr)->weight = (int)(c - '0');
            c = getc(stdin); // skip space

            edgeCurr = &((*edgeCurr)->next);
            if (c == '\n')
                break;
            c = getc(stdin); // getting next value
        }
    }
    *func = c;
    return graph;
}

void functionB(pGraph graph, char *func)
{

    getc(stdin);
    int nodeNum = (int)(getc(stdin) - '0');
    if (nodeNum > graph->numNodes)
    {

        graph->Nodes = realloc(graph->Nodes, (graph->numNodes + 1) * sizeof(Node));

        //~~~~~~~~~~~~~~~~~~~~~~~Problem~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //~~~~~~~~~~~~~~~~~~~~~~~Problem~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //~~~~~~~~~~~~~~~~~~~~~~~Problem~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //~~~~~~~~~~~~~~~~~~~~~~~Problem~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //~~~~~~~~~~~~~~~~~~~~~~~Problem~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        for (int i = graph->numNodes; i < sizeof(graph->Nodes); i++)
        { // filling the array with unconnected nodes
            graph->Nodes[i] = newNode(i);
            graph->Nodes[i]->flag = 0;
            graph->numNodes++;
        }
    }
    else
    {
        if (graph->Nodes[nodeNum]->edgeHead != NULL)
        {
            pEdge edgeHead = graph->Nodes[nodeNum]->edgeHead;
            if (edgeHead != NULL)
            {
                int edgesDeleted = deleteEdges(edgeHead);
                graph->numEdges -= edgesDeleted; // updating edgesNum value
            }
        }
    }

    graph->Nodes[nodeNum]->flag = 1; // connect the new node to the graph
    pEdge *edgeCurr;
    getc(stdin); // skip the space
    edgeCurr = &(graph->Nodes)[nodeNum]->edgeHead;
    char c = getc(stdin);                                                                    // get the endpoint
    while (c != EOF && c != 'n' && c != 'S' && c != 'D' && c != 'B' && c != 'A' && c != 'T') // looping for each vertex.
    {
        *edgeCurr = newEdgeValue();
        graph->numEdges++;

        getc(stdin);                               // skip the space
        int i = (int)(c - '0');                    // index
        (*edgeCurr)->endPoint = (graph->Nodes[i]); // endpoint is the node at index i of the nodes array

        c = getc(stdin);                      // getting the edge weight
        (*edgeCurr)->weight = (int)(c - '0'); // initializing edge weight
        c = getc(stdin);                      // skip the space

        edgeCurr = &((*edgeCurr)->next);
        if (c == '\n')
            break;
        c = getc(stdin); // trying to get next value
    }
    *func = c;
}

void functionC(pGraph graph, char *func)
{
    getc(stdin); // skip the space
    int nodeNum = (int)(getc(stdin) - '0');
    pEdge edgeHead = graph->Nodes[nodeNum]->edgeHead;

    int edgesDeleted = deleteEdges(edgeHead);
    graph->Nodes[nodeNum]->edgeHead = NULL;
    graph->numEdges -= edgesDeleted; // updating edgesNum value

    for (int i = 0; i < graph->numNodes; ++i)
    {
        if (graph->Nodes[i]->flag == 1)
            deleteEdge(graph, i, nodeNum);
    }
    graph->Nodes[nodeNum]->flag = 0;
    getc(stdin);
    *func = getc(stdin);
}

void TSP(pGraph graph, int k, int *currNodes)
{

    int **arr = NULL;
    arr = TSPhelp(graph, k, currNodes);

    int minDist = __INT_MAX__;                     // variable to store the minimum distance found
    int *tempPath = NULL;                          // array to store the current path
    tempPath = (int *)calloc(k, sizeof(int)); 

    memcpy(tempPath, currNodes, k * sizeof(int));
    int totalDist = 0;

    do
    {
        totalDist = 0;

        int dist = 0;
        for (int j = 0; j < k - 1; j++)
        {
            dist = arr[tempPath[j]][tempPath[j + 1]];
            if (dist == -1)
            {
                totalDist = __INT_MAX__;
                break;
            }
            totalDist += dist;
        }
        if (totalDist < minDist)
        {
            minDist = totalDist;
        }

    } while (next_permutation(tempPath, k));
    if (minDist == __INT_MAX__)
    {
        minDist = -1;
    }

    free(tempPath);
    printf("TSP shortest path: %d \n", minDist);

    freeTSP(arr, graph->numNodes);
}

void freeAll(Graph *p)
{
    for (int i = 0; i < p->numNodes; i++)
    {
        deleteEdges((p->Nodes[i])->edgeHead);
        free(p->Nodes[i]);
    }
    free(p->Nodes);
    free(p);
}

int compare(const void *a, const void *b)
{
    int x = *((int *)a);
    int y = *((int *)b);
    return x - y;
}

bool next_permutation(int *arr, int n)
{
    int i, j;
    for (i = n - 2; i >= 0; i--)
    {
        if (arr[i] < arr[i + 1])
            break;
    }

    if (i == -1)
        return false;

    for (j = n - 1; j > i; j--)
    {
        if (arr[j] > arr[i])
            break;
    }

    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;

    int k = i + 1, l = n - 1;
    while (k < l)
    {
        temp = arr[k];
        arr[k] = arr[l];
        arr[l] = temp;
        k++;
        l--;
    }
    return true;
}

// void printGraph(pGraph graph) {
//
//     printf("Graph with %d nodes and %d edges:\n", graph->numNodes, graph->numEdges);
//     for (int i = 0; i < graph->numNodes; i++) {
//         if (graph->Nodes[i]->flag == 1) {
//             printf("Node %d: ", i);
//             pEdge edge = graph->Nodes[i]->edgeHead;
//             while (edge != NULL) {
//                 if (edge->endPoint->flag != 1) break;
//                 printf("(%d, %d, %d) ", i, edge->endPoint->data, edge->weight);
//                 edge = edge->next;
//             }
//             printf("\n");
//         }
//     }
// }

int factorial(int n)
{
    if (n == 0)
    {
        return 1;
    }
    return n * factorial(n - 1);
}

int *allShortToAnyV(pGraph graph, int nodeNum)
{

    int *arr = (int *)calloc(graph->numNodes, sizeof(int));
    for (int i = 0; i < graph->numNodes; i++)
    {
        arr[i] = dijkstra(graph, nodeNum, i);
    }
    return arr;
}

int **TSPhelp(pGraph graph, int k, int *currNodes)
{
    qsort(currNodes, k, sizeof(int), compare);
    int **arr = NULL;

    arr = (int **)calloc(graph->numNodes, sizeof(int *));
    int p = 0;
    for (int i = 0; i < graph->numNodes; i++)
    {
        if (p<k)
        {
            if (i == currNodes[p])
            {
                arr[i] = allShortToAnyV(graph, currNodes[p]);
                p++;
            }
        }
    }
    return arr;
}

void freeTSP(int **arr, int k)
{
    if (arr != NULL)
    {
        for (int i = 0; i < k; i++)
        {
            if (arr[i] != NULL)
            {
                free(arr[i]);
                arr[i] = NULL;
            }
        }
        free(arr);
        arr = NULL;
    }
}

void freeNodesAll(Node **arr, int k)
{
    if (arr != NULL)
    {
        for (int i = 0; i < k; i++)
        {
            if (arr[i] != NULL)
            {
                deleteEdges(arr[i]->edgeHead);
                free(arr[i]);
                arr[i] = NULL;
            }
        }
        free(arr);
        arr = NULL;
    }
}
