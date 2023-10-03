#include "TextureCache.h"

// Include the "assert feature"
#include <cassert>

TextureCache* TextureCache::m_s_instance_ = nullptr;

// Singleton check
TextureCache::TextureCache()
{
	assert(m_s_instance_ == nullptr);

	m_s_instance_ = this;
}

Texture& TextureCache::GetTexture(string const& filename)
{
	// Get a reference to m_Textures using m_s_Instance
	auto& m = m_s_instance_->m_textures_;

	// auto is the equivalent of map<string, Texture>
	// Create an iterator to hold a key-value-pair (kvp)

	const auto key_value_pair = m.find(filename);
	// auto is equivalent of map<string, Texture>::iterator

	// Did we find a match?
	if (key_value_pair != m.end())
	{
		// the second part of the kvp, the texture
		return key_value_pair->second;
	}
	else
	{
		// File name not found
		// Create a new key value pair using the filename
		auto& texture = m[filename];

		// Load the texture from file in the usual way
		texture.loadFromFile(filename);

		// Return the texture to the calling code
		return texture;
	}
}
