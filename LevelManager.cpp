#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TextureCache.h"
#include <sstream>
#include <fstream>
#include "LevelManager.h"

using namespace sf;
using namespace std;

int** LevelManager::NextLevel(VertexArray& r_va_level)
{
	m_level_size_.x = 0;
	m_level_size_.y = 0;

	// Get the next level
	m_current_level_++;
	if (m_current_level_ > num_levels_)
	{
		m_current_level_ = 1;
		m_time_modifier_ -= .1f;
	}

	// Load the appropriate level from a text file
	string level_to_load;
	switch (m_current_level_)
	{

	case 1:
		level_to_load = "levels/level1.txt";
		m_start_position_.x = 100;
		m_start_position_.y = 100;
		m_base_time_limit_ = 30.0f;
		break;

	case 2:
		level_to_load = "levels/level2.txt";
		m_start_position_.x = 100;
		m_start_position_.y = 3600;
		m_base_time_limit_ = 100.0f;
		break;

	case 3:
		level_to_load = "levels/level3.txt";
		m_start_position_.x = 1250;
		m_start_position_.y = 0;
		m_base_time_limit_ = 30.0f;
		break;

	case 4:
		level_to_load = "levels/level4.txt";
		m_start_position_.x = 50;
		m_start_position_.y = 200;
		m_base_time_limit_ = 50.0f;
		break;
	default: ;
	}

	ifstream input_file(level_to_load);
	string s;

	// Count the number of rows in the file
	while (getline(input_file, s))
	{
		++m_level_size_.y;
	}

	// Store the length of the rows
	m_level_size_.x = s.length();

	// Go back to the start of the file
	input_file.clear();
	input_file.seekg(0, ios::beg);

	// Prepare the 2d array to hold the int values from the file
	const auto array_level = new int* [m_level_size_.y];
	for (int i = 0; i < m_level_size_.y; ++i)
	{
		// Add a new array into each array element
		array_level[i] = new int[m_level_size_.x];
	}

	// Loop through the file and store all the values in the 2d array
	string row;
	int y = 0;
	while (input_file >> row)
	{
		for (int x = 0; x < row.length(); x++) {

			const char val = row[x];
			array_level[y][x] = atoi(&val);
		}

		y++;
	}

	// close the file
	input_file.close();

	// What type of primitive are we using?
	r_va_level.setPrimitiveType(Quads);

	// Set the size of the vertex array
	r_va_level.resize(m_level_size_.x * m_level_size_.y * verts_in_quad);

	// Start at the beginning of the vertex array
	int current_vertex = 0;

	for (int x = 0; x < m_level_size_.x; x++)
	{
		for (int y = 0; y < m_level_size_.y; y++)
		{
			// Position each vertex in the current quad
			r_va_level[current_vertex + 0].position =
				Vector2f(x * tile_size, y * tile_size);

			r_va_level[current_vertex + 1].position =
				Vector2f((x * tile_size) + tile_size, y * tile_size);

			r_va_level[current_vertex + 2].position =
				Vector2f((x * tile_size) + tile_size, (y * tile_size) + tile_size);

			r_va_level[current_vertex + 3].position =
				Vector2f((x * tile_size), (y * tile_size) + tile_size);

			// Which tile from the sprite sheet should we use
			const int vertical_offset = array_level[y][x] * tile_size;

			r_va_level[current_vertex + 0].texCoords =
				Vector2f(0, 0 + vertical_offset);

			r_va_level[current_vertex + 1].texCoords =
				Vector2f(tile_size, 0 + vertical_offset);

			r_va_level[current_vertex + 2].texCoords =
				Vector2f(tile_size, tile_size + vertical_offset);

			r_va_level[current_vertex + 3].texCoords =
				Vector2f(0, tile_size + vertical_offset);

			// Position ready for the next four vertices
			current_vertex = current_vertex + verts_in_quad;
		}
	}

	return array_level;
}

Vector2i LevelManager::GetLevelSize() const
{
	return m_level_size_;
}

int LevelManager::GetCurrentLevel() const
{
	return m_current_level_;
}

float LevelManager::GetTimeLimit() const
{
	return m_base_time_limit_ * m_time_modifier_;

}
Vector2f LevelManager::GetStartPosition() const
{
	return m_start_position_;
}
