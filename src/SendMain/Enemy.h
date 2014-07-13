#pragma once

#include "Sprite.h"
#include "Shader.h"
#include "Transform.h"

class Enemy
{
public:
	Enemy(Shader* s, float dim, int t);
	void Update();
	void Draw();

	virtual ~Enemy();
private:
	Sprite* m_sprite;
	Shader* m_shader;
	Transform* m_transform;
	int m_type;

	static const unsigned int NUM_TYPES = 2;
};