#include "PlayState.h"
#include "Application.h"
#include "SeekBehaviour.h"
#include "FleeBehaviour.h"
#include "WanderBehaviour.h"
#include "Graph2D.h"
#include "Graph2DEditor.h"
#include "GameStateManager.h"
#include "pathfinding.h"

PlayState::PlayState(Application* app) : m_app(app)
{

}
PlayState::~PlayState()
{

}

void PlayState::Load()
{

    /*Agent* testPlayer = new Agent();
    testPlayer->AddBehaviour(new pathfinding());
    testPlayer->SetPosition({ 250,900 });
    m_player.push_back(testPlayer);*/

    // Loading Agents
    for (size_t i = 0; i < m_initalPlayerAgents; i++)
    {
        Agent* player = new Agent();
        player->AddBehaviour(new WanderBehaviour());
        player->SetPlayer();
        player->AddBehaviour(new pathfinding());
        player->SetPosition({ 250,900 });
        m_player.push_back(player);
    }

    for (size_t i = 0; i < m_initalEnemyAgents; i++)
    {
        Agent* player = new Agent();
        player->AddBehaviour(new WanderBehaviour());
        player->SetPosition({ 900,250 });
        m_enemy.push_back(player);
    }

    // Loading Map
	m_map = LoadTexture("./Sprites/big_Map_concept.png");
    m_worldBorder = { (float)m_map.width, (float)m_map.height };

    // Loading Camera
    m_camera.target = Vector2{ m_app->GetWindowWidth() / 2, m_app->GetWindowHeight() * 3/2 };
    m_camera.offset = Vector2{ m_app->GetWindowWidth() / 2, m_app->GetWindowHeight() / 2 };
    m_camera.rotation = 0.0f;
    m_camera.zoom = 1.0f;

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
    m_graphEditor = new Graph2DEditor();
    m_graphEditor->SetGraph(m_graph);
}
void PlayState::Unload()
{

}

void PlayState::Update(float dt)
{
    auto gms = m_app->GetGameStateManager();
	if (IsKeyPressed(KEY_P))
	{
		if (gms->GetActiveState() == this )
		{
			m_app->GetGameStateManager()->PushState("Pause");
		}	
	}
    if (gms->GetActiveState() == this)
    {
        //m_graphEditor->Update(dt);

        
        // Updating all agents
        for (auto agent : m_player) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !agent->FindBehaviour("SeekBehaviour"))
            {
                //agent->AddBehaviour(new SeekBehaviour(&m_camera));
            }
            if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && !agent->FindBehaviour("FleeBehaviour"))
            {
                agent->AddBehaviour(new FleeBehaviour(&m_camera));
            }
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && agent->FindBehaviour("FollowPathBehaviour"))
            {
                pathfinding* behaviour = (pathfinding*)agent->GetBehaviour("FollowPathBehaviour");
                std::vector<Vector2> path = m_graph->GetPath(agent, GetScreenToWorld2D(GetMousePosition(), m_camera));
                behaviour->SetPath(path);
            }
            agent->Update(dt);
            if (agent->GetPosition().x > m_worldBorder.x) agent->SetPosition({ m_worldBorder.x, agent->GetPosition().y });
            if (agent->GetPosition().x < 0) agent->SetPosition({ 0, agent->GetPosition().y });
            if (agent->GetPosition().y > m_worldBorder.y) agent->SetPosition({ agent->GetPosition().x, m_worldBorder.y });
            if (agent->GetPosition().y < 0) agent->SetPosition({ agent->GetPosition().x, 0 });
        }
        for (auto agent : m_enemy)
        {
            agent->Update(dt);
            if (agent->GetPosition().x > m_worldBorder.x) agent->SetPosition({ m_worldBorder.x, agent->GetPosition().y });
            if (agent->GetPosition().x < 0) agent->SetPosition({ 0, agent->GetPosition().y });
            if (agent->GetPosition().y > m_worldBorder.y) agent->SetPosition({ agent->GetPosition().x, m_worldBorder.y });
            if (agent->GetPosition().y < 0) agent->SetPosition({ agent->GetPosition().x, 0 });
        }

        // Camera moves with arrow keys
        if (IsKeyDown(KEY_RIGHT)) m_camera.target.x += 2;
        if (IsKeyDown(KEY_LEFT)) m_camera.target.x -= 2;
        if (IsKeyDown(KEY_UP)) m_camera.target.y -= 2;
        if (IsKeyDown(KEY_DOWN)) m_camera.target.y += 2;

        if (m_camera.target.x < m_camera.offset.x) m_camera.target.x = m_camera.offset.x;
        if (m_camera.target.x > m_map.width - m_camera.offset.x) m_camera.target.x = m_map.width - m_camera.offset.x;
        if (m_camera.target.y < m_camera.offset.y) m_camera.target.y = m_camera.offset.y;
        if (m_camera.target.y > m_map.height - m_camera.offset.y) m_camera.target.y = m_map.height - m_camera.offset.y;

        // Camera zoom controls
        m_camera.zoom += ((float)GetMouseWheelMove() * 0.05f);

        if (m_camera.zoom > 3.0f) m_camera.zoom = 3.0f;
        else if (m_camera.zoom < 0.1f) m_camera.zoom = 0.1f;

        // Camera reset (zoom and rotation)
        if (IsKeyPressed(KEY_R))
        {
            m_camera.zoom = 1.0f;
            m_camera.rotation = 0.0f;
        }
        // Debug View Toggle
        if (IsKeyPressed(KEY_D) && IsKeyPressed(KEY_B) && IsKeyPressed(KEY_M) && IsKeyPressed(KEY_BACKSPACE))
        {
            m_debugMode = !m_debugMode;
        }
    }   
}
void PlayState::Draw()
{
    BeginMode2D(m_camera);
        DrawTexture(m_map, 0, 0, WHITE);
        for (auto agent : m_player)agent->Draw();
        for (auto agent : m_enemy)agent->Draw();
        if (m_debugMode)
        {
            m_graphEditor->Draw(m_app->GetGameStateManager()->GetActiveState() == this);
        }       
    EndMode2D();

}

//Camera2D PlayState::GetCamera2D()
//{
//    return m_camera;
//}