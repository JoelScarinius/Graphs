#include "graph.h"
#include <stdlib.h>

Graph* createGraph(int numOfNodes)
{   
    Graph *graph = (Graph*)malloc(sizeof(Graph)); //FUCKED UP!
    graph->N = numOfNodes;
    AdjListNode *newNode, *last;
    int i, j, n ,val;
    for (i = 0; i < graph->N; i++)
    {
        last = NULL;
        // Number of neighbours?
        printf("\n Enter the number of neighbours of %d: ", i);
        scanf("%d", &n);
        for(j = 1; j <= n; j++)
        {
            printf("\n Enter the neighbour %d of %d: ", j, i);
            scanf("%d", &val);
            newNode = (AdjListNode*) malloc(sizeof(AdjListNode));
            newNode->graph_node_id = val;
            newNode->next = NULL;
            if (graph->array[i].head == NULL) graph->array[i].head = newNode;
            else last->next = newNode;
            last = newNode;
        }
    }
    // Graph *graph = (Graph*)malloc(sizeof(Graph)); //FUCKED UP!
    // if (graph == NULL) { // If memory wasn't possible to allocate for any reason.
    //     puts("Failed to allocate memory on the heap!");
    //     exit(-1);
    // }
    // graph->N = numOfNodes;
    // graph->array = (AdjList*)malloc(sizeof(AdjList)); 
    // graph->array->head = (AdjListNode*)malloc(sizeof(AdjListNode)); 
    
    // AdjListNode *ptr = graph->array->head; 
    // for (size_t i = 0; i < graph->N; i++) 
    // {
    //     ptr->graph_node_id = i;
    //     if (i != 6) 
    //     {
    //         ptr->next = (AdjListNode*)malloc(sizeof(AdjListNode)); 
    //         ptr = ptr->next;
    //     }
    // }
    // ptr->next = NULL;
    // // Kanske behöver allokera minne för vår array graph->array
    return graph;
}

void displayGraph(Graph* graph, char **cities) // FRÅGA förstår ej denna funktion. Ska inte en parameter vara source också då?
{
    AdjListNode *ptr;
    int i;
    for(i = 0; i < graph->N; i++)
    {
        ptr = graph->array[i].head;
        printf("\n The neighbours of node %d are:", i);
        while(ptr != NULL)
        {
            printf("\t%d", ptr->graph_node_id);
            ptr = ptr->next;
        }
    }
    // AdjListNode *ptr = graph->array->head;
    // for (size_t i = 0; i < graph->N; i++)
    // {
    //     // printf("%d: %s  ", i, cities[i]);
    //     if (ptr->weight != 0)
    //     {
    //         printf("The distance between %s and %s is %d", cities[ptr->graph_node_id], cities[ptr->next->graph_node_id], ptr->weight);
    //         ptr = ptr->next;
    //     }
    //     // printf("The distance between %d: %s and %d: %s is %d", i, cities[i], i, cities[i+1], );
    // }
    
}

void addEdge(Graph* graph, int source, int target, int weight) 
{
    AdjListNode *ptr = graph->array->head;
    for (size_t i = 0; i <= source; i++)
    {
        if (ptr->graph_node_id == source)
        {
            ptr->weight = weight;
            ptr->next->graph_node_id = target;
        }
        else ptr = ptr->next;
    }
}

void deleteEdge(Graph* graph, int source, int target)
{
    AdjListNode *ptr = graph->array->head;
    for (size_t i = 0; i <= source; i++)
    {
        if (ptr->graph_node_id == source)
        {
            ptr->weight = 0;
            ptr->next->graph_node_id = target;
        }
        else ptr = ptr->next;
    }
}