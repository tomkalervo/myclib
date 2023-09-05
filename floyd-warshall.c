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
int *path_2D_array;

typedef struct Edge {
    int v1,v2,w;
    struct Edge *next;
} Edge_t;

void    printGraph(Edge_t *head);
void    freeGraph(Edge_t *head);
int     getWeight(int u, int v);
void    setWeight(int u, int v, int w);
int     getPath(int u, int v);
void    setPath(int u, int v, int k);


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

int initArray(Edge_t *head){
    if(! (maxValueVertice > 0))
        return 0;

    vertices_2D_array = malloc(maxValueVertice*maxValueVertice*sizeof(int));
    path_2D_array = malloc(maxValueVertice*maxValueVertice*sizeof(int));

    /* Set all weights to infinity (max value of 32 bit integer)*/
    for(int i = 0; i < maxValueVertice; i++){
        for(int j = 0; j < maxValueVertice; j++){
            vertices_2D_array[i * maxValueVertice + j] = INT32_MAX;
            path_2D_array[i * maxValueVertice + j] = 0;
        }
    }
    /* Set weight/distance of (v,v) to 0*/
    for(int i = 0; i < maxValueVertice; i++){
        vertices_2D_array[i * maxValueVertice + i] = 0;
        path_2D_array[i * maxValueVertice + i] = i+1;
    }
    /* Transfer initial weights from graph*/
    Edge_t *tmp = head;
    while(tmp->next != NULL){
        if(getWeight(tmp->v1,tmp->v2) > tmp->w){
            setWeight(tmp->v1,tmp->v2,tmp->w);
            setPath(tmp->v1,tmp->v2,tmp->v1);
        }
        tmp = tmp->next;
    }

    return 1;
}

/* Runs the Floyd-Warshall algorithm on the 2D-array. 
Returns 0 (false) if a negative cycle is detected.
Otherwise return 1 if successfull execution */
int floydWarshall(){
    for(int k = 1; k <= maxValueVertice; k++)
        for(int i = 1; i <= maxValueVertice; i++)
            for(int j = 1; j <= maxValueVertice; j++){
                if(getWeight(i,k) < INT32_MAX && getWeight(k,j) < INT32_MAX){
                    int weightThroughK = getWeight(i,k) + getWeight(k,j);
                    /* Check for negative cycle */
                    if(i == j && weightThroughK < 0)
                        return 0; 
                    if(getWeight(i,j) > weightThroughK){
                        /* Found a "shorter" path from i to j through k*/
                        // printf("(%d,%d) previous w: %d, new w: %d through %d \n", i,j,getWeight(i,j), weightThroughK,k);
                        setWeight(i,j, weightThroughK);
                        setPath(i,j, getPath(k,j));
                    }
                }
            }
    return 1;
}

int getWeight(int u, int v){
    /* Subtract 1 to get 0-index */
    return vertices_2D_array[(u-1) * maxValueVertice + (v-1)];
}

void setWeight(int u, int v, int w){
    /* Subtract 1 to get 0-index */
    vertices_2D_array[(u-1) * maxValueVertice + (v-1)] = w;
    // vertices_2D_array[(v-1) * maxValueVertice + (u-1)] = w;
}

int getPath(int u, int v){
    /* Subtract 1 to get 0-index */
    return path_2D_array[(u-1) * maxValueVertice + (v-1)];
}

void setPath(int u, int v, int k){
    /* Subtract 1 to get 0-index */
    path_2D_array[(u-1) * maxValueVertice + (v-1)] = k;
}

int* path(int u, int v){
    int len = 3;
    int *path;
    int prev = getPath(u, v);
    if(prev == 0){
        int tmp[] = {0};
        path = tmp;
    }
    else{
        while(prev != u){
            len++;
            prev = getPath(u, prev);
        }
        prev = getPath(u, v);
        int tmp[len];
        tmp[0] = len;
        /* store path from v to u */
        tmp[--len] = v;
        while(len-- > 2){
            tmp[len] = getPath(u, tmp[len+1]);
        }
        tmp[1] = u;
        path = tmp;
    }

    return path;
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

/* Function for visually printing out the 2D-array with vertices and weights */
void printArray(int *array){
    printf("  |1");
    for(int i = 1; i < maxValueVertice; i++)
        printf("    |%d", i+1);
    printf("   |\n  |____");
    for(int i = 1; i < maxValueVertice; i++)
        printf("_|____");
    printf("|\n");
    for(int i = 0; i < maxValueVertice; i++){
        printf("%d", i+1);
        for(int j = 0; j < maxValueVertice; j++){
            int val = array[i*maxValueVertice + j];
            int sign = 2;
            if(val < 0){
                val = (~val)+1;
                sign = 1;
            }
            char space[sign + 1];
            space[sign] = 0;
            while(sign-- > 0)
                space[sign] = ' ';

            if(val < 100){
                if(val < 10){
                    printf(" |%d%s ", array[i*maxValueVertice + j], space);

                }
                else{
                    printf(" |%d%s", array[i*maxValueVertice + j], space);

                }
            }
            else
                printf(" |inf ");
        }
        printf("|\n");
    }
    printf("  |____");
    for(int i = 1; i < maxValueVertice; i++)
        printf("______");
    printf("|\n\n");

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

void freeArray(){
    free(vertices_2D_array);
    free(path_2D_array);
}

void showPath(){
    printf("Enter edge pair u,v to show path or type q to quit\n");
    char input[20];
    scanf("%s", input);
    while(input[0] != 'q' && input[0] != 'Q'){
        int u,v,len;
        int *p;
        int i = -1;
        /* get u */
        while(input[++i] != ',');
        char vertice_u[i];
        len = i;
        while(i-- > 0)
            vertice_u[i] = input[i];
        u = atoi(vertice_u);
        /* get v */
        int start = len + 1;
        len = strlen(input);
        char vertice_v[len-start];
        for(i = 0; i < len-start; i++)
            vertice_v[i] = input[start+i];
        v = atoi(vertice_v);
        if(u < 1 || u > maxValueVertice){
            printf("Vertice u: %d, does not exist\n", u);
            break;
        }
        if(v < 1 || v > maxValueVertice){
            printf("Vertice v: %d, does not exist\n", v);
            break;
        }
        p = path(u,v);
        len = p[0];
        if(len == 0){
            printf("No path found\n");
        }
        else{
            printf("[");
            for(int i = 1; i < len-1; i++)
                printf("%d ", p[i]);
            printf("%d]\n", p[len-1]);
        }
        memset(input, 0, sizeof(input));
        scanf("%s", input);
    }
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
    printArray(vertices_2D_array);
    floydWarshall();
    printArray(vertices_2D_array);
    showPath();
    freeArray();

    return 1;
}