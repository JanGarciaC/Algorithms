#include "graph.h"

#include <cstdlib>
#include <ctime>
#include <set>

////////////// PRINTPATH IMPLEMENTATION //////////////
//
//            Path Printing Function
//
// This function reconstructs and prints the shortest path
// from the start vertex to a given end vertex.
//
// It follows the chain of edges stored in each vertex's
// 'previous' pointer and uses a stack to reverse the order
// for correct output.
//
// Time Complexity:
//   - O(V) in the worst case
//
// Space Complexity:
//   - O(V) due to stack usage
//
// Notes:
//   - Requires that a pathfinding algorithm (Dijkstra/A*)
//     has been executed beforehand
//   - Prints "No path Found." if unreachable
//
/////////////////////////////////////////////////////
void printPath(Graph& graph, Vertex* end)
{
    stack<Vertex*> stack;

    Vertex* current = end;
    Vertex* start = nullptr;

    for (Vertex* v : graph.indexToVertex)
        if (v->distance == 0)
            start = v;

    if (start == nullptr)
    {
        cout << endl << "No Start Vertex found." << endl;
        return;
    }

    while (current != start)
    {
        if (current->previous == nullptr)
        {
            cout << "No path Found." << endl;
            return;
        }
        current = current->previous->origin;
        stack.push(current);
    }

    while (!stack.empty())
    {
        cout << stack.top()->vertexID << " --> ";
        stack.pop();
    }

    cout << end->vertexID << endl;
}
void printPath(Graph& graph, int end)
{
    printPath(graph, graph.indexToVertex[end]);
}

////////////// GENERATERANDOMGRAPH IMPLEMENTATION //////////////
//
//           Random Graph Generator
//
// This function generates a random graph with a given number
// of vertices and edges.
//
// Each vertex is assigned random (x, y) coordinates.
// Edges are created ensuring connectivity and avoiding duplicates.
//
// Time Complexity:
//   - O(V + E)
//
// Space Complexity:
//   - O(V + E)
//
// Notes:
//   - Ensures the graph is connected
//   - Uses Euclidean distance as edge weight
//   - Supports directed and undirected graphs
//
///////////////////////////////////////////////////////////////
void Graph::generateRandomGraph(int numVertexs, int numEdges)
{
    Vertexs.clear();
    Edges.clear();
    indexToVertex.clear();

    if (numVertexs <= 0 || numEdges <= 0) return;

    srand(time(nullptr));

    for (int i = 0; i < numVertexs; i++)
    {
        double x = rand() % 1000;
        double y = rand() % 1000;

        Vertexs.emplace_back(i, x, y);
        indexToVertex.push_back(&Vertexs.back());
    }

    set<pair<int, int>> existingEdges;

    for (int i = 1; i < numVertexs; i++)
    {
        int j = rand() % i;
        addEdge(i, j, existingEdges);
    }

    int currentEdges = existingEdges.size();
    if (!directed)
        currentEdges /= 2;

    while (currentEdges < numEdges)
    {
        int u = rand() % numVertexs;
        int v = rand() % numVertexs;

        if (u == v) continue;

        if (existingEdges.count({ u, v }) == 0)
        {
            addEdge(u, v, existingEdges);
            currentEdges++;
        }
    }
}

void Graph::addEdge(int u, int v, set<pair<int, int>>& existingEdges)
{
    Vertex* vertU = indexToVertex[u];
    Vertex* vertV = indexToVertex[v];

    double dx = vertU->x - vertV->x;
    double dy = vertU->y - vertV->y;
    double dist = sqrt(dx * dx + dy * dy);

    existingEdges.insert({ u, v });

    if (directed)
    {
        Edges.emplace_back(vertU, vertV, dist);
        vertU->Edges.push_back(&Edges.back());
    }
    else
    {
        Edges.emplace_back(vertU, vertV, dist);
        Edge* e1 = &Edges.back();

        Edges.emplace_back(vertV, vertU, dist);
        Edge* e2 = &Edges.back();

        e1->reverse = e2;
        e2->reverse = e1;

        vertU->Edges.push_back(e1);
        vertV->Edges.push_back(e2);

        existingEdges.insert({ v, u });
    }
}


////////////// DIJKSTRA IMPLEMENTATION //////////////
//
//            Dijkstra Shortest Path Algorithm
//
// This function computes the shortest paths from a start
// vertex to all other vertices in the graph using a
// priority queue (min-heap).
//
// Time Complexity:
//   - O((V + E) log V)
//
// Space Complexity:
//   - O(V)
//
// Notes:
//   - Works only with non-negative edge weights
//   - Stores path using 'previous' pointer in vertices
//
////////////////////////////////////////////////////
struct ver
{
    Vertex* v;
    double value;
};

struct comparator
{
    bool operator()(ver& v1, ver& v2) { return v1.value > v2.value; }
};

void dijkstra(Graph& graph, Vertex* start) 
{
    priority_queue<ver, vector<ver>, comparator> queue;

    for (Vertex* v : graph.indexToVertex)
    {
        v->distance = numeric_limits<double>::infinity();
        v->visited = false;
        v->previous = nullptr;
    }

    start->distance = 0;

    ver first; first.v = start; first.value = 0;
    queue.push(first);

    Vertex* current;

    while (!queue.empty())
    {
        current = queue.top().v;
        queue.pop();

        if (current->visited)
            continue;

        current->visited = true;

        for (auto e : current->Edges)
        {
            if (e->destination->distance > current->distance + e->length)
            {
                e->destination->distance = current->distance + e->length;
                ver v; 
                v.v = e->destination; 
                v.value = e->destination->distance;
                queue.push(v);

                e->destination->previous = e;
            }
        }
    }
}
void dijkstra(Graph& graph, int start)
{
    dijkstra(graph, graph.indexToVertex[start]);
}

////////////// ASTAR IMPLEMENTATION //////////////
//
//            A* Pathfinding Algorithm
//
// This function computes the shortest path between a start
// and an end vertex using the A* algorithm.
//
// It combines actual distance (g) and heuristic (h) to
// guide the search efficiently.
//
// Time Complexity:
//   - O((V + E) log V)
//
// Space Complexity:
//   - O(V)
//
// Notes:
//   - Faster than Dijkstra in many cases
//   - Uses Euclidean heuristic
//   - Stops early when goal is reached
//
//////////////////////////////////////////////////
double heuristic(Vertex* a, Vertex* b)
{
    double dx = a->x - b->x;
    double dy = a->y - b->y;
    return sqrt(dx * dx + dy * dy);
}

struct aStarVertex
{
    Vertex* v;
    double value;
};

struct CompareAStar
{
    bool operator()(aStarVertex a, aStarVertex b)
    {
        return a.value > b.value;
    }
};

void aStar(Graph& graph, Vertex* start, Vertex* end)
{
    for (auto& v : graph.Vertexs)
    {
        v.distance = numeric_limits<double>::infinity();
        v.visited = false;
        v.previous = nullptr;
    }

    priority_queue<aStarVertex, vector<aStarVertex>, CompareAStar> queue;

    start->distance = 0;
    aStarVertex v;
    v.v = start; 
    v.value = heuristic(start, end);
    queue.push(v);

    while (!queue.empty())
    {
        Vertex* current = queue.top().v;
        queue.pop();

        if (current->visited)
            continue;

        current->visited = true;

        if (current == end)
            return;

        for (Edge* e : current->Edges)
        {
            Vertex* neighbor = e->destination;

            double totalDistance = current->distance + e->length;

            if (totalDistance < neighbor->distance)
            {
                neighbor->distance = totalDistance;
                neighbor->previous = e;

                double f = totalDistance + heuristic(neighbor, end);
                aStarVertex v;
                v.v = neighbor; v.value = f;
                queue.push(v);
            }
        }
    }
}

void aStar(Graph& graph, int start, int end)
{
    aStar(graph, graph.indexToVertex[start], graph.indexToVertex[end]);
}