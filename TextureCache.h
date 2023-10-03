#pragma once

#ifndef TEXTURE_HOLDER_H

#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

class TextureCache
{
private:
	// A map container from the STL,
	// that holds related pairs of String and Texture
	map< string, Texture> m_textures_;

	// A pointer of the same type as the class itself
	// the one and only instance
	static TextureCache* m_s_instance_;

public:
	TextureCache();

	static Texture& GetTexture(string const& filename);
};

#endif
