#pragma once

class Graph2D;

class Graph2DEditor
{
public:
	Graph2DEditor();
	~Graph2DEditor();

	void Update(float deltaTime);
	void Draw(bool activeState);

	Graph2D* GetGraph();
	void SetGraph(Graph2D* graph);


protected:
	Graph2D* m_graph;
private:
	int m_connectRange;
};
