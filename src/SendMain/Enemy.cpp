#include "Enemy.h"
#include <stdlib.h>

Enemy::Enemy(Shader* s, float dim, int t)
{
	float hd = dim / 2.0f;
	Vertex verts[] = {
		Vertex(glm::vec3(hd, hd, 0), glm::vec2(1, 1)),
		Vertex(glm::vec3(hd, -hd, 0), glm::vec2(1, 0)),
		Vertex(glm::vec3(-hd, -hd, 0), glm::vec2(0, 0)),
		Vertex(glm::vec3(-hd, hd, 0), glm::vec2(0, 1))
	};

	std::string file;
	m_type = t;
	file = m_type == 0 ? std::string("../data/Textures/Enemy1.png") : std::string("../data/Textures/Enemy2.png");
	
	m_sprite = new Sprite(verts, sizeof(verts) / sizeof(verts[0]), file.c_str());

	m_asc = 1;
	m_fps = 0.0f;

	m_shader = s;
	m_transform = new Transform;

	float x, y, z;
	x = (rand() % 100 - 50) / 50.0f;
	y = (rand() % 100 - 20) / 100.0f;
	z = 0;

	m_transform->SetPos(glm::vec3(x, y, z));
	m_shader->Update(*m_transform);
}

void Enemy::Draw()
{
	m_sprite->Draw();
}

void Enemy::Update()
{
	float speed = 0.015f;
	float limit = 0.85f;
	float x, y, z;
	x = m_transform->GetPos()->x;
	y = m_transform->GetPos()->y;
	z = m_transform->GetPos()->z;

	if (m_type == 1)
	{
		if (y + sinf(m_fps) / 200 < limit)
			y += sinf(m_fps) / 200;

		m_fps += speed;
	}

	x += m_asc * speed;
	if (fabs(x) < limit)
	{
		m_transform->SetPos(glm::vec3(x, y, z));
	}
	else
	{
		m_transform->SetPos(glm::vec3(x < 0 ? -limit : limit, y, z));
		m_asc *= -1;
	}

	m_shader->Update(*m_transform);
}

Enemy::~Enemy()
{
	delete m_sprite;
	delete m_transform;
}
