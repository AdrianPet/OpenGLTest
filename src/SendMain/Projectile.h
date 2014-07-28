#pragma once

#include "Sprite.h"
#include "Shader.h"

class Projectile
{
public:
	Projectile(Shader* sh, Transform t, glm::vec3 forward);
	void Update();
	void Draw();
	bool isValid();
	~Projectile();

	float xm, xM, ym, yM;
private:
	Sprite* m_sprite;
	Shader* m_shader;
	Transform m_transform;
	bool m_good;
	float hd;
	glm::vec3 m_forward;
};

