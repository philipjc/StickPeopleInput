#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::Update(const float dt_as_seconds)
{
	if (m_NewLevelRequired)
	{
		LoadLevel();
	}

	if (m_GameRunning)
	{
		m_Enemy.UpdateEnemy(dt_as_seconds);

		// Update Knight
		m_Knight.Update(dt_as_seconds);

		// Detect collisions and see if characters have reached the goal tile
		// The second part of the if condition is only executed
		// when thomas is touching the home tile
		if (DetectCollisions(m_Knight))
		{
			// New level required
			m_NewLevelRequired = true;

			// Play the reach goal sound
		}
		else
		{
			// Run bobs collision detection
			DetectCollisions(m_Knight);
			EnemyCollision(m_Knight, m_Enemy);
		}

		// Count down the time the player has left
		m_TimeRemaining -= dt_as_seconds;

		// Have Thomas and Bob run out of time?
		if (m_TimeRemaining <= 0)
		{
			m_NewLevelRequired = true;
		}

	}// End if playing

	// Set the appropriate view around the appropriate character
	if (m_SplitScreen)
	{
		m_RightView.setCenter(m_Knight.GetCenter());
	}
	else
	{
		m_MainView.setCenter(m_Knight.GetCenter());
	}
}