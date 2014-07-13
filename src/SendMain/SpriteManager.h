#pragma once
#include "Sprite.h"
#include <vector>

class SpriteManager
{
public:
	SpriteManager();
	void add(Sprite* square);
	void Draw();
	virtual ~SpriteManager();
private:
	std::vector<Sprite*> m_squares;
};

