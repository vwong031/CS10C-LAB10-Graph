#include "Graph.h"

/* SOURCES
* https://d1b10bmlvqabco.cloudfront.net/attach/ilv1r6m8xjc64o/h7ks2ibk8jg6s3/ioki9sunvh1o/graphs.pdf
* https://docs.google.com/presentation/d/0B2yW_TPa-9oiZnMxZDZ2dTc0bjg/edit
*/

Graph::Graph(ifstream &ifs) {
  int nodes;
  int edges;
  int indexOfStartingNode; 
  string nodeLabel; 
  string terminatingNodeLabel;

  ifs >> nodes; 
  ifs >> edges;

  for (int i = 0; i < nodes; ++i) {
    Vertex node;

    // Read line in input file
    ifs >> node.label;

    if (ifs.fail()) {
      cerr << "Input error while reading nodes" << endl;
      exit(1);
    }

    vertices.push_back(node);
  }

  for (int i = 0; i < edges; ++i) {
    pair<int, int> edgeDestinationAndCost;  // TODO: Must declare here so the edges aren't all copies?
    indexOfStartingNode = -1;
    edgeDestinationAndCost.first = -1;

    // Read line in input file
    ifs >> nodeLabel >> terminatingNodeLabel >> edgeDestinationAndCost.second;
    
    if (ifs.fail()) {
      cerr << "Input error while reading edges" << endl;
      exit(1);
    }
    
    for (long unsigned int i = 0; i < vertices.size(); ++i) {
      // Search for node and adjacent node in vertices vector
      // TODO: Make this more efficient (maybe with a hash table?)
      if (vertices.at(i).label == nodeLabel) {
        // Found starting node
        indexOfStartingNode = i;
      }
      if (vertices.at(i).label == terminatingNodeLabel) {
        // Found terminating node
        edgeDestinationAndCost.first = i;
      }
      if (indexOfStartingNode != -1 && edgeDestinationAndCost.first != -1) {
        // Found both node and adjacent node
        break;
      }
    }

    if (indexOfStartingNode == -1 || edgeDestinationAndCost.first == -1) {
      // Throw exception b/c node and adjacent node were not found
      cerr << "Edge includes a nonexistent node: "
           << nodeLabel << " or " << terminatingNodeLabel << endl;
      exit(1);
    }

    // Add edge to vertices vector
    // Vertex startingNode = vertices.at(indexOfStartingNode);
    Vertex& startingNode = vertices.at(indexOfStartingNode);
    startingNode.neighbors.push_back(edgeDestinationAndCost);
  }

  ifs.close();
}

/* Parker's output_graph()
   This version only outputs the breadth first traversal,
   starting at vertices.at(0) as the source node.
   If a node can't be reached from the source node, don't display it.
   */
void Graph::output_graph(const string &outputFilename){
 ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,0);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

/* Parker's visualizeTree()
   Note: "BLACK" was changed to "RED"
   because otherwise no vertices will display
   since all the vertices are black after the BFS
   */
void Graph::visualizeTree(ofstream & outFS, int n) {
  if(vertices[n].color == "RED")
    return;

  vertices[n].color = "RED";
  outFS << vertices[n].label << "[label=\"" << vertices[n].label << ", " << vertices[n].distance << "\"];" << endl;

  for(list<pair<int,int> >::const_iterator it = vertices[n].neighbors.begin(); it != vertices[n].neighbors.end(); it++) {
    outFS<< vertices[n].label <<" -> " << vertices[(*it).first].label <<";"<<endl;
    visualizeTree(outFS,(*it).first);
  }
}


void Graph::bfs() {
  queue<Vertex*> frontierQueue;
  Vertex* startNode;
  Vertex* currNode; 
  Vertex* adjNode;

  startNode = &vertices.at(0);
  startNode->color = "GRAY";
  startNode->distance = 0; 
  startNode->prev = 0; 

  frontierQueue.push(startNode); 
  
  while (!frontierQueue.empty()) {
    currNode = frontierQueue.front(); 
    frontierQueue.pop();

    for (pair<int, int> edgeDestinationAndCost : currNode->neighbors) {
      adjNode = &vertices.at(edgeDestinationAndCost.first);
      if (adjNode->color == "WHITE") {
        adjNode->color = "GRAY"; // discovered, but not expanded
        adjNode->distance = currNode->distance + 1; 
        adjNode->prev = currNode; 

        frontierQueue.push(adjNode);
      }
    }

    currNode->color = "BLACK"; // expanded
  }
}
