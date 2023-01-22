#include <stdio.h>
#include <stdlib.h>
#include "edges.h"


int deleteEdges(pEdge e) {
    pEdge temp;
    int edgesDeletedNum = 0;
    while (e != NULL) {
        temp = e->next;
        free(e);
        e = temp;
        edgesDeletedNum++;
    }
    return edgesDeletedNum;
}

void deleteEdge(Graph* graph, int src, int dest) {
    pNode srcNode = graph->Nodes[src];
    pEdge edge = srcNode->edgeHead;
    pEdge prevEdge = NULL;
    while (edge != NULL) {
        if (edge->endPoint->data == dest) {
            if (prevEdge == NULL) {
                srcNode->edgeHead = edge->next;
            } else {
                prevEdge->next = edge->next;
            }
            free(edge);
            graph->numEdges--;
            return;
        }
        prevEdge = edge;
        edge = edge->next;
    }
//    printf("Edge from %d to %d not found.\n", src, dest);
}

Edge* newEdgeValue()
{
    Edge* nEdge = (Edge*)calloc(sizeof(Edge),1);

    nEdge->weight = 0;

    //Node* endPoint = (Node*)calloc(sizeof(Node),1);
    nEdge->endPoint = NULL;

    nEdge->next = NULL;

    return nEdge;
}