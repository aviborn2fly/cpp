/* circuit_check.cpp :Defines the entry point for the console application.
*
*		** Author - Avinash **
*		** id - 2018PEV5137 **
*
*/
//Instructions(Please read)--
//
// A C++ Program which takes input from a file containing nodes and connection of a circuit and checks if it is a sequential or combinational circuit.
//
// Please include boost library in path before compiling this file.
//
//Please enter the file name (if in same directory) or COMPLETE PATH of the file INCLUDING filename when asked while running the program 
//
//This program works correctly for number of nodes between 0 to 9 ( total should be less than 10 ), so please specify the nodes in the text file accordingly.
// Nodes greater than 9 however are possible with small modification but requires some more time to implement.
//
//and total number of lines are bound by the number of elements defined in the array, here 20 lines are defined,
// so for more lines than 20 present in the input file the program ignores rest of the lines.
// 
//THANKYOU
//
//


using namespace std;


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <list>
#include <limits>
#include <utility>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/visitors.hpp>

using namespace boost;

struct cycle_detector : public dfs_visitor<>
{
  cycle_detector(bool& has_cycle) 
    : m_has_cycle(has_cycle) { }

  template <class Edge, class Graph>
  void back_edge(Edge, Graph&) { m_has_cycle = true; }
protected:
  bool& m_has_cycle;
};


int main()
{
	string line, values[20];
	int inputcount = 0, checkcount = 0, intvalues[20][3], nodes, count=0;
	char filename[50];

	cout<<"Enter the filename to be opened (including path if not in same directory): \n";
	cin>>filename;
	
	cout << "\nPerforming file operations... \n";

	ifstream myfile(filename);
	if (myfile.is_open())
	{
		cout<<"\nContents of the file are: \n";
		while ( getline (myfile, line))
		{
			
			values[checkcount] = line;
			cout << values[checkcount] << '\n';
			
			checkcount++;
			inputcount++;

			if (checkcount > 19)
			{
				cout << "\n More than 20 lines are not allowed in the text file \n";
				break;
			}

			
		}
		cout<<"Here first line defines number of nodes and rest of the lines defines edge connectivity. \n";
		myfile.close();

	}

	else
	{
	cout << "Unable to open file";
		cout << "\n\nPlease close the window\n\n";
	cin.get();
	system("pause");

	return 0;
	}


	cout << "Converting file data objects into integer data type for processing... \n";

	//Type conversion from string to integer

	char intermediate2[2];
	strcpy(intermediate2, values[0].c_str());

	nodes = intermediate2[0] - '0';

	//nodes = total number of nodes in the graph, which is given in the first line of the input file.

	for (int i = 1; i < inputcount; i++) {
 
		char intermediate[4];
		strcpy(intermediate, values[i].c_str());
		
		intvalues[i-1][0] = intermediate[0] - '0';
		intvalues[i-1][1] = intermediate[2] - '0';

	}
	
	/*
	*
	*	values are stored in 2d array variable intvalues[inputcount][j].
	*	ie, values defining edge directed from intvalues[inputcount][0] to intvalues[inputcount][1] in the array
	*
	*
	*/

	

	cout << "\nType conversion successful.\n";
	
	cout << "Creating Graph... \n";



	if (inputcount < 1)
	{
		cout << "No edge is defined in the file.\n";
		cout << "\n\nPlease close the window\n\n";
	cin.get();
	system("pause");

	return 0;
	}

	else {

 typedef adjacency_list< listS, vecS, directedS > digraph;

   // instantiate a digraph object with vertices equal to value of variable nodes
   digraph g(nodes);
   
   // add some edges
   int kk=inputcount-1;
   for(int i=0; i<kk; i++){
   	
   	add_edge(intvalues[i][0], intvalues[i][1], g);
   	
   }
   cout << "Performing Cycle Check... \n\n\n";
 
   
  // are there any cycles in the graph?
  
  {
    bool has_cycle = false;
    cycle_detector vis(has_cycle);
    depth_first_search(g, visitor(vis));
    if(has_cycle)
      cout<<"This is a Sequential circuit";
    else
      cout<<"This is a Combinational circuit";
  }
  cout << endl;

	}

	


	//Ending
	cout << "\n\nPlease close the window\n\n";
	cin.get();
	system("pause");

	return 0;
}