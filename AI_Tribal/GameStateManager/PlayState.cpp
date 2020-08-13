#include "PlayState.h"
#include "Application.h"
#include "Graph2D.h"
#include "Graph2DEditor.h"
#include "GameStateManager.h"

PlayState::PlayState(Application* app) : m_app(app)
{

}
PlayState::~PlayState()
{

}

void PlayState::Load()
{
    
	m_map = LoadTexture("./Sprites/big_Map_concept.png");
    m_camera.target = Vector2{ m_app->GetWindowWidth() / 2,  m_app->GetWindowHeight() * 3/2 };
    m_camera.offset = Vector2{ m_app->GetWindowWidth() / 2, m_app->GetWindowHeight() / 2 };
    m_camera.rotation = 0.0f;
    m_camera.zoom = 1.0f;
	m_graph = new Graph2D();
    int numRows = 10;
    int numCols = 17;
    float xOffset = 0;
    float yOffset = 0;
    float spacing = 50;

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
        m_graphEditor->Update(dt);

        if (IsKeyDown(KEY_RIGHT)) m_camera.target.x += 2;
        if (IsKeyDown(KEY_LEFT)) m_camera.target.x -= 2;
        if (IsKeyDown(KEY_UP)) m_camera.target.y -= 2;
        if (IsKeyDown(KEY_DOWN)) m_camera.target.y += 2;

        if (m_camera.target.x < m_camera.offset.x) m_camera.target.x = m_camera.offset.x;
        if (m_camera.target.x > m_map.width - m_camera.offset.x) m_camera.target.x = m_map.width - m_camera.offset.x;
        if (m_camera.target.y < m_camera.offset.y) m_camera.target.y = m_camera.offset.y;
        if (m_camera.target.y > m_map.height - m_camera.offset.y) m_camera.target.y = m_map.height - m_camera.offset.y;

        // Camera target follows player

        // Camera rotation controls
        //if (IsKeyDown(KEY_A)) camera.rotation--;
        //else if (IsKeyDown(KEY_S)) camera.rotation++;

        // Limit camera rotation to 80 degrees (-40 to 40)
        //if (camera.rotation > 40) camera.rotation = 40;
        //else if (camera.rotation < -40) camera.rotation = -40;

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
    }   
}
void PlayState::Draw()
{
    BeginMode2D(m_camera);
        DrawTexture(m_map, 0, 0, WHITE);
        m_graphEditor->Draw(m_app->GetGameStateManager()->GetActiveState() == this);
    EndMode2D();

}