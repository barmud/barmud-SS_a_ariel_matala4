#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"


Node* newNode(int dataNew)
{
    Node* node = (Node*)calloc(sizeof(Node),1);

    node->data = dataNew;

    node->flag = 1;

    //Edge* edgeHead = (Edge*)calloc(sizeof(Edge),1);
    node->edgeHead = NULL;

    return node;
}

void fillNodesArray(pGraph graph, int n){
    graph->Nodes = (Node**)calloc(n,sizeof(Node));
    for (int i = 0; i < n; i++) {
        ((graph->Nodes)[i]) = (Node*)calloc(sizeof(Node),1);
        ((graph->Nodes)[i])->data = i;
        ((graph->Nodes)[i])->flag = 1; // this node is not connected to the graph yet
        ((graph->Nodes)[i])->edgeHead = NULL;
    }
}

int dijkstra(Graph *graph, int src, int dest) {

    int V = graph->numNodes;
    if (dest > V || src > V || src < 0 || dest < 0) return -1;

    int dist[V]; //array of distance from src.
    int visited[V];

    for (int i = 0; i < V; i++) {
        dist[i] = __INT_MAX__;
        visited[i] = false;
    }
    dist[src] = 0; // distance from src to src.

    for (int i = 0; i < V - 1; i++) {
        int u = minDistance(graph->Nodes, dist, visited, V);
        visited[u] = true;
        if (u == dest) break; // done

        if (u != -1) {
            if (graph->Nodes[u]->flag == 0) continue; // this vertex is not part of the graph

            if (graph->Nodes[u]->edgeHead == NULL) break;

            pEdge pCrawl = graph->Nodes[u]->edgeHead;
            while (pCrawl != NULL) {
                int v = pCrawl->endPoint->data;
                if (!visited[v] && dist[u] + pCrawl->weight < dist[v]) {
                    dist[v] = dist[u] + pCrawl->weight;
                }
                pCrawl = pCrawl->next;
            }
        }
    }
    if (dist[dest] == __INT_MAX__) dist[dest] = -1;
    return dist[dest];
}

int minDistance(pNode *graphNodes, int dist[], int visited[], int V) {
    int min = __INT_MAX__, min_index = -1; // check
    for (int v = 0; v < V; v++) {
        if (visited[v] == false && dist[v] <= min && graphNodes[v]->flag == 1) {
            min = dist[v];
            min_index = v;
        }
    }
    if (min == __INT_MAX__ || min_index == -1) {
        return -1;
    }
    return min_index;
}