#include<iostream>
#include<vector>
#include<iomanip>
#include "Graph.hpp"

int main()
{
	AdjListGraph<int> graph;
	graph.addNode(1);
	graph.addNode(10);
	graph.addEdge(10, 1);

	graph.addNode(2);
	graph.addEdge(2, 10);

	graph.deleteEdge(10, 1);
	graph.deleteNode(1);

	//Used breakpoints and watch/locals tab to ensure this worked properly
	return 0;
}