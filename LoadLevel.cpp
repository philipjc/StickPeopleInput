#include "Engine.h"

void Engine::LoadLevel()
{
    bool m_playing = false;

    // Delete the previously allocated memory
    for (int i = 0; i < m_lm_manager_.GetLevelSize().y; ++i)
    {
        delete[] m_array_level_[i];
    }

    delete[] m_array_level_;

    // Load the next 2d array with the map for the level
    // And repopulate the vertex array as well
    m_array_level_ = m_lm_manager_.NextLevel(m_va_level_);

    // How long is this new time limit
    m_time_remaining_ = m_lm_manager_.GetTimeLimit();

    // Spawn Thomas and Bob
    m_thomas_.Spawn(m_lm_manager_.GetStartPosition(), gravity_);
    m_bob_.Spawn(m_lm_manager_.GetStartPosition(), gravity_);

    // Make sure this code isn't run again
    m_new_level_required_ = false;
}
