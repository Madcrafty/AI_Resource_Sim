#include "Graph2D.h"

Graph2D::Graph2D()
{

}
Graph2D::~Graph2D()
{

}

void Graph2D::GetNearbyNodes(Node* targetNode, float radius, std::vector<Graph2D::Node*>& out_nodes)
{
	for (auto node : m_nodes)
	{
		float dist = Vector2Distance(node->data, targetNode->data);
		if (dist < radius && node != targetNode)
		{
			out_nodes.push_back(node);
		}
	}
}
void Graph2D::GetNearbyNodes(Vector2 position, float radius, std::vector<Graph2D::Node*>& out_nodes)
{
	for (auto node : m_nodes)
	{
		float dist = Vector2Distance(node->data, position);
		if (dist < radius)
		{
			out_nodes.push_back(node);
		}
	}
}