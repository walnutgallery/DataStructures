#include "graph.h"
#include <iostream>
#include <string>
using namespace std;
using namespace mystl;
int main(){
/* 	graph<int,int> test;
	int a=test.insert_vertex(5);
	cout<<test.num_vertices()<<" "<<a<<" "<<test.num_edges()<<endl;
	a=test.insert_vertex(5);
	cout<<test.num_vertices()<<" "<<a<<" "<<test.num_edges()<<endl;
	pair<size_t, size_t> par=test.insert_edge(0,1,5);
	cout<<par.first<<par.second<<endl;
	cout<<test.num_vertices()<<" "<<a<<" "<<test.num_edges()<<endl;
	test.erase_edge(make_pair(0,1));
	cout<<test.num_vertices()<<" "<<" "<<test.num_edges(); */
	graph<string,size_t> test;
	//test.file_input("specs.txt");
	//cout<<"hello";
/* 		 	ifstream input("specs.txt");
			size_t num_vert, num_edge;
			input>>num_vert>>num_edge;
			string temp_verts;
			size_t ab;
			for(size_t i=0; i<num_vert;i++){
				input>>temp_verts;
			
				ab=test.insert_vertex(temp_verts);
					cout<<temp_verts<<" "<<ab<<endl;
			}
			
				 size_t a, b;
			size_t c;
			for(size_t i=0; i<num_edge;i++){
				input>>a>>b>>c;
				cout<<a<<b<<c<<endl;
				test.insert_edge(a,b,c);
			}  
	cout<<test.num_vertices()<<test.num_edges();  */
	test.file_input("specs.txt");
 return 1;
}