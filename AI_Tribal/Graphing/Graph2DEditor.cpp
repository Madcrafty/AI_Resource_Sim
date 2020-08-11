#include "Graph2DEditor.h"
#include "Graph2D.h"

Graph2DEditor::Graph2DEditor()
{

}
Graph2DEditor::~Graph2DEditor()
{

}

void Graph2DEditor::Update(float deltaTime)
{
	if (IsMouseButtonDown(0))
	{
		auto mousePos = GetMousePosition();

		auto newNode = m_graph->AddNode(mousePos);

		std::vector<Graph2D::Node*> nearbyNodes;
		m_graph->GetNearbyNodes(mousePos, 60, nearbyNodes);

		for (auto nearbyNode : nearbyNodes)
		{
			float dist = Vector2Distance(newNode->data, nearbyNode->data);
			m_graph->AddEdge(newNode, nearbyNode, dist);
			m_graph->AddEdge(nearbyNode, newNode, dist);
		}
	}
}
void Graph2DEditor::Draw()
{
	// Draw all connections
	for (auto node : m_graph->GetNodes())
	{
		for (auto connection : node->connections)
		{
			DrawLine(node->data.x, node->data.y, connection.to->data.x, connection.to->data.y, GRAY);
		}
	}

	// Draw all Nodes
	for (auto node : m_graph->GetNodes())
	{
		//DrawCircle(node->data.x, node->data.y, 8, LIGHTGRAY);
		//DrawCircleLines(node->data.x, node->data.y, 8, LIGHTGRAY);
	}

	// Draw a "preview" node where the mouse is

	auto mousePos = GetMousePosition();
	DrawCircleV(mousePos, 6, { 200, 200, 200, 100 });

	std::vector<Graph2D::Node*> nearbyNodes;
	m_graph->GetNearbyNodes(mousePos, 60, nearbyNodes);

	for (auto nearbyNode : nearbyNodes)
	{
		DrawLineV(mousePos, nearbyNode->data, { 130, 130, 130, 100 });
	}

}

Graph2D* Graph2DEditor::GetGraph() 
{
	return m_graph;
}
void Graph2DEditor::SetGraph(Graph2D* graph)
{
	m_graph = graph;
}