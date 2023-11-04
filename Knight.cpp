#include "Knight.h"
#include "TextureCache.h"
#include <iostream>


Knight::Knight()
{
	m_IdleTexture = TextureCache::GetTexture("graphics/knight/idle.png");
	m_WalkingTexture = TextureCache::GetTexture("graphics/knight/walk.png");
	m_AttackingTexture = TextureCache::GetTexture("graphics/knight/attack_1.png");
	m_AttackingSlashTexture = TextureCache::GetTexture("graphics/knight/attack_slash.png");

	// Associate a texture with the sprite
	m_PlayerSprite = Sprite();
	m_PlayerSprite.setTexture(m_IdleTexture);

	m_JumpDuration = .25;

	m_IsIdle = true;
	m_PlayerIdleClock.restart();
	m_AnimIdleFrameCount = 0;

}
