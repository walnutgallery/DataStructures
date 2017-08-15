#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <vector>
#include <iostream>
#include <fstream>
#include <string>


using namespace std;
namespace mystl {
/// @brief Graph ADT using ADJ List and vectors
/// @ingroup MySTL
/// @tparam vertex Property
/// @tparam EdgeProperty
///
/// Assumes the following: There is always enough memory for allocations (not a
/// good assumption, just good enough for our purposes); Functions not
/// well-defined on an empty container will exhibit undefined behavior.
////////////////////////////////////////////////////////////////////////////////
template<typename VertexProperty, typename EdgeProperty>
  class graph {

    //you have to forward declare these so you can use them in the public
    //section, when they are defined in the private section below. Essentially,
    //the compiler needs to know they exist in order to use them before the
    //definition of them.
    class vertex;
    class edge;

    public:
    ////////////////////////////////////////////////////////////////////////////
    /// @name Types
    /// @{
      
      typedef size_t vertex_descriptor; //<unique vertex identifier

      typedef pair<size_t, size_t> edge_descriptor; //<unique edge identifier
                                                    //<represents pair of vertex
                                                    //<descriptors

      //vertex container should contain "vertex*" or shared_ptr<vertex>
      typedef typename vector<vertex*>::iterator vertex_iterator; //<vertex iterators
      typedef typename vector<vertex*>::const_iterator const_vertex_iterator;//<const vertex iterators

      //edge container should contain "edge*" or shared_ptr<edge>
      typedef typename vector<edge*>::iterator edge_iterator; //<edge iterators
      typedef typename vector<edge*>::const_iterator const_edge_iterator;

      //adjacent edge container should contain "edge*" or shared_ptr<edge>
      typedef typename vector<edge*>::iterator adj_edge_iterator; //<adjacency list iterators
      typedef typename vector<edge*>::const_iterator const_adj_edge_iterator;//<const adjacency list iterators

       /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructors
    /// @{

    /// @brief Constructor
      graph(){}
	/// @brief Destructor
      ~graph(){}

      graph(const graph&) = delete;
      graph& operator=(const graph&) = delete;

      ///required graph operations
    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Iterators
    /// @{

    /// @return Iterator to vertex beginning
      vertex_iterator vertices_begin(){
		  return verts.begin();
	  }
	/// @return Iterator to vertex constant beginning
      const_vertex_iterator vertices_cbegin() const{
		  return verts.cbegin();
	  }
	/// @return Iterator to vertex end
      vertex_iterator vertices_end(){
		  return verts.end();
	  }
	/// @return Iterator to vertex constant end
      const_vertex_iterator vertices_cend() const{
		  return verts.cend();
	  }
	/// @return Iterator to edge beginning
      edge_iterator edges_begin(){
		  return edges.begin();
	  }
	/// @return Iterator to edges constant beginning
      const_edge_iterator edges_cbegin() const{
		return edges.cbegin();
	  }
	/// @return Iterator to edge ending
      edge_iterator edges_end(){
		return edges.end();
	  }
	/// @return Iterator to edge constant ending
	  const_edge_iterator edges_cend() const{
		return edges.cend();
	  }
    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
      /// @name Capacity
    /// @{
	/// @return Number of Vertices
      size_t num_vertices() const{
		  return num_vert; 
	  }
	  /// @return Number of Edges
      size_t num_edges() const{
		  return num_edge;
	  }
	  /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Element Access
    /// @{

    /// @param desc vertex descriptor
    /// @return iterator at the description
    ///
    /// If \c desc matches an element in the container, the function will return a
    /// reference to its mapped value.
    ///
    /// If \c k is not found in the container, the function should insert a new
    /// element with that key and return a reference to its mapped value
    /// (constructed through default construction)
      vertex_iterator find_vertex(vertex_descriptor desc){
		return verts.begin()+desc;
	  }
      const_vertex_iterator find_vertex(vertex_descriptor desc) const{
			return verts.begin()+desc;
		
	  }
      edge_iterator find_edge(edge_descriptor desc){
		return verts[desc.first]->fin_edge(desc);
	  }
      const_edge_iterator find_edge(edge_descriptor desc) const{
		return verts[desc.first]->fin_edge(desc);
	  }
    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
	  

      //modifiers
	  //pushes back the created vertex and returns the descriptor
      vertex_descriptor insert_vertex(const VertexProperty& v){
		vertex* created = new vertex(vert_desc, v);
		verts.push_back(created);
		num_vert++;
		vert_desc++;
		return vert_desc-1;
	  }
	  //pushes back the created edge into the adjacency list and returns the descriptor and increments edges by 1.
      edge_descriptor insert_edge(vertex_descriptor start, vertex_descriptor end, const EdgeProperty& weight){
		edge* created=new edge(start, end, weight);
		edges.push_back(created);
		verts[start]->add_edge_out(created);
		verts[end]->add_edge_in(created);
		num_edge++;
		edge_desc++;
		return make_pair(start,end);
	  }
	  //pushes back the created edge into the adjacency list and increments the edges by 2.
      void insert_edge_undirected(vertex_descriptor start, vertex_descriptor end, const EdgeProperty &weight){
		edge* to=new edge(start, end, weight);
		edge* from=new edge(end, start, weight);
		edges.push_back(to);
		edges.push_back(from);
		verts[start]->add_edge_out(to);
		verts[start]->add_edge_in(from);
		verts[end]->add_edge_out(from);
		verts[end]->add_edge_in(to);
		num_edge=num_edge+2;
		vert_desc+=2;
	  }
	  //erases the vertex by calling nullout, null in and make empty
      void erase_vertex(vertex_descriptor a){
	    size_t total=0;
		if(a<=vert_desc){
		if(verts[a]->descriptor()!=777777){
	    total+=verts[a]->null_out();
		total+=verts[a]->null_in();
		
		verts[a]->make_empty();
		num_vert--;
		num_edge-=total;
		}
		}
	  }
	  //calls remove edge.
      void erase_edge(edge_descriptor removed){
	  if(removed.first<=vert_desc && removed.second<=vert_desc){
	  if(verts[removed.first]->descriptor()!=777777){
		verts[removed.first]->remove_edge(removed);
		num_edge--;}}
	  }
	  //takes in a string of the file name and populates the graph based on the contents of the file.
	  void file_input(string name){
			ifstream input(name);
			cout<<name<<endl;
			size_t num_verts=0;
			size_t num_edges=0;
			input>>num_verts>>num_edges;
			string temp_verts;
			cout<<num_verts<<num_edges<<endl;
			
			for(size_t i=0; i<num_verts;i++){
				input>>temp_verts;
				cout<<temp_verts<<endl;
				insert_vertex(temp_verts);
			}
			
			 vertex_descriptor a, b;
			EdgeProperty c;
			for(size_t i=0; i<num_edges;i++){
				input>>a>>b>>c;
				cout<<a<<" "<<b<<" "<<c<<endl;
				insert_edge(a,b,c);
			}  
		
	  }
	  //clears the graph's data.
      void clear(){
		verts.clear();
		edges.clear();
		num_vert=num_edge=vert_desc=edge_desc=0;
	  }

      template<typename V, typename E>
        friend istream& operator>>(istream&, graph<V, E>&);
      template<typename V, typename E>
        friend ostream& operator<<(ostream&, const graph<V, E>&);

    private:
	size_t num_vert = 0;
	size_t num_edge = 0;
	vector <vertex*> verts;
	vector <edge*> edges;
	size_t vert_desc=0;
	size_t edge_desc=0;

      ///required internal classes
		
      class vertex {
        public:
          ///required constructors/destructors
		  //constructor for initalizing data.
          vertex(vertex_descriptor vd, const VertexProperty& v){
			  vdesc=vd;
			  prop=v;
		  }

          ///required vertex operations

          //iterators
		  //iterator to the beginning of the adjacency list
          adj_edge_iterator begin(){
			  return adj_list.begin();
		  }
		  //const iterator to the beginning of the adjacency list
          const_adj_edge_iterator cbegin() const{
			  return adj_list.cbegin();
		  }
		  //iterator to the end of the adjacency list
          adj_edge_iterator end(){
			  return adj_list.end();
		  }
		  //const iterator to the end of the adjacency list
          const_adj_edge_iterator cend() const{
			  return adj_list.cend();
		  }

          //accessors
		  //returns the descriptor
          const vertex_descriptor descriptor() const{
			  return vdesc;
		  }
		  //returns the property
          VertexProperty& property(){
			  return prop;
		  }
		  //returns the const property
          const VertexProperty& property() const{
			  return property;
		  }
		  

		  //returns the iterator to find edge.  searches through the adjacency list for the correct edge.
		  edge_iterator fin_edge(edge_descriptor desc){
			for(size_t i=0;i<adj_list.size();i++){
				if(adj_list[i]->target()==desc.second)
					return adj_list.begin()+i;
			}
			return adj_list.begin();
		  }

		 //modifiers
		 //pushes it into the adjacency list.
		  void add_edge_out(edge *a){
			   adj_list.push_back(a);  	
		  }
		  //pushse back into the incoming adjacency list.
		  void add_edge_in(edge *a){
			   incoming_adj.push_back(a);
		  }
		  //sets all the edges to a nonexistent edge
		  size_t null_out(){
		  size_t total=0;
		  size_t size=adj_list.size();
				for(size_t i=0;i<size;i++){
					if(adj_list[i]->source()!=777777){
						incoming_adj[i]->make_empty();
						total++;
						}
				} 
			incoming_adj.clear();
			return total;
			
		  }
		  //sets all the edges to a nonexistent edge
		  size_t null_in(){
		  size_t total=0;		
		  size_t size=incoming_adj.size();
			 	for(size_t i=0; i<size;i++){
					if(incoming_adj[i]->source()!=777777){
						incoming_adj[i]->make_empty();
						total++;
						}
				} 
			incoming_adj.clear();
			return total;
		  }
		  //finds the edge and sets it to a nonexistent edge
		  void remove_edge(edge_descriptor removing){
			vertex_descriptor targ=removing.second;
			for(size_t i=0; i<adj_list.size();i++){
				if(adj_list[i]->target()==targ && targ!=777777){
					adj_list[i]->make_empty();
					}		
			}
		  }
		  //sets the description to 777777 and clears the adjacency lists
		  void make_empty(){
		  vdesc=777777;
		  prop=VertexProperty();
		  adj_list.clear();
		  incoming_adj.clear();
		  
		  }
		 
		
		 
        private:
		vertex_descriptor vdesc;
		VertexProperty prop;
		vector<edge*> adj_list;
		vector<edge*> incoming_adj;
      };

      class edge {
        public:
          ///required constructors/destructors
		  //initalizes data.
		   edge(vertex_descriptor start, vertex_descriptor end, const EdgeProperty& weight){
				sour=start;
				targ=end;
				value=weight;
		   }
		  
		  
          ///required edge operations

          //accessors
		  //returns the source
          const vertex_descriptor source() const{
			  return sour;
		  }
		  //returns the target
          const vertex_descriptor target() const{
			  return targ;
		  }
		  //returns the source target pair
          const edge_descriptor descriptor() const{
			  return std::make_pair(sour,targ);
		  }
          EdgeProperty& property(){
			  return value;
		  }
          const EdgeProperty& property() const{
			  return value;
		  }
		  //creats an edge between descriptor 9999999 and 9999999 which are nonexistent and sets the
		  //value to the default value.
		  void make_empty(){ 
		  sour=999999;
		  targ=999999;
		  value=EdgeProperty();
		  }

        private:
		vertex_descriptor sour;
		vertex_descriptor targ;
		EdgeProperty value;
      };

  };

}

#endif
