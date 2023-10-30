// 2ADS101_Graph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>

#include "Nodes.cpp"
#include "Tree.cpp"
#include "Graph.cpp"


#pragma region Tree
void TreeTest() {
	std::cout << "= TREE TEST =" << std::endl;
	
	TreeNode* root = new TreeNode(nullptr, 1);
	
	Tree tree(root);

	TreeNode* branch_1 = root->add(2);
	TreeNode* branch_2 = root->add(3);

	branch_1->add(4); 
	branch_1->add(5);
	branch_2->add(6)->add(8);
	branch_2->add(7);
	
	tree.print();

	// tree.exportToGML(); // Used to generate the visuals, see function for details
}
#pragma endregion

#pragma region Graph
void GraphTest() {
	std::cout << "= GRAPH TEST =" << std::endl;
	
	Graph graph;
	
	graph.addVertex(1);
	graph.addVertex(2);
	graph.addVertex(3);
	graph.addVertex(4);
	graph.addVertex(5);
	graph.addVertex(6);
	graph.addVertex(7);
	graph.addVertex(8); 
	graph.addVertex(9);
	graph.addVertex(10);

	graph.addEdge(1, 2, 1);
	graph.addEdge(2, 4, 2);
	graph.addEdge(3, 4, 1);
	graph.addEdge(1, 3, 2);
	graph.addEdge(4, 5, 3);
	graph.addEdge(5, 6, 12);
	graph.addEdge(6, 7, 5);
	graph.addEdge(7, 8, 8);
	graph.addEdge(8, 9, 5);
	graph.addEdge(9, 10, 2);
	graph.addEdge(10, 3, 25);
	graph.addEdge(1, 8, 9);
	graph.addEdge(4, 10, 13);

	graph.print();

	DijkstraResult dijkstra = graph.dijkstra(graph.findVertex(1));
	std::cout << "Dijkstra from " << dijkstra.origin->value << std::endl;
	while (!dijkstra.costs.empty()) {
		std::cout << "Cost to " << dijkstra.costs.begin()->first->value << " is " << dijkstra.costs.begin()->second << std::endl;
		dijkstra.costs.erase(dijkstra.costs.begin());
	}

	// graph.exportToGML(); // Used to generate the visuals, see function for details
}
#pragma endregion

int main()
{
	TreeTest();
	GraphTest();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
