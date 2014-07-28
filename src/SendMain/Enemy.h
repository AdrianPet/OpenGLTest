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

	float xm, xM, ym, yM;
	int hp;
private:
	Sprite* m_sprite;
	Shader* m_shader;
	Transform* m_transform;
	int m_type;
	int m_asc;
	float m_fps;
	float hd;
};