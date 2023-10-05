#pragma once
#include <SFML/Graphics.hpp>
#include "TextureCache.h"
#include "Thomas.h"
#include "Bob.h"
#include "LevelManager.h"

using namespace sf;

class Engine
{
private:
	// The texture holder
	TextureCache th;

	// Thomas and his friend, Bob
	Thomas m_Thomas;
	Bob m_Bob;

	// A class to manage all the levels
	LevelManager m_LM;

	const int tile_Size = 50;
	const int verts_In_Quad = 4;

	// The force pushing the characters down
	const int gravity = 300;

	// A regular RenderWindow
	RenderWindow m_Window;

	// The main Views
	View m_MainView;
	View m_LeftView;
	View m_RightView;

	// Three views for the background
	View m_BgMainView;
	View m_BgLeftView;
	View m_BgRightView;

	View m_HudView;

	// Declare a sprite and a Texture for the background
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;

	// Is the game currently playing?
	bool m_Playing = false;

	// Is character 1 or 2 the current focus?
	bool m_Character1 = true;

	// Start in full screen mode
	bool m_SplitScreen = false;

	// How much time is left in the current level
	float m_TimeRemaining = 10;
	Time m_GameTimeTotal;

	// Is it time for a new/first level?
	bool m_NewLevelRequired = true;

	// The vertex array for the level design
	VertexArray m_VaLevel;

	// The 2d array with the map for the level
	// A pointer to a pointer
	int** m_ArrayLevel = nullptr;

	// Texture for the background and the level tiles
	Texture m_TextureTiles;

	// Private functions for internal use only
	void Input();
	void Update(float dt_as_seconds);
	void Draw();

	// Load a new level
	void LoadLevel();

	// Run will call all the private functions
	bool DetectCollisions(PlayableCharacter& character);

public:
	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void Run();

};