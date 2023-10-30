#include <list>
#pragma once

#pragma region Tree

class TreeNode {
public:
	int value;
	std::list<TreeNode*> children;
	TreeNode* parent;

	// Create a new node.
	TreeNode(TreeNode* parent, int value) {
		this->value = value;
		this->parent = parent;
		if (parent != nullptr) {
			parent->addChild(this);
		}
	}

	// Add a new child with the specified value.
	TreeNode* add(int value) {
		return new TreeNode(this, value);
	}

	// Adds a child to this node.
	void addChild(TreeNode* child) {
		children.push_back(child);
	}

	// Removes a child from this node.
	void removeChild(TreeNode* child) {
		children.remove(child);
	}

	// Removes the node from the tree.
	void remove() {
		if (parent != nullptr) {
			parent->removeChild(this);
		}
	}

	// Checks if the node has no children.
	bool isLeaf() {
		return children.size() == 0;
	}

	// Checks if the node has no parent.
	bool isRoot() {
		return parent == nullptr;
	}

	// Get the depth of the node.
	// Depth is equal to parent connections to the rot.
	int getDepth() {
		if (isRoot()) {
			return 0;
		}
		return parent->getDepth() + 1;
	}

	// Get the number of children of this node.
	int getSize() {
		int count = children.size();
		for (TreeNode* child : children) {
			count += child->getSize();
		}
		return count;
	}

	// Set a new parent.
	void setParent(TreeNode* node) {
		if (parent != nullptr) {
			parent->removeChild(this);
		}
		parent = node;
		if (parent != nullptr) {
			parent->addChild(this);
		}
	}

	std::list<TreeNode*> getAllChildren() {
		std::list<TreeNode*> nodes;
		nodes.push_back(this);
		for (TreeNode* child : children) {
			std::list<TreeNode*> childNodes = child->getAllChildren();
			nodes.insert(nodes.end(), childNodes.begin(), childNodes.end());
		}
		return nodes;
	}

	// Get the thickness from the node.
	// Thickness is equal to the longest path from the node to a leaf.
	int getThickness() {
		if (isLeaf()) {
			return 0;
		}
		int max = 0;
		for (TreeNode* child : children) {
			int level = child->getThickness();
			if (level > max) {
				max = level;
			}
		}
		return max + 1;
	}
};

#pragma endregion

#pragma region Graph

class Vertex;
class Edge;

class Edge {
public:
	Vertex* from;
	Vertex* to;
	int weight;
	Edge(Vertex* from, Vertex* to, int weight) {
		this->from = from;
		this->to = to;
		this->weight = weight;
	}
};

class Vertex {
public:
	int value;
	std::list<Vertex*> adjacents;
	std::list<Edge*> incident;
	Vertex(int value) {
		this->value = value;
	}
};

#pragma endregion