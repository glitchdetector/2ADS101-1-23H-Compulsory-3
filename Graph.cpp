#include <list>
#include <iostream>
#pragma once

#include "Nodes.cpp"
#include <map>

class DijkstraResult {
public:
	Vertex* origin;
	std::map<Vertex*, int> costs;

	DijkstraResult(Vertex* origin, std::map<Vertex*, int> costs) {
		this->origin = origin;
		this->costs = costs;
	}
};

class Graph {
private:
	std::list<Vertex*> vertices;
	std::list<Edge*> edges;

public:
	Graph() {}

	void addVertex(int value) {
		Vertex* v = new Vertex(value);
		vertices.push_back(v);
	}

	void addEdge(int from, int to, int weight) {
		Vertex* vFrom = findVertex(from);
		Vertex* vTo = findVertex(to);
		Edge* e = new Edge(vFrom, vTo, weight);
		edges.push_back(e);
		vFrom->adjacents.push_back(vTo);
		vTo->adjacents.push_back(vFrom);
		vFrom->incident.push_back(e);
		vTo->incident.push_back(e);
	}

	Vertex* findVertex(int value) {
		for (Vertex* v : vertices) {
			if (v->value == value) {
				return v;
			}
		}
		return nullptr;
	}
	
	// Return a list of costs to each vertex from the origin vertex
	DijkstraResult dijkstra(Vertex* vOrigin) {
		std::map<Vertex*, int> costs;
		std::map<Vertex*, bool> visited;
		for (Vertex* v : vertices) {
			visited[v] = false;
			costs[v] = INT_MAX;
		}
		costs[vOrigin] = 0;
		std::list<Vertex*> queue;
		queue.push_back(vOrigin);
		while (!queue.empty()) {
			Vertex* current = queue.front();
			queue.pop_front();
			if (!visited[current]) {
				visited[current] = true;
				for (Edge* edge : current->incident) {
					int alt = costs[current] + edge->weight;
					if (alt < costs[edge->to]) {
						costs[edge->to] = alt;
						queue.push_back(edge->to);
					}
				}
			}
		}
		return DijkstraResult(vOrigin, costs);
	}

	void print() {
		for (Vertex* v : vertices) {
			std::cout << v->value << " -> ";
			for (Vertex* adj : v->adjacents) {
				std::cout << adj->value << " ";
			}
			std::cout << std::endl;
		}
	}

	// Export in a format to visualize it
	// Used with https://cdn.tycoon.community/tools/yed to visualize the tree
	void exportToGML() {
		for (Edge* e : edges) {
			std::cout << "" << e->from->value << "," << e->to->value << "," << e->weight << "" << std::endl;
		}
	}
};

/*
Functions: 
Constructor, Access functions(return node information, 
adjacent nodes, vertices in graph, edges in graph), 
Query functions(size, isEmpty), 
insertion(both at random and as the child of a specific node) and deletion of a node, 
insertion and deletion of an edge, and one type of traversal(Depth or Breadth).
You can choose to implement adjacent nodes with an adjacency list or an adjacency matrix
*/ 