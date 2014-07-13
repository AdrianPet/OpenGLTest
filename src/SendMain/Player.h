#pragma once

#include "Sprite.h"
#include "Display.h"
#include "Transform.h"
#include "Shader.h"

class Player
{
public:
	Player(Display* d, Shader* sh, std::string file);
	void Draw();
	void Update();
	virtual ~Player();
private:
	Sprite* m_sprite;
	Display* m_display;
	Transform* m_transform;
	Shader* m_shader;
};