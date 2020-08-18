#pragma once

class Graph2D;

class pathfinding
{
public:
	pathfinding();
	~pathfinding();

	void Update(float deltaTime);
	void Draw(bool activeState);

	Graph2D* GetGraph();
	void SetGraph(Graph2D* graph);


protected:
	Graph2D* m_graph;
private:
	int m_connectRange;
};
