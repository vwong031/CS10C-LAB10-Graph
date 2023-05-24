#include <cstring>
#include "Graph.h"

using namespace std; 

/* COMPILE COMMAND
g++ main.cpp Graph.cpp -Wall -Werror
*/

/* HOW TO READ INPUT FILE
- first line = # nodes (N)
- second line = # edges (M)
- rest of lines = labels 

N @ most maxN = 50
M @ most maxM = 200
string @ most = 15 chars (spaces not allowed)

first node in file assumed to be start vertex
the next M lines contain edges e = (u, v, c) described by source vertex, 
label u, sink vertex, label v, followed by cost c of going from vertex u
to v
*/

int main(int argc, char* argv[]) {

  if (argc != 2) {
    cerr << "Usage error: expected <executable> <input>" << endl; 
    exit(1);
  } 

  ifstream ifs(argv[1]);
  if (!ifs) {
    cerr << "Input file not found." << endl; 
    exit(1);
  }

  Graph g(ifs);
  ifs.close();
  g.bfs();
  string filename = strcat(argv[1], ".dot");
  g.output_graph(filename);
  cout << "The End." << endl; 

  return 0; 
}
