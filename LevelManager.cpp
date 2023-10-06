#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <fstream>
#include "LevelManager.h"

using namespace sf;
using namespace std;

int** LevelManager::NextLevel(VertexArray& r_va_level)
{
	m_LevelSize.x = 0;
	m_LevelSize.y = 0;

	// Get the next level
	m_CurrentLevel++;
	if (m_CurrentLevel > num_Level)
	{
		m_CurrentLevel = 1;
		m_TimeModifier -= .1f;
	}

	// Load the appropriate level from a text file
	string levelToLoad;
	switch (m_CurrentLevel)
	{

	case 1:
		levelToLoad = "levels/level1.txt";
		m_StartPosition.x = 100;
		m_StartPosition.y = 100;
		m_BaseTimeLimit = 30.0f;
		break;

	case 2:
		levelToLoad = "levels/level2.txt";
		m_StartPosition.x = 100;
		m_StartPosition.y = 3600;
		m_BaseTimeLimit = 100.0f;
		break;

	case 3:
		levelToLoad = "levels/level3.txt";
		m_StartPosition.x = 1250;
		m_StartPosition.y = 0;
		m_BaseTimeLimit = 30.0f;
		break;

	case 4:
		levelToLoad = "levels/level4.txt";
		m_StartPosition.x = 50;
		m_StartPosition.y = 200;
		m_BaseTimeLimit = 50.0f;
		break;
	default: ;
	}

	ifstream input_file(levelToLoad);
	string s;

	// Count the number of rows in the file
	while (getline(input_file, s))
	{
		++m_LevelSize.y;
	}

	// Store the length of the rows
	m_LevelSize.x = static_cast<int>(s.length());

	// Go back to the start of the file
	input_file.clear();
	input_file.seekg(0, ios::beg);

	// Prepare the 2d array to hold the int values from the file
	const auto arrayLevel = new int* [m_LevelSize.y];
	for (int i = 0; i < m_LevelSize.y; ++i)
	{
		// Add a new array into each array element
		arrayLevel[i] = new int[m_LevelSize.x];
	}

	// Loop through the file and store all the values in the 2d array
	string row;
	int y = 0;
	while (input_file >> row)
	{
		for (int x = 0; x < row.length(); x++) {

			const char val = row[x];
			arrayLevel[y][x] = atoi(&val);
		}

		y++;
	}

	// close the file
	input_file.close();

	// What type of primitive are we using?
	r_va_level.setPrimitiveType(Quads);

	// Set the size of the vertex array
	r_va_level.resize(m_LevelSize.x * m_LevelSize.y * verts_in_quad);

	// Start at the beginning of the vertex array
	int currentVertex = 0;

	for (int x = 0; x < m_LevelSize.x; x++)
	{
		for (int y = 0; y < m_LevelSize.y; y++)
		{
			// Position each vertex in the current quad
			r_va_level[currentVertex + 0].position =
				Vector2f(static_cast<float>(x * tile_size), static_cast<float>(y * tile_size));

			r_va_level[currentVertex + 1].position =
				Vector2f(static_cast<float>(x * tile_size + tile_size), static_cast<float>(y * tile_size));

			r_va_level[currentVertex + 2].position =
				Vector2f(static_cast<float>(x * tile_size + tile_size), static_cast<float>(y * tile_size + tile_size));

			r_va_level[currentVertex + 3].position =
				Vector2f(static_cast<float>(x * tile_size), static_cast<float>(y * tile_size + tile_size));

			// Which tile from the sprite sheet should we use
			const int verticalOffset = arrayLevel[y][x] * tile_size;

			r_va_level[currentVertex + 0].texCoords =
				Vector2f(0, static_cast<float>(0 + verticalOffset));

			r_va_level[currentVertex + 1].texCoords =
				Vector2f(static_cast<float>(tile_size), static_cast<float>(0 + verticalOffset));

			r_va_level[currentVertex + 2].texCoords =
				Vector2f(static_cast<float>(tile_size), static_cast<float>(tile_size + verticalOffset));

			r_va_level[currentVertex + 3].texCoords =
				Vector2f(0, static_cast<float>(tile_size + verticalOffset));

			// Position ready for the next four vertices
			currentVertex = currentVertex + verts_in_quad;
		}
	}

	return arrayLevel;
}

Vector2i LevelManager::GetLevelSize() const
{
	return m_LevelSize;
}

int LevelManager::GetCurrentLevel() const
{
	return m_CurrentLevel;
}

float LevelManager::GetTimeLimit() const
{
	return m_BaseTimeLimit * m_TimeModifier;

}
Vector2f LevelManager::GetStartPosition() const
{
	return m_StartPosition;
}

Vector2f LevelManager::GetEnemyStartPosition() const
{
	return m_EnemyStartPosition;
}
