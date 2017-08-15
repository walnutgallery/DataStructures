#include "graph.h"
#include "graph_algorithms.h"
using mystl::graph;
using mystl::breadth_first_search;

#include <chrono>
#include <climits>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <string>
#include <utility>
using namespace std;
using namespace chrono;

/// @brief create a complete graph of size n
void initialize_complete_graph(graph<int, double>& g, size_t n) {
  // add vertices
  for(size_t i = 0; i < n; ++i)
    g.insert_vertex(i);

  //add edges

  typedef graph<int, double> graph_id;
  typedef graph_id::const_vertex_iterator CVI;

  for(CVI vi1 = g.vertices_cbegin(); vi1 != g.vertices_cend(); ++vi1)
    for(CVI vi2 = g.vertices_cbegin(); vi2 != g.vertices_cend(); ++vi2)
      if((*vi1)->descriptor() != (*vi2)->descriptor())
        g.insert_edge((*vi1)->descriptor(), (*vi2)->descriptor(), double(rand()) / RAND_MAX);
}

/// @brief create a mesh of size n
void initialize_mesh_graph(graph<int, double>& g, size_t n) {
  //make n a square number
  size_t rootn = sqrt(n);
  n = rootn*rootn;

  // add vertices
  for(size_t i = 0; i < n; ++i)
    g.insert_vertex(i);

  // add edges
  for(size_t i = 0; i < n; ++i) {
    size_t x = i + 1;
    size_t y = i + rootn;

    if(x % rootn != 0)
      g.insert_edge_undirected(i, x, double(rand()) / RAND_MAX);

    if(y < n)
      g.insert_edge_undirected(i, y, double(rand()) / RAND_MAX);
  }
}

/// @brief create a mesh of size n
void initialize_random_graph(graph<int, double>& g, size_t n) {
  // add vertices
  for(size_t i = 0; i < n; ++i)
    g.insert_vertex(i);

  // add edges for connectivity
  for(size_t i=0; i < n - 1; ++i)
    g.insert_edge_undirected(i, i+1, double(rand()) / RAND_MAX);

  size_t num_edges = n*sqrt(n)/2;
  for(size_t i=0; i < num_edges; ++i) {
    size_t s = rand() % n;
    size_t t = rand() % n;
    if(s != t)
      g.insert_edge_undirected(s, t, double(rand()) / RAND_MAX);
    else
      --i;
  }
}

/// @brief create a mesh of size n
void initialize_powerlaw_graph(graph<int, double>& g, size_t n) {
}

///@brief Time functions of a graph
template<typename Initializer>
void time_graph(Initializer i, size_t n) {
  //create graph, testing insertion
  typedef graph<int, double> graph_id;
  graph_id g;
  i(g, n);


  //run BFS
  typedef graph_id::vertex_descriptor vertex_descriptor;
  unordered_map<vertex_descriptor, vertex_descriptor> parent_map;
  breadth_first_search(g, parent_map);

  //test find operations
  double sum = 0;
  for(size_t i = 0; i < g.num_edges() / 2; ++i) {
    if(rand()%2)
      sum += (*g.find_vertex(rand() % g.num_vertices()))->property();
    else {
      graph_id::edge_descriptor ed =
        make_pair(rand() % g.num_vertices(), rand() % g.num_vertices());
      graph_id::edge_iterator ei = g.find_edge(ed);
      if(ei != g.edges_end())
        sum += (*ei)->property();
    }
  }

  //test erase operations
  size_t quarter_edge = g.num_edges() / 4;
  for(size_t i = 0; i < quarter_edge; ++i) {
      graph_id::edge_iterator ei = g.find_edge(
          make_pair(rand() % g.num_vertices(), rand() % g.num_vertices())
          );
      if(ei != g.edges_end())
        g.erase_edge((*ei)->descriptor());
      else
        --i;
  }
/*   size_t quarter_nodes = g.num_vertices() / 4;
  for(size_t i = 0; i < quarter_nodes; ++i) {
      graph_id::vertex_iterator vi = g.find_vertex(rand() % g.num_vertices());
      if(vi != g.vertices_end())
        g.erase_vertex((*vi)->descriptor());
      else
        --i;
  } */

  //run BFS
  parent_map.clear();
  breadth_first_search(g, parent_map);
}

/// @brief Control timing of a single function
/// @tparam Func Function type
/// @param f Function taking a single size_t parameter
/// @param max_size Maximum size of test. For linear - 2^23 is good, for
///                 quadrati - 2^18 is probably good enough, but its up to you.
/// @param name Name of function for nice output
///
/// Essentially this function outputs timings for powers of 2 from 2 to
/// max_size. For each timing it repeats the test at least 10 times to ensure
/// a good average time.
template<typename Func>
void time_function(Func f, size_t graph_size, string name) {
  cout << setw(20) << name << ",";

  // create a clock
  high_resolution_clock::time_point start = high_resolution_clock::now();

  time_graph(f, graph_size);

  // calculate time
  high_resolution_clock::time_point stop = high_resolution_clock::now();
  duration<double> diff = duration_cast<duration<double>>(stop - start);

  cout << setw(15) << diff.count() << endl;
}

/// @brief Main function to time all your functions
int main(int argc, char** argv) {
  if(argc != 4) {
    cerr << "Error. Wrong number of arguments. Run program like:" << endl;
    cerr << "./timing.o <complete_graph_size> <mesh_graph_size> <random_graph_size>" << endl;
    cerr << "Example: ./timing.o 300 1750 800" << endl;
    exit(-1);
  }

  size_t complete_size = atoi(argv[1]);
  size_t     mesh_size = atoi(argv[2]);
  size_t   random_size = atoi(argv[3]);

  time_function(initialize_complete_graph, complete_size, "Complete");
  time_function(    initialize_mesh_graph,     mesh_size,     "Mesh");
  time_function(  initialize_random_graph,   random_size,   "Random");
}