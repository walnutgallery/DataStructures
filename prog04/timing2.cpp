////////////////////////////////////////////////////////////////////////////////
/// @brief Example timing file. Add to this file the functions you want to time
////////////////////////////////////////////////////////////////////////////////

#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "graph_algorithm.h"

using namespace std;
using namespace chrono;

/// @todo Modify timing.cpp to evaluate the various sorting algorithms on the
///       following input types:
///       - Random sequence
///       - Sorted sequence
///       - Reverse sorted sequence
///       - A few unique elements sequence

/// @brief Generate random sequence and bubble_sort
/// @param k Vector size
void bubble_sort_random_sequence_k(size_t k) {

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
		
   typedef graph_id::vertex_descriptor vertex_descriptor;
  unordered_map<vertex_descriptor, vertex_descriptor> parent_map;
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
void time_function(Func f, size_t max_size, string name) {
  cout << "Function: " << name << endl;
  cout << setw(15) << "Size" << setw(15) << "Time(sec)" << endl;

  // Loop to control input size
  for(size_t i = 2; i < max_size; i*=2) {
    cout << setw(15) << i;

    // create a clock
    high_resolution_clock::time_point start = high_resolution_clock::now();

    // loop a specific number of times to make the clock tick
    size_t num_itr = max(size_t(10), max_size / i);
    for(size_t j = 0; j < num_itr; ++j)
      f(i);

    // calculate time
    high_resolution_clock::time_point stop = high_resolution_clock::now();
    duration<double> diff = duration_cast<duration<double>>(stop - start);

    cout << setw(15) << diff.count() / num_itr << endl;
  }
}

/// @brief Main function to time all your functions
int main() {
  //time_function(bubble_sort_random_sequence_k, pow(2, 15), "Bubble Sort Random Sequence");
  time_function(slow_sort_random_sequence_k, pow(2, 17), "Slow Sort Random Sequence");
  //time_function(sort_random_sequence_k, pow(2, 23), "Sort Random Sequence");
  

  
}
