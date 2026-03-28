#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include <set>
#include <queue>
#include <stack>
#include <iostream>

using namespace std;

class Edge;

class Vertex
{
public:
	int vertexID;
	double x, y;
	list<Edge*> Edges;
	double distance;
	bool visited;
	Edge* previous;
	
	Vertex() : vertexID(-1), x(0), y(0), distance(numeric_limits<double>::infinity()), visited(false), previous(nullptr) {}
	Vertex(int id, double xi, double yi) : vertexID(id), x(xi), y(yi), distance(numeric_limits<double>::infinity()), visited(false), previous(nullptr) {}
	~Vertex() {}
};

class Edge
{
public:
	Vertex* origin;
	Vertex* destination;
	Edge* reverse;
	double length;

	Edge() : origin(nullptr), destination(nullptr), length(0), reverse(nullptr) {}
	Edge(Vertex* Or, Vertex* Des, double len) : origin(Or), destination(Des), length(len), reverse(nullptr) {}
	~Edge() {}
};

class Graph
{
public:
	list<Vertex> Vertexs;
	vector<Vertex*> indexToVertex;
	list<Edge> Edges;
	bool directed;

	void addEdge(int u, int v, set<pair<int, int>>& existingEdges);
	void generateRandomGraph(int numVertexs, int numEdges);

	Graph(bool dir) : directed(dir) {}
	~Graph() {}
};

void dijkstra(Graph& graph, Vertex* start);
void dijkstra(Graph& graph, int start);
void printPath(Graph& graph, Vertex* end);
void printPath(Graph& graph, int end);
void aStar(Graph& graph, Vertex* start, Vertex* end);
void aStar(Graph& graph, int start, int end);