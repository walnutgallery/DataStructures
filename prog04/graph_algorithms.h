#ifndef _GRAPH_ALGORITHMS_H_
#define _GRAPH_ALGORITHMS_H_

namespace mystl {

//Here is an example list of the basic algorithms we will work with in class. I
//will add more as we go to the online version of this file.
//
//In general this is what the following template parameters are:
// - Graph - type of graph, literally your adjacency list graph
// - ParentMap - associative container between vertex_descriptors and parent
//               vertex_descriptors. This is a representation of the free
//               trees/forests created by these search methods
// - DistanceMap - associative container between vertex_descriptors and
//                 EdgeProperties. This represents the summation of the path
//                 weights to the vertex itself.
//
//Assume EdgeProperties can be added and compared with less than/less than or
//equal.
//
//Remember that every extra algorithm you implement can earn you bonus.

template<typename Graph, typename ParentMap>
  void depth_first_search(const Graph& g, ParentMap& p);

  
  //takes in a graph and parentmap. 
  //populates parentmap with child-parent key value pairs
template<typename Graph, typename ParentMap>
  void breadth_first_search(const Graph& g, ParentMap& p){
		vector<bool> visitedYet;
		for(int i=0;i<g.num_of_vertices();i++){
			visited[i]=false;
		}
		size_t start=0;
		while(!visted.empty){
			list<size_t> visited.push_back(start);
			for(auto i=g.find_vertex(start)->begin();i!=g.find_vertex(start)->end;i++){
			if(visitedYet[i->property()]=false){
				p[i->property]=start;
				visitedYet[i->property()]=true;
				visited.push_back(i->property());
				}
				}
				start++;
		}
		
  }
  
  
  

template<typename Graph, typename ParentMap>
  void mst_prim_jarniks(const Graph& g, ParentMap& p);

template<typename Graph, typename ParentMap>
  void mst_kruskals(const Graph& g, ParentMap& p);

template<typename Graph, typename ParentMap, typename DistanceMap>
  void sssp_dijkstras(const Graph& g, ParentMap& p, DistanceMap& d);

template<typename Graph, typename ParentMap, typename DistanceMap>
  void sssp_bellman_ford(const Graph& g, ParentMap& p, DistanceMap& d);

}

#endif