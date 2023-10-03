#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class PlayableCharacter
{

protected:
	// Of course we will need a sprite
	Sprite m_sprite_;

	// How long does a jump last
	float m_jump_duration_ = 0;

	// Is character currently jumping or falling
	bool m_is_jumping_ = false;
	bool m_is_falling_ = false;

	// Which directions is the character currently moving in
	bool m_left_pressed_ = false;
	bool m_right_pressed_ = false;

	// How long has this jump lasted so far
	float m_time_this_jump_ = 0;

	// Has the player just initiated a jump
	bool m_just_jumped_ = false;

	// Private variables and functions come next
private:
	// What is the gravity
	float m_gravity_ = 0;

	// How fast is the character
	float m_speed_ = 400;

	// Where is the player
	Vector2f m_position_;

	// Where are the characters various body parts?
	FloatRect m_feet_;
	FloatRect m_head_;
	FloatRect m_right_;
	FloatRect m_left_;

	// And a texture
	Texture m_texture_;

	// All our public functions will come next
public:
	virtual ~PlayableCharacter() = default;
	void Spawn(Vector2f start_position, float gravity);
	// This is a pure virtual function

	bool virtual HandleInput() = 0;

	// This class is now abstract and cannot be instantiated
	// Where is the player
	FloatRect GetPosition() const;

	// A rectangle representing the position 
	// of different parts of the sprite
	FloatRect GetFeet() const;
	FloatRect GetHead() const;
	FloatRect GetRight() const;
	FloatRect GetLeft() const;

	// Send a copy of the sprite to main
	Sprite GetSprite();

	// Make the character stand firm
	void StopFalling(float position);
	void StopRight(float position);
	void StopLeft(float position);
	void StopJump();

	// Where is the center of the character
	Vector2f GetCenter() const;

	// We will call this function once every frame
	void Update(float elapsed_time);
};
