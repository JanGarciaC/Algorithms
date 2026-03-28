///////////////////////////////////////////////////////////
//
//                 TEST PROGRAM
//
// This program demonstrates the usage of several algorithms
// and functions defined in different header files.
//
// Available Files and Functions: 
// · sorting.h:
//   - CreateRandom
//   - RandomShuffle
//   - CheckIfSorted
//   - BubbleSort
//   - QuickSort
//	 - InsertionSort
//	 - MergeSort
//	 - BogoSort
// 
// · graph.h: --> includes class Vertex, class Edge and class Graph
//	 - CreateRandomGraph
//	 - printPath
//	 - dijkstra
//	 - aStar
//
// Each function is documented in detail in its corresponding
// header file.
//
// Note:
//   - This project is a work in progress.
//   - Additional functions and modules will be added in the future.
//
///////////////////////////////////////////////////////////

#include <iostream>
#include <chrono>

#include "sorting.h"
#include "graph.h"

int main()
{
	// false --> not directed graph
	Graph graph(false);

	// Generates a random graph with 1000 vertices and 5000 Edges (x2 since graph is not directed)
	graph.generateRandomGraph(1000, 5000);

	// Applies dijkstra algorithm to calculate path from start to all other vertices
	dijkstra(graph, 0);

	// Shows path from start to vertice 500
	printPath(graph, 500);

	// Applies aStar to get shortest path from 750 to 50
	aStar(graph, 750, 50);
	
	// Shows path from start to vertice 50
	printPath(graph, 50);
}