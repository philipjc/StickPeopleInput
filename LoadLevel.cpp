#include "Engine.h"

void Engine::LoadLevel()
{
	m_Playing = false;

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

	// Spawn Thomas and Bob
	m_Thomas.Spawn(m_Lm.GetStartPosition(), static_cast<int>(gravity));
	m_Bob.Spawn(m_Lm.GetStartPosition(), static_cast<int>(gravity));

	m_Enemy.SpawnEnemy(m_Lm.GetEnemyStartPosition(), static_cast<int>(gravity));

	// Make sure this code isn't run again
	m_NewLevelRequired = false;
}