#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class LevelManager
{
private:
	Vector2i m_LevelSize;
	Vector2f m_StartPosition;
	float m_TimeModifier = 1;
	float m_BaseTimeLimit = 0;
	int m_CurrentLevel = 0;
	const int num_Level = 4;

	Vector2f m_EnemyStartPosition = Vector2f(500, 0);

public:

	const int tile_size = 50;
	const int verts_in_quad = 4;

	float GetTimeLimit() const;

	Vector2f GetStartPosition() const;

	Vector2f GetEnemyStartPosition() const;

	int** NextLevel(VertexArray& r_va_level);

	Vector2i GetLevelSize() const;

	int GetCurrentLevel() const;

};