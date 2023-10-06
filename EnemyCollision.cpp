#include "Engine.h"

bool Engine::EnemyCollision(Enemy& enemy) const
{
	bool reachedGoal = false;
	// Make a rect for all his parts
	const FloatRect detectionZone = enemy.GetEnemyPosition();


	// Make a FloatRect to test each block
	FloatRect block;

	block.width = static_cast<float>(tile_Size);
	block.height = static_cast<float>(tile_Size);

	// Build a zone around thomas to detect collisions
	int startX = static_cast<int>(detectionZone.left) / tile_Size - 1;
	int startY = static_cast<int>(detectionZone.top) / tile_Size - 1;
	int endX = static_cast<int>(detectionZone.left) / tile_Size + 2;

	// Thomas is quite tall so check a few tiles vertically
	int endY = static_cast<int>(detectionZone.top) / tile_Size + 3;

	// Make sure we don't test positions lower than zero
	// Or higher than the end of the array
	if (startX < 0)startX = 0;
	if (startY < 0)startY = 0;
	if (endX >= m_Lm.GetLevelSize().x)
		endX = m_Lm.GetLevelSize().x;
	if (endY >= m_Lm.GetLevelSize().y)
		endY = m_Lm.GetLevelSize().y;

	// Has the enemy fallen out of the map?
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!This can be part of level manager!!!!!!!!!!!!!!!!!!!!!!!!
	const FloatRect level(0, 0, static_cast<float>(m_Lm.GetLevelSize().x * tile_Size), static_cast<float>(m_Lm.GetLevelSize().y * tile_Size));
	if (!enemy.GetEnemyPosition().intersects(level))
	{
		// re-spawn the enemy
		enemy.SpawnEnemy(m_Lm.GetStartPosition(), static_cast<int>(gravity));
	}

	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			// Initialize the starting position of the current block
			block.left = static_cast<float>(x * tile_Size);
			block.top = static_cast<float>(y * tile_Size);

			// Has enemy been burnt or drowned?
			// Use head as this allows him to sink a bit
			/*if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
			{
				if (enemy.GetHead().intersects(block))
				{
					enemy.Spawn(m_Lm.GetStartPosition(), static_cast<int>(gravity));

					// Which sound should be played?
					if (m_ArrayLevel[y][x] == 2)// Fire, ouch!
					{
						// Play a sound

					}
					else // Water
					{
						// Play a sound
					}
				}
			}*/


			// Is enemy colliding with a regular block
			if (m_ArrayLevel[y][x] == 1)
			{

				/*if (enemy.GetRight().intersects(block))
				{
					enemy.StopRight(block.left);
				}
				else if (enemy.GetLeft().intersects(block))
				{
					enemy.StopLeft(block.left);
				}
				*/

				if (enemy.GetEnemyFeet().intersects(block))
				{
					enemy.StopEnemyFalling(block.top);
				}
				//else if (enemy.GetHead().intersects(block))
				//{
				//	enemy.StopJump();
				//}
			}

			// More collision detection here once we have learned about particle effects

			// Has the enemy reached the goal?
			if (m_ArrayLevel[y][x] == 4)
			{
				// Character has reached the goal
				reachedGoal = true;
			}

		}

	}

	// All done, return, whether or not a new level might be required
	return reachedGoal;
}
