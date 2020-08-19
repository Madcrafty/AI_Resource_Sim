#pragma once

#include "Graph.h"
#include "raymath.h"

class Agent;

class Graph2D : public Graph<Vector2, float>
{
public:
	struct PFNode
	{
		Graph2D::Node* gNode;
		float gScore;
		PFNode* parent;
	};
	Graph2D();
	virtual ~Graph2D();

	void GetNearbyNodes(Node* targetNode, float radius, std::vector<Graph2D::Node*>& out_nodes);
	void GetNearbyNodes(Vector2 position, float radius, std::vector<Graph2D::Node*>& out_nodes);

	Node* GetClosestNode(Vector2 position, float radius);
	std::vector<Graph2D::Node*> GetPath(Agent* agent);

	int GetRange();

private:
	int m_connectRange = 91;
};