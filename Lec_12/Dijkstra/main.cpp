#include "WGraphDijkstra.h"
void main()
{
	WGraphDijkstra g;
	g.load("graph_sp.txt");
	//printf("Dijkstra의 최단경로 탐색을 위한 그래프:graph_sp.txt\n);
	//g.display();
	printf("Shortest path By Dijkstra Algorithm\n");
	g.ShortestPath(0);
}