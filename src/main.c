// The main function for the program to find the shortest path between cities.
//
//Written by He Tan, March 2022
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "graph.h"
#include <stdbool.h>

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
    dijkstra(source_node, dist, graph);

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
    // AdjListNode *startingNode = graph->array[source_node].head, *adjNode = graph->array[startingNode->next->graph_node_id].head, *ptr = startingNode, ptr2;
    // int flag, noPathToSource = 0, pathDistance = 0, id = 0;
    int flag;
    // bool duplicate = false;
    
    
    Minheap *h = create_heap(graph->N);
    
    for (size_t i = 0; i < graph->N; i++) 
    {
        dist[i] = INFINITY;
        MinHeapNode *n = new_min_heap_node(i, dist[i]);
        (flag = insert_heap(h, n)) ? puts("Insertion was successful") : puts("Heap is full");
        h->pos[i] = i;
    } 
    h->array[source_node] = new_min_heap_node(source_node, dist[source_node]);
    h->pos[0] = source_node;
    dist[source_node] = 0;
    decreaseKey(h, source_node, dist[source_node]);
    
    while (h->cur_size > 0)
    {
        MinHeapNode *n = findmin(h);
        (flag = delete_heap(h)) ? puts("Deletion was successful") : puts("Heap is empty");

        int node = n->graph_node_id;

        AdjListNode *adjNode = graph->array[node].head;

        while (adjNode != NULL)
        {
            int idx = adjNode->graph_node_id;
            if (dist[node] != INFINITY )
            {
                if (h->pos[idx] < h->cur_size)
                {
                    if (adjNode->weight + dist[node] < dist[idx])
                    {
                        dist[idx] = dist[node] + adjNode->next->weight;
                        decreaseKey(h, idx, dist[idx]);
                    }
                    
                }
                
            }
            adjNode = adjNode->next;
        }
    }
    
    //Hyffsat försök men tror det är fel
    // while (adjNode != NULL)
    // {   
    //     if (startingNode->next != NULL)
    //     {
    //         for (size_t i = 1; i <= h->cur_size; i++)
    //             if (adjNode->graph_node_id == (id = h->array[i]->graph_node_id)) duplicate = true;
    //         if (duplicate == false)
    //         {
    //             // pathDistance = startingNode->next->weight;
    //             n = new_min_heap_node(adjNode->graph_node_id, pathDistance += graph->array[ptr->graph_node_id].head->next->weight);
    //             (flag = insert_heap(h, n)) ? puts("Insertion was successful") : puts("Heap is full");
    //             ptr = graph->array[ptr->next->graph_node_id].head;
    //             if (adjNode->next != NULL) adjNode = graph->array[adjNode->next->graph_node_id].head;
    //         }
    //         else if (adjNode->next != NULL)
    //         {
    //             adjNode = graph->array[adjNode->next->graph_node_id].head;
    //             duplicate = false;
    //         }
    //         else if (startingNode->next != NULL)
    //         {
    //             startingNode = startingNode->next;
    //             if (startingNode->next != NULL)
    //             {
    //                 ptr = startingNode->next;
    //                 if (ptr->next != NULL) adjNode = graph->array[ptr->next->graph_node_id].head;
    //             }
    //         }
    //     }
    //     else
    //     {
    //         for (size_t i = 0; i < graph->N; i++)
    //         {   
    //             for (size_t j = 1; j <= h->cur_size; j++)
    //                 if (i == (id = h->array[j]->graph_node_id)) duplicate = true;
    //             if (duplicate == false)
    //             {
    //                 n = new_min_heap_node(graph->array[i].head->graph_node_id, noPathToSource);
    //                 (flag = insert_heap(h, n)) ? puts("Insertion was successful") : puts("Heap is full");
    //             }
    //             duplicate = false;
    //         }
    //         break;
    //     }   
    // }

    //      n = findmin(h);
    //     (flag = delete_heap(h)) ? puts("Deletion was successful") : puts("Heap is empty");
    //     while (ptr != NULL)
    //     {
    //         ptr = graph->array[n->graph_node_id].head->next;
    //         // decreaseKey(h, ptr->graph_node_id, ptr->weight);
    //         dist[ptr->graph_node_id] = ptr->weight;
    //         ptr = ptr->next;
    //     }
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

   // Testa detta
//    unsigned int heap[n][2];
//     unsigned int S[n];
    
//     for(int i = 0; i < n; i++) {
//         distance[i][0] = 0xFFFFFFFF;
//         distance[i][1] = 0xFFFFFFFF;
//         heap[i][0] = 0xFFFFFFFF;
//         heap[i][1] = i;
//         S[i] = 0;
//     }
//     distance[s][0] = 0;
//     distance[s][1] = 0;
//     heap[s][0] = 0;
    
//     unsigned int heap_size = n;
    
//     build_min_heap(heap, heap_size);
    
//     while(heap_size > 0) {
//         unsigned int u = -1;
//         unsigned int min_val = heap_extract_min(heap, heap_size, &u);

//         if (u == -1) {
//            printf("unexpected case\n");
//             break;
//         }        
//         S[u] = 1; 
//         heap_size--;
//         if(min_val == (unsigned int)-1) {
//             break;
//         } else {
//             for (unsigned int v = 0; v < n; v++) {
//                 unsigned int w = adj_matrix[u][v];
//                 if (w != (unsigned int)-1 && S[v] != 1) {
//                     relax(heap, distance, u, v, w, heap_size);
//                 }
//             }
//         }
//     }
}