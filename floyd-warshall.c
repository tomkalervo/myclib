#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * Author: Tom Karlsson
 * Date: 2023-09-28
 * 
 * This Floyd-Warshall algorithm is inspired by the pseudocode described at wikipedia:
 * https://en.wikipedia.org/wiki/Floyd?Warshall_algorithm
 * 
 * It finds the shortest path in a directed, weighted graph. 
 * Weights can be both positive and negative, but no negative cycles may exist.
 * 
 * Graph is described using vertices(V), edges(E) with weights(W):
 * E1 = V1,V2,W
 * 
 * Input:
 * Total number of edges
 * E1
 * E2
 * ...
 * En
 * 
 * Example of input:
 * 5
 * 1,3,-2
 * 3,4,2
 * 4,2,-1
 * 2,1,4
 * 2,3,3
*/
int ROW_LENGTH = 20;
int NAME_LENGTH = 5;

int maxValueVertice = 0;
int *vertices_2D_array;
typedef struct Edge {
    int v1,v2,w;
    struct Edge *next;
} Edge_t;
void printGraph(Edge_t *head);
void freeGraph(Edge_t *head);

void* loadGraph(int edges){
    printf("Edges: %d\n", edges);
    Edge_t *head = malloc(sizeof(Edge_t));
    Edge_t *edge = NULL;
    edge = head;

    for(int i = 0; i < edges; i++){
        char input[ROW_LENGTH];
        int j = 0;
        int element = 0;

        printf("Enter %d/%d\n", i+1, edges);
        scanf("%s", input);
        int len = (int) strlen(input);

        /* Each row of input consists of 3 elements */
        while(element < 3){
            char tmp[NAME_LENGTH];
            int k = 0;

            /* First two elements is seperated by commaa */
            while((input[j] != ',') && (j < len)){
                tmp[k++] = input[j++];
            }

            /* Mark end of element*/
            if(j < NAME_LENGTH)
                tmp[j] = 0;

            /* Convert to integer */
            int val = atoi(tmp);

            /* Store value into data structure */
            switch (element)
            {
            case 0:
                /* Vertice 1 */
                edge->v1 = val;
                if(maxValueVertice < val)
                    maxValueVertice = val;
                break;
            case 1:
                /* Vertice 2 */
                edge->v2 = val;
                if(maxValueVertice < val)
                    maxValueVertice = val;
                break;
            case 2:
                /* Weight */
                edge->w = val;
                break;
            }
            j++;
            element++;
        }
        Edge_t *tmp = malloc(sizeof(Edge_t));
        edge->next = tmp;
        edge = tmp;
    }


    return head;
}

/* TODO */
int initArray(Edge_t *head){
    if(! (maxValueVertice > 0))
        return 0;
    //vertices_2D_array = malloc(edges*edges*sizeof(int));

    return 1;
}

void printGraph(Edge_t *head){
    Edge_t *tmp = head;
    printf("Printing all edges:\n");
    while(tmp->next != NULL){
        printf("Edge: (%d, %d), Weight: %d\n", tmp->v1, tmp->v2, tmp->w);
        tmp = tmp->next;
    }
    printf("All edges printed.\n");
}

void freeGraph(Edge_t *head){
    Edge_t *tmp;
    while(head->next != NULL){
        tmp = head;
        head = head->next;
        free(tmp);
    }
    printf("Graph memory allocation is freed.\n");
}

int main(){
    char input[20];
    int edges;
    printf("Number of edges? (positive integer value, max of 20 digits)\n");
    scanf("%s", input);
    edges = atoi(input);
    if(edges < 1){
        printf("Bad integer value.\n");
        return 0;
    }
    Edge_t *head;
    head = loadGraph(edges);
    printGraph(head);
    initArray(head);
    freeGraph(head);

    return 1;
}