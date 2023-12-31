#include "Engine.h"

void Engine::LoadLevel()
{
	m_GameRunning = false;

	// Delete the previously allocated memory
	for (int i = 0; i < m_Lm.GetLevelSize().y; ++i)
	{
		delete[] m_ArrayLevel[i];

	}
	delete[] m_ArrayLevel;

	// Load the next 2d array with the map for the level
	// And repopulate the vertex array as well
	m_ArrayLevel = m_Lm.NextLevel(m_VaLevel);

	// How long is this new time limit
	m_TimeRemaining = m_Lm.GetTimeLimit();

	// Spawn Knight
	m_Knight.Spawn(m_Lm.GetStartPosition());

	m_Enemy.SpawnEnemy(m_Lm.GetEnemyStartPosition(), static_cast<int>(m_Gravity));

	// Make sure this code isn't run again
	m_NewLevelRequired = false;
}
