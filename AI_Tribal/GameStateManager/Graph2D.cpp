#include "Graph2D.h"
#include "Agent.h"
#include <map>
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
Graph2D::Node* Graph2D::GetClosestNode(Vector2 position, float radius)
{
	std::vector<Graph2D::Node*> neibours;
	GetNearbyNodes(position, radius, neibours);

	if (neibours.empty())
		return nullptr;

	
	Graph2D::Node* closest = neibours[0];
	float closestDist = Vector2Distance(closest->data, position);
	for (auto& n : neibours)
	{
		float dist = Vector2Distance(n->data, position);
		if (dist < closestDist)
		{
			closestDist = dist;
			closest = n;
		}
	}

	return closest;
}
int Graph2D::GetRange()
{
	return m_connectRange;
}
std::vector<Vector2>Graph2D::GetPath(Agent* agent, Vector2 Target)
{
	
	std::vector<Vector2> path;

	// Get end node
	//auto mousePos = GetScreenToWorld2D(GetMousePosition(), *m_camera);
	auto endGNode = GetClosestNode(Target, m_connectRange);
	auto beginGNode = GetClosestNode(agent->GetPosition(), m_connectRange);

	if (beginGNode == nullptr)
	{
		return path;
	}


	//Create our temporary lists for storing nodes
	std::vector<PFNode*> openList;
	std::vector<PFNode*> closedList;

	auto IsNodeInOpenOrClosed = [&](Graph2D::Node* node) -> PFNode* {
		for (auto pfn : openList)
			if (pfn->gNode == node)
				return pfn;

		for (auto pfn : closedList)
			if (pfn->gNode == node)
				return pfn;

		return nullptr;
	};


	//Add the starting node to openList
	PFNode* pfNode = new PFNode();
	pfNode->parent = nullptr;
	pfNode->gNode = beginGNode;
	openList.push_back(pfNode);

	while (!openList.empty())
	{
		//Set the current node to the first node in the openList
		auto currentNode = openList.front();
		//Remove currentNode from openList
		openList.erase(openList.begin());
		//Add currentNode to closedList
		closedList.push_back(currentNode);

		//If the destination node was added to the closed list,
		//the shortest path has been found
		if (currentNode->gNode == endGNode)
		{
			
			while (currentNode != nullptr)
			{
				//Add the current node to the beginning of the path
				path.insert(path.begin(), currentNode->gNode->data);
				//Go to the previous node
				currentNode = currentNode->parent;
			}

			break;
		}

		//For each Edge e in currentNode's connections
		for (Graph2D::Edge e : currentNode->gNode->connections)
		{
			float gScore = currentNode->gScore + e.data;

			auto childPfNode = IsNodeInOpenOrClosed(e.to);
			if (childPfNode == nullptr)
			{
				// we should create a pfnode and add it to the stack
				childPfNode = new PFNode();
				childPfNode->parent = currentNode;
				childPfNode->gNode = e.to;
				childPfNode->gScore = gScore;
				openList.push_back(childPfNode);
			}
			else
			{
				// was it faster to get to the child node from the currentNode
				// if so, we should update its parent and gscore
				if (childPfNode->gScore > gScore)
				{
					childPfNode->gScore = gScore;
					childPfNode->parent = currentNode;
				}
			}
		}
	}

	// TODO: cleanup memory - delete all the newed PFNode * that we created
	

	return path;
}