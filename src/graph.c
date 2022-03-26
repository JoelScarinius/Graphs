#include "graph.h"
#include <stdlib.h>

Graph* createGraph(int numOfNodes)
{   
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->N = numOfNodes;
    graph->array = (AdjList*)malloc(numOfNodes * sizeof(AdjList)); // Create an N-size array of adjacency lists.  

    for (int i = 0; i < numOfNodes; ++i)//Initialize each adjacency list
    { 
        graph->array[i].head = (AdjListNode*)malloc(sizeof(AdjListNode));
        graph->array[i].head->graph_node_id = i;
        graph->array[i].head->next = NULL;
        // AdjListNode* head = (AdjListNode*)malloc(sizeof(AdjListNode));
        // head->graph_node_id = i;
        // head->next = NULL;
        // graph->array[i].head = head;
    }
    return graph;
}

void displayGraph(Graph* graph, char **cities) // print the graph
{
    for (int i = 0; i < graph->N; i++) {
        AdjListNode* head = graph->array[i].head;
   
        printf("\nAdjacency list of vertex %d ", head->graph_node_id);
            
        AdjListNode* adjNode = head->next;
        while (adjNode != NULL) {
            printf(" -> %d ", adjNode->graph_node_id);
            adjNode = adjNode->next;
        }
        printf("\n");      
    }
    printf("\n");    
}

void addEdge(Graph* graph, int source, int target, int weight) 
{
    AdjListNode* newAdjListNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newAdjListNode->graph_node_id = target;
    newAdjListNode->next = NULL;

    AdjListNode *adjListNode = graph->array[source].head;

    while(adjListNode->next != NULL){
        adjListNode = adjListNode->next;
    }
    adjListNode->next = newAdjListNode;
}

void deleteEdge(Graph* graph, int source, int target)
{
    if (graph->array[source].head->next == NULL) return;
    else
    {
        AdjListNode* prev = graph->array[source].head;
        AdjListNode* temp = graph->array[source].head->next;

        while( temp != NULL && temp->graph_node_id != target){
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL) return; // If target is not present in the adjacent list
        prev->next = temp->next; // Unlink the node from the adjacent list
        free(temp); // Free memory
    }
}