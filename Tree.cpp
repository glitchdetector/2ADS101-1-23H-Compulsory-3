#include <list>
#include <iostream>
#pragma once

#include "Nodes.cpp"

class Tree {
private:
	TreeNode* root;

public:
	// Create a new tree from a root node.
	Tree(TreeNode* root) {
		this->root = root;
	}

	// The root of the tree.
	TreeNode* getRoot() {
		return root;
	}

	// Get the depth of the tree.
	// Depth is equal to the longest path from the root to a leaf.
	int getTotalDepth() {
		return root->getThickness();
	}

	// Get the number of nodes in the tree.
	int getSize() {
		return root->getSize();
	}

	std::list<TreeNode*> getAllNodes() {
		return root->getAllChildren();
	}

	// Output a list of all children to this node.
	void print(TreeNode* node) {
		int depth = node->getDepth();
		for (int i = 0; i < depth; i++) {
			std::cout << "-";
		}
		std::cout << node->value << std::endl;
		for (TreeNode* child : node->children) {
			print(child);
		}
	}

	// Output a list of all nodes in the tree.
	void print() {
		std::cout << "Total depth: " << getTotalDepth() << std::endl;
		std::cout << "Size: " << getSize() << std::endl;
		print(root);
	}

	// Export in a format to visualize it
	// Used with https://cdn.tycoon.community/tools/yed to visualize the tree
	void exportToGML() {
		for (TreeNode* node : getAllNodes()) {
			if (!node->isRoot()) {
				std::cout << "" << node->parent->value << "," << node->value << ", " << std::endl;
			}
		}
	}
};