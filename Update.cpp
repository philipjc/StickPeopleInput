#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::Update(const float dt_as_seconds)
{
	if (m_NewLevelRequired)
	{
		// These calls to spawn will be moved to a new
		// LoadLevel function soon
		// Spawn Thomas and Bob
		//m_Thomas.spawn(Vector2f(0,0), GRAVITY);
		//m_Bob.spawn(Vector2f(100, 0), GRAVITY);

		// Make sure spawn is called only once
		//m_TimeRemaining = 10;
		//m_NewLevelRequired = false;

		// Load a level
		LoadLevel();

	}

	if (m_Playing)
	{
		m_Enemy.UpdateEnemy(dt_as_seconds);

		// Update Thomas
		// m_Thomas.Update(dt_as_seconds);

		// Update Bob
		m_Bob.Update(dt_as_seconds);


		// Detect collisions and see if characters have reached the goal tile
		// The second part of the if condition is only executed
		// when thomas is touching the home tile
		if (DetectCollisions(m_Thomas) && DetectCollisions(m_Bob))
		{
			// New level required
			m_NewLevelRequired = true;

			// Play the reach goal sound

		}
		else
		{
			// Run bobs collision detection
			DetectCollisions(m_Bob);
			EnemyCollision(m_Enemy);
		}

		// Let bob and thomas jump on each others heads
		if (m_Bob.GetFeet().intersects(m_Thomas.GetHead()))
		{
			m_Bob.StopFalling(m_Thomas.GetHead().top);
		}
		else if (m_Thomas.GetFeet().intersects(m_Bob.GetHead()))
		{
			m_Thomas.StopFalling(m_Bob.GetHead().top);
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
		m_LeftView.setCenter(m_Thomas.GetCenter());
		m_RightView.setCenter(m_Bob.GetCenter());
	}
	else
	{
		// Centre full screen around appropriate character
		if (m_Character1)
		{
			m_MainView.setCenter(m_Thomas.GetCenter());
		}
		else
		{
			m_MainView.setCenter(m_Bob.GetCenter());
		}
	}
}