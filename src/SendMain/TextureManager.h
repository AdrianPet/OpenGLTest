#pragma once

#include <string>
#include <map>

#include "rapidxml\rapidxml.hpp"
#include "rapidxml\rapidxml_iterators.hpp"
#include "rapidxml\rapidxml_print.hpp"
#include "rapidxml\rapidxml_utils.hpp"

#include "Texture.h"

class Loaded_Texture{
public:
	~Loaded_Texture();

	unsigned char* texture;
	std::string imageName;
	int height, width;
};

class Dict_Entry{
public:
	~Dict_Entry();

	char* sprite_name;
	int x, y, width, height;
	unsigned char* refTex;

};

class TextureManager
{
public:
	TextureManager();
	~TextureManager();
private:
	std::map<std::string, Dict_Entry * > loadedSprites;
	std::map<std::string, Loaded_Texture*> loadedTextures;
};

