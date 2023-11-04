#include "Knight.h"
#include "TextureCache.h"
#include <iostream>

Knight::Knight()
{
	m_IdleTexture = TextureCache::GetTexture("graphics/knight/idle.png");
	m_WalkingTexture = TextureCache::GetTexture("graphics/knight/walk.png");
	m_RunningTexture = TextureCache::GetTexture("graphics/knight/run.png");
	m_JumpingTexture = TextureCache::GetTexture("graphics/knight/jump.png");
	m_AttackingTexture = TextureCache::GetTexture("graphics/knight/attack_1.png");
	m_AttackingSlashTexture = TextureCache::GetTexture("graphics/knight/attack_slash.png");
	m_TakeDamageTexture = TextureCache::GetTexture("graphics/knight/hurt.png");
	m_DefendingTexture = TextureCache::GetTexture("graphics/knight/protect.png");

	m_PlayerSprite.setTexture(m_IdleTexture);

	m_JumpDuration = .25;

	m_IsIdle = true;
	m_PlayerIdleClock.restart();
	m_AnimIdleFrameCount = 0;

}
