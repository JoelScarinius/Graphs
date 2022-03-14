// The main function for the program to find the shortest path between cities.
//
//Written by He Tan, March 2022
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "graph.h"

//the number of nodes in the graph
#define GRAPH_NODE_N 7
#define INFINITY 9999


//the function that calculates the distances of shortest paths between cities
//parameters: source_node, the id of the source node
//            dist, the minimum distance
//            graph, the graph
void dijkstra(int source_node, int dist[], Graph* graph);


int main(void)
{
    char *cities[GRAPH_NODE_N] = {"Jönköping", "Ulricehamn", "Värnamo", "Göteborg", "Helsingborg", "Ljungby", "Malmö"};

    Graph* graph = createGraph(GRAPH_NODE_N);

    //0: Jönköping, 1: Ulricehamn, 2: Värnamo, 3: Göteborg, 4: Helsingborg, 5: Ljunby, 6: Malmö
    addEdge(graph, 0, 2, 2);
    addEdge(graph, 1, 0, 4);
    addEdge(graph, 3, 1, 15);
    addEdge(graph, 3, 5, 5);
    addEdge(graph, 3, 6, 23);
    addEdge(graph, 4, 1, 17);
    addEdge(graph, 4, 6, 11);
    addEdge(graph, 5, 2, 9);
    addEdge(graph, 5, 6, 13);

    displayGraph(graph, cities);

    int source_node;
    printf("\n0: Jönköping, 1: Ulricehamn, 2: Värnamo, 3: Göteborg, 4: Helsingborg, 5: Ljunby, 6: Malmö");
    printf("\nEnter the city :  ");
    scanf("%d", &source_node);


    //store the minimun distance
    int dist[GRAPH_NODE_N];
    // dijkstra(source_node, dist, graph);

    printf("\nThe distance of the shortest path for travelling from %s to ", cities[source_node]);
    for(int i=0; i<GRAPH_NODE_N; i++ )
    {
        if(dist[i] == INFINITY)
            printf("\n%s !!! no connection between these two cities", cities[i]);
        else printf("\n%s is %d", cities[i], dist[i]);
    }
    printf("\n");
    return 0;
}

void dijkstra(int source_node, int dist[], Graph* graph) //
{   
    
    
    // Steps 1 - 3
    // AdjListNode *ptr = graph->array->head; // Tror detta blir fel
    // ptr->graph_node_id = 0;
    // dist[0] = ptr->weight;

    // AdjListNode *ptr = graph->array->head; // Detta känns mest rätt
    // for (size_t i = 0; i < graph->N; i++)
    // {
    //     if (ptr->graph_node_id == source_node)
    //     {
    //         ptr->graph_node_id = 0;
    //         dist[0] = ptr->weight;
    //     }
    //     ptr = ptr->next;
    // }
    // for (size_t i = 1; i <= graph->N; i++)
    // {
    //     ptr->graph_node_id = 0;
    //     dist[i] = ptr->weight;
    // }
    
     
    /*
    ALGORITHM
    1. Select the source node also called the initial node
    2. Define an empty set N that will be used to hold nodes to which a shortest path has been found.
    3. Label the initial node with 0, and insert it into N. 
    // Set weight or dist = 0 of the source node.
    4. Repeat Steps 5 to 7 until the destination node is in N or there are no more labelled nodes in N.
    5. Consider each node that is not in N and is connected by an edge from the newly inserted node.
    6. (a) If the node that is not in N has no label then SET the label of the 
    node = the label of the newly inserted node + the length of the edge.
    (b) Else if the node that is not in N was already labelled, then SET its new
    label = minimum (label of newly inserted vertex + length of edge, old label)
    7. Pick a node not in N that has the smallest label assigned to it and add it to N.
    */
}