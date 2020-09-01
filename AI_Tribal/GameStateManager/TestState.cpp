
#include "TestState.h"
#include "Application.h"
#include "raylib.h"
#include "GameStateManager.h"
#include "GameObject.h"
#include "Graph2D.h"
#include "Agent.h"

#include "WanderBehaviour.h"

#include <iostream>
#include "ResourceNode.h"

TestState::TestState(Application* app) : m_app(app)
{

}
TestState::~TestState()
{

}

void TestState::Load()
{
	std::cout << "LOADING TEST" << std::endl;
	//m_player = new GameObject();
	//m_player->SetPostion({ m_app->GetWindowWidth() / 2, m_app->GetWindowHeight() / 2 });
	//m_player->SetFriction(1);
    // Loading Graph
    m_graph = new Graph2D();
    int numRows = 17;
    int numCols = 17;
    float xOffset = 0;
    float yOffset = 0;
    float spacing = 64;

    for (size_t y = 0; y < numRows; y++)
    {
        for (size_t x = 0; x < numCols; x++)
        {
            m_graph->AddNode({
                x * spacing + xOffset,
                y * spacing + yOffset
                });
        }
    }

    for (auto node : m_graph->GetNodes())
    {
        std::vector<Graph2D::Node*> nearbyNodes;
        m_graph->GetNearbyNodes(node, m_graph->GetRange(), nearbyNodes);

        for (auto connectedNode : nearbyNodes)
        {
            float dist = Vector2Distance(node->data, connectedNode->data);
            m_graph->AddEdge(node, connectedNode, dist);
            m_graph->AddEdge(connectedNode, node, dist);
        }
    }
    //m_graphEditor = new Graph2DEditor();
    //m_graphEditor->SetGraph(m_graph);


    // load some berries
    for (int i = 0; i < 10; i++)
    {
        float xPos = rand() % (int)m_app->GetWindowWidth();
        float yPos = rand() % (int)m_app->GetWindowHeight();
        SpawnBerry(Vector2{xPos, yPos});
    }

    // load agents
    m_agent1 = new Agent(this);
    m_agent1->AddBehaviour(new WanderBehaviour);
    m_agent1->SetPlayer();
    m_agent1->SetPostion({100,100});
    m_agent2 = new Agent(this);
    m_agent2->AddBehaviour(new WanderBehaviour);
}
void TestState::Unload()
{
	std::cout << "UNLOADING TEST" << std::endl;

    for (auto berry : m_berries)
        delete berry;
    m_berries.clear();

	//delete m_player;
	//m_player = nullptr;
}

void TestState::Update(float dt)
{
	auto gms = m_app->GetGameStateManager();
	if (IsKeyPressed(KEY_P))
	{
		if (gms->GetActiveState() == this)
		{
			m_app->GetGameStateManager()->PushState("Pause");
		}
	}
	if (gms->GetActiveState() == this)
	{
		//if (IsKeyDown(KEY_W)) m_player->ApplyForce({ 0, -100 });
		//if (IsKeyDown(KEY_A)) m_player->ApplyForce({ -100, 0 });
		//if (IsKeyDown(KEY_S)) m_player->ApplyForce({ 0, 100 });
		//if (IsKeyDown(KEY_D)) m_player->ApplyForce({ 100, 0 });
		//m_player->ApplyForce({ 10, 0 });
		//m_player->Update(dt);
	}

    for (auto berry : m_berries)
    {
        berry->Update(dt);
    }

    m_agent1->Update(dt);
    if (m_agent1->GetPosition().x < 0)
    {
        m_agent1->SetPostion({ 0, m_agent1->GetPosition().y });
    }
    if (m_agent1->GetPosition().x > m_app->GetWindowWidth())
    {
        m_agent1->SetPostion({ m_app->GetWindowWidth(), m_agent1->GetPosition().y });
    }
    if (m_agent1->GetPosition().y < 0)
    {
        m_agent1->SetPostion({ m_agent1->GetPosition().x, 0 });
    }
    if (m_agent1->GetPosition().y > m_app->GetWindowHeight())
    {
        m_agent1->SetPostion({ m_agent1->GetPosition().x, m_app->GetWindowHeight() });
    }
    m_agent2->Update(dt);
    if (m_agent2->GetPosition().x < 0)
    {
        m_agent2->SetPostion({ 0, m_agent2->GetPosition().y });
    }
    if (m_agent2->GetPosition().x > m_app->GetWindowWidth())
    {
        m_agent2->SetPostion({ m_app->GetWindowWidth(), m_agent2->GetPosition().y });
    }
    if (m_agent2->GetPosition().y < 0)
    {
        m_agent2->SetPostion({ m_agent2->GetPosition().x, 0 });
    }
    if (m_agent2->GetPosition().y > m_app->GetWindowHeight())
    {
        m_agent2->SetPostion({ m_agent2->GetPosition().x, m_app->GetWindowHeight() });
    }
}
void TestState::Draw()
{
    for (auto berry : m_berries)
        berry->Draw();

	m_agent1->Draw();
    m_agent2->Draw();

    // Score Board;
    std::string s = std::to_string(m_agent1->GetScore());
    char const* a1_score = s.c_str();
    DrawText(a1_score, 0, 0, 32, RED);
    s = std::to_string(m_agent2->GetScore());
    char const* a2_score = s.c_str();
    DrawText(a2_score, m_app->GetWindowWidth() - 64,0 , 32, RED);
}

std::vector<ResourceNode *>& TestState::GetBerries()
{
    return m_berries;
}

Agent* TestState::GetAgent(int num)
{
    if (num == 0)
    {
        return m_agent1;
    }
    else if (num == 1)
    {
        return m_agent2;
    }
    else
    {
        std::cout << "Agent null" << std::endl;
        return nullptr;
    }
}

void TestState::SpawnBerry(Vector2 pos)
{
    auto berry = new ResourceNode(this);
    berry->SetPostion(pos);

    m_berries.push_back(berry);

}