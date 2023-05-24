#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <queue>
#include <string> 
#include <fstream>
#include <cstdlib>
#include <cstdio>

#include "Vertex.h"

class Graph {
  public:
    /* Reads the graph input file & instantiates a graph object */
    Graph(ifstream &ifs); 
    /* Outputs graph object to a .dot file, then makes a system call that 
    calls dotty on this file. In the dotty file, each node should include 
    vertex label and its distance value */
    void output_graph(const string &filename);
    void visualizeTree(ofstream&, int); 
    /* Breadth First Search. Via a BFS traversal, this function should
    assign each individual vertex's distance to the number of hops that
    the vertex is from the start vertex. 
    You can find the pseudo code for BFS on: 
    https://d1b10bmlvqabco.cloudfront.net/attach/ilv1r6m8xjc64o/h7ks2ibk8jg6s3/ioki9sunvh1o/graphs.pdf */
    void bfs();
  private:
    /* Vector containing all of the vertices in the graph.
    The start vertex is in the first position in the vector */
    vector<Vertex> vertices; 
};

#endif
