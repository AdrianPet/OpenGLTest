#include "Background.h"


Background::Background(Shader* sh, std::string file)
{
	Vertex screen[] = {
		Vertex(glm::vec3(1, 1, 0), glm::vec2(1, 1)),
		Vertex(glm::vec3(1, -1, 0), glm::vec2(1, 0)),
		Vertex(glm::vec3(-1, -1, 0), glm::vec2(0, 0)),
		Vertex(glm::vec3(-1, 1, 0), glm::vec2(0, 1))
	};

	m_sprite = new Sprite(screen, sizeof(screen) / sizeof(screen[0]), file.c_str());
	m_shader = sh;
	m_transform = new Transform;
}

void Background::Draw()
{
	m_sprite->Draw();
}

void Background::Update()
{
	m_shader->Update(*m_transform);
}

Background::~Background()
{
	delete m_sprite;
	delete m_transform;
}
