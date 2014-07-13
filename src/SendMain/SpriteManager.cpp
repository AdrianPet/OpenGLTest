#include "SpriteManager.h"


SpriteManager::SpriteManager()
{
}


void SpriteManager::add(Sprite* square)
{
	m_squares.push_back(square);
}

void SpriteManager::Draw()
{
	for (int i = 0; i < m_squares.size(); i++)
	{
		(m_squares[i])->Draw();
	}
}

SpriteManager::~SpriteManager()
{
	for (int i = 0; i < m_squares.size(); i++)
	{
		delete m_squares[i];
	}
	m_squares.erase(m_squares.begin(), m_squares.end());
}