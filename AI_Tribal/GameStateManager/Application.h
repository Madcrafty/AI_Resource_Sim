#pragma once

// predclare classes
class GameStateManager;

class Application
{
public:
	Application(int windowWidth, int windowHeight);
	~Application();

	void Run();

	void Update(float deltaTime);
	void Draw();

	GameStateManager* GetGameStateManager()
	{
		return m_gameStateManager;
	}

	float GetWindowWidth() { return m_windowWidth; }
	float GetWindowHeight() { return m_windowHeight; }

protected:
private:

	int m_windowWidth;
	int m_windowHeight;

	GameStateManager* m_gameStateManager = nullptr;

};

/*
TODO:
- play state
- pause state
- high score state

when player presses "space" in the menu change state to "play"
when player presses "p" on the play state change state to "pause"
when player presses "p" on the pause state pop the pause state from the stack

CHALLANGE: see if you can update the GAME STATE MANAGER so that only the tops state is updated: all states should draw 
*/