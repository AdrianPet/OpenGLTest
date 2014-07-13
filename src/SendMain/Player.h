#pragma once

#include "Sprite.h"
#include "Display.h"
#include "Transform.h"
#include "Shader.h"
#include "ProjectileManager.h"
#include "EnemyManager.h"

class Player
{
public:
	Player(Display* d, Shader* sh, std::string file, EnemyManager* em);
	void Draw();
	void Update();
	void Fire();
	virtual ~Player();
private:
	Sprite* m_sprite;
	Display* m_display;
	Transform* m_transform;
	Shader* m_shader;
	ProjectileManager* m_projectileManager;
};