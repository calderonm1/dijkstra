the program will run dijkstras algorithm and 
output the shortest path between a start vertex
and an end vertex

there are 2 input files, one containing all of the
vertices and another containing all of the edges

both files begin with an integer which represents
the total number of edges/vertices in the file

for the vertices, they are arranged in the format:
number xcoord ycoord
ex. 1 2755 2265 = vertex 1, position (2755, 2265)
these x and y coordinates represent pixels on the library
map which will be used to draw the path onto the map

for the edges, they are arranged in the format:
vertex1, vertex2
where each edge is simply 2 adjacent vertices