#pragma once

#include "Sprite.h"
#include "Shader.h"

class Projectile
{
public:
	Projectile(Shader* sh, Transform t);
	void Update();
	void Draw();
	bool isValid();
	~Projectile();
private:
	Sprite* m_sprite;
	Shader* m_shader;
	Transform m_transform;
	bool m_good;
};

