/*
dijkstra.c
Mateo Calderon
Library Research Project
04/14/23
the program will run dijkstras algorithm and 
output the shortest path between a start vertex
and an end vertex
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define INF 99999999 //very large number to represent infinity

struct vertex {
    int id; //index of vertex in vertices array
    int x; //x coordinate
    int y; //y coordinate
};

struct edge {
    struct vertex v1; //vertex 1
    struct vertex v2; //vertex 2
    int weight; //weight of the edge
};

//set the weight of edge struct
void setWeight(struct edge *e1){
    //calculate and set the weight of an edge to the distance between its x and y coordinates
    e1->weight = abs(e1->v1.x - e1->v2.x + e1->v1.y - e1->v2.y);
}

//if an edge exists between 2 vertices, return the index of that edge
int isAdjacent(struct vertex v1, struct vertex v2, struct edge edges[], int num_edges){
    //iterate through all edges 
    for (int i = 0; i < num_edges; ++i){
        //if the edge contains the two vertices that means they are adjacent
        if ((edges[i].v1.id == v1.id && edges[i].v2.id == v2.id) || 
            (edges[i].v1.id == v2.id && edges[i].v2.id == v1.id))
            //return the index of that edge
            return i;
    }
    //no edge was found, return -1
    return -1;
}

//find the index of the vertex w/ minimum distance value
int minDistance(int dist[], int visited[], int num_vertices){
    int min = INF;
    int minIndex;

    //iterate through all vertices: if unvisited and the distance from the start is the smallest, set that as the minimum
    for (int i = 0; i < num_vertices; ++i){
        if ((visited[i] == 0) && (dist[i] < min)){
            min = dist[i];
            minIndex = i;
            break;
        }
    }
    return minIndex;
}

//print distances of each vertex to source
void printSolution(int dist[], int num_vertices){
    printf("Vertex  Distance from Source\n");

    //iterate through all vertices and print their distance from the source vertex
    for (int i = 0; i < num_vertices; ++i){
        printf("%d \t %d\n", i, dist[i]);
    }
}

//print path from destination to source
void printPath(struct vertex end, int prev[], struct vertex vertices[]){
    int currV = end.id; //begin from the final vertex in the path
    int parentIndex = prev[currV]; //get the index of the vertex prior to the current vertex in the path
    printf("(end) ");

    //iterate while there still exists a parent vertex; if not that means we have reached the end of the path (start vertex will not have a parent)
    while (parentIndex != -1){
        printf("%d <- ", currV);
        currV = parentIndex; //set the current vertex to the parent
        parentIndex = prev[currV]; //set the parent vertex to the parent of the parent
    }
    printf("%d (start)\n", currV);
}

//create a txt file containing the coordinates of each vertex in the path
void generateCoordinates(struct vertex end, int prev[], int num_vertices, struct vertex vertices[]){
    const char *filename = "coordinates.txt"; //create output file
    FILE *file = fopen(filename, "w"); //open output file for writing

    int currV = end.id; //begin from the final vertex in the path
    int parentIndex = prev[currV]; //get the index of the vertex prior to the current vertex in the path

    //iterate while there still exists a parent vertex; if not that means we have reached the end of the path (start vertex will not have a parent)
    while (parentIndex != -1){
        //find the vertex in the vertices array
        for (int i = 0; i < num_vertices; ++i){
            if (currV == vertices[i].id){
                //add vertex coordinates to output file
                fprintf(file, "%d,%d\n", vertices[i].x, vertices[i].y);
            }
        }
        currV = parentIndex; //set the current vertex to the parent
        parentIndex = prev[currV]; //set the parent vertex to the parent of the parent
    }
    fprintf(file, "%d,%d\n", vertices[currV].x, vertices[currV].y); //add the final vertex
}

//dijkstra algorithm
void dijkstra(struct vertex start, struct vertex end, struct vertex vertices[], struct edge edges[], int num_vertices, int num_edges){
    int visited[num_vertices]; //whether a vertex has been processed or not
    int dist[num_vertices]; //distance a vertex is from the source vertex
    int prev[num_vertices]; //parent vertex of vertex[i], used for outputting the path

    //initialize all values
    for (int i = 0; i < num_vertices; ++i){
        visited[i] = 0; //all vertices are initially unvisited
        dist[i] = INF; //all vertices are intially an unknown (infinite) distance from source
        prev[i] = -1; //all vertices do not yet have a parent
    }

    dist[start.id] = 0; //start vertex is 0 distance from itself

    //for all vertices except for the start vertex
    for (int i = 0; i < num_vertices - 1; ++i){
        int currV = minDistance(dist, visited, num_vertices); //current vertex will always be the closest unvisited vertex
        int currE; //current edge 
        visited[currV] = 1; //mark current vertex as visited as we process it

        for (int j = 0; j < num_vertices; ++j){
            //check if vertices[j] is adjacent to the current vertex, if so retrieve the index of the edge
            currE = isAdjacent(vertices[currV], vertices[j], edges, num_edges);

            //if vertex hasn't been visited, there exists an edges between the vertices, and the sum would be less than the current distance
            if ((visited[j] == 0) && (currE != -1) && (dist[currV] + (edges[currE]).weight < dist[j])){
                dist[j] = dist[currV] + edges[currE].weight; //set the distance to the distance of the previous vertex from the start + weight of the edge between current vertex and previous
                prev[j] = currV; //set the previous vertex of the current vertex (for outputting the path)
            }
        }
    }
    //print the distances from each vertex from the start vertex
    //printSolution(dist, num_vertices);

    //print the path from the start vertex to the end vertex
    //printPath(end, prev, vertices);

    //create the output file
    generateCoordinates(end, prev, num_vertices, vertices);
}

int main(int argc, char* argv[]){
    int num_vertices; //number of vertices
    int num_edges; //number of edges
    int start = atoi(argv[3]); //start vertex
    int end = atoi(argv[4]); //end vertex

    char* filename_V = argv[1]; //argument 1 from command line, txt file containing vertices
    char* filename_E = argv[2]; //argument 2 from command line, txt file containing edges

    //declare and open files containing vertex and edge information
    FILE *file_V, *file_E;
    file_V = fopen(filename_V, "r");
    file_E = fopen(filename_E, "r");

    //initally scan file to obtain number of edges and vertices
    fscanf(file_V, "%d", &num_vertices);
    fscanf(file_E, "%d", &num_edges);

    //declare arrays for storing vertices and edges
    struct vertex vertices[num_vertices];
    struct edge edges[num_edges];

    //scan file info to array (vertices)
    for (int i = 0; i < num_vertices; ++i){
        fscanf(file_V, "%d %d %d", &vertices[i].id, &vertices[i].x, &vertices[i].y);
    }

    //scan file info to array (edges)
    for (int i = 0; i < num_edges; ++i){
        int v1; 
        int v2;
        fscanf(file_E, "%d %d", &v1, &v2);
        edges[i].v1 = vertices[v1];
        edges[i].v2 = vertices[v2];
    }

    //close files
    fclose(file_V);
    fclose(file_E);
    
    //calculate and set the weight of all edges prior to performing algorithm
    for (int i = 0; i < num_edges; ++i){
        setWeight(&edges[i]);
    }

    //run dijkstras algorithm
    dijkstra(vertices[start], vertices[end], vertices, edges, num_vertices, num_edges);
    
    return 0;
}