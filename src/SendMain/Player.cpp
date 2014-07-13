#include "Player.h"

Player::Player(Display* d, Shader* sh, std::string file)
{
	float dim = 0.25f;
	float hd = dim / 2.0f;
	Vertex verts[] = {
		Vertex(glm::vec3(hd, hd, 0), glm::vec2(1, 1)),
		Vertex(glm::vec3(hd, -hd, 0), glm::vec2(1, 0)),
		Vertex(glm::vec3(-hd, -hd, 0), glm::vec2(0, 0)),
		Vertex(glm::vec3(-hd, hd, 0), glm::vec2(0, 1))
	};

	m_sprite = new Sprite(verts, sizeof(verts) / sizeof(verts[0]), file.c_str());
	m_display = d;
	m_shader = sh;
	m_transform = new Transform;
}

void Player::Draw()
{
	m_sprite->Draw();
}

void Player::Update()
{
	const float speed = 0.01f;

	float x, y, z;
	x = m_transform->GetPos()->x;
	y = m_transform->GetPos()->y;
	z = m_transform->GetPos()->z;

	if (GLFW_PRESS == glfwGetKey(m_display->window, GLFW_KEY_W))
	{
		y += speed;
	}
	if (GLFW_PRESS == glfwGetKey(m_display->window, GLFW_KEY_S))
	{
		y -= speed;
	}
	if (GLFW_PRESS == glfwGetKey(m_display->window, GLFW_KEY_A))
	{
		x -= speed;
	}
	if (GLFW_PRESS == glfwGetKey(m_display->window, GLFW_KEY_D))
	{
		x += speed;
	}
	const float ylimit = 0.9f;
	const float xlimit = 0.9f;
	if (fabs(y) < ylimit && fabs(x) < xlimit)
	{
		m_transform->SetPos(glm::vec3(x, y, z));
	}
	else
	{
		if (fabs(y) >= ylimit && fabs(x) >= xlimit)
		{
			m_transform->SetPos(glm::vec3(x < 0 ? -xlimit : xlimit, y < 0 ? -ylimit : ylimit, z));
		}
		else
		{
			if (fabs(y) >= ylimit)
			{
				m_transform->SetPos(glm::vec3(x, y < 0 ? -ylimit : ylimit, z));
			}
			else
			{
				m_transform->SetPos(glm::vec3(x < 0 ? -xlimit : xlimit, y, z));
			}
		}
	}

	m_shader->Update(*m_transform);
}

Player::~Player()
{
	delete m_sprite;
	delete m_transform;
}
