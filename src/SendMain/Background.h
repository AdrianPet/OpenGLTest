#pragma once

#include "Shader.h"
#include "Transform.h"
#include "Sprite.h"

class Background
{
public:
	Background(Shader* sh, std::string file);

	void Update();
	void Draw();

	~Background();

private:
	Shader* m_shader;
	Transform* m_transform;
	Sprite* m_sprite;
};

