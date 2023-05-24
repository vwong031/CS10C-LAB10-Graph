#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <list>
#include <map>
#include <climits>
using namespace std; 

class Vertex {
  public:
    /* Individual vertex's label */
    string label;
    /* Distance the vertex is from the start vertex. 
    Updated during BFS traversal */
    int distance;
    string color; 
    Vertex *prev;
    /* An STL list of STL pairs. For each int,int pair, the integer values
    are the neighboring vertex's position in the graph object's vector 
    vertices & the cost of the edge of that neighbor */
    list<pair<int, int> > neighbors; 
    /* A pointer to the previous vertex in BFS traversal. Initially prev 
    is null for all vertices */

    Vertex() : label(""), distance(INT_MAX), color("WHITE"), prev(0) {}
    ~Vertex() {}
};

#endif
