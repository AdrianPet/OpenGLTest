#include "Player.h"
#include <iostream>
#include <windows.h>
#include <mmsystem.h>

#define MAX_HP 10000

Player::Player(Display* d, Shader* sh, std::string file, EnemyManager* em)
{
	float dim = 0.25f;
	hd = dim / 2.0f;
	Vertex verts[] = {
		Vertex(glm::vec3(hd, hd, 0), glm::vec2(1, 1)),
		Vertex(glm::vec3(hd, -hd, 0), glm::vec2(1, 0)),
		Vertex(glm::vec3(-hd, -hd, 0), glm::vec2(0, 0)),
		Vertex(glm::vec3(-hd, hd, 0), glm::vec2(0, 1))
	};

	m_sprite = new Sprite(verts, sizeof(verts) / sizeof(verts[0]), file.c_str());
	m_display = d;
	m_shader = sh;
	m_transform = new Transform(glm::vec3(0, -.5, 0));

	m_projectileManager = new ProjectileManager(m_shader, &m_forward, em);
	m_enemyManager = em;

	hp = MAX_HP;
}

void Player::Draw()
{
	m_shader->Update(*m_transform);
	m_sprite->Draw();
	m_projectileManager->Draw();
}

void Player::Update()
{
	if (hp < 0)
	{
		PlaySound("../data/Sounds/GameOver.wav", NULL, SND_SYNC | SND_FILENAME);
		exit(0);
	}

	if (hp < MAX_HP)
	{
		hp += MAX_HP / 900;
		std::cout << hp << std::endl;
	}

	if (hp < MAX_HP / 3)
	{
		PlaySound("../data/Sounds/alarm.wav", NULL, SND_ASYNC | SND_FILENAME);
	}

	m_shader->php = hp;
	m_projectileManager->Update();

	const float speed = 0.01f;
	const float uspeed = 5.0f;

	float yaw, pitch, roll;
	yaw = m_transform->GetRot()->y;
	pitch = m_transform->GetRot()->x;
	roll = m_transform->GetRot()->z;

	if (GLFW_PRESS == glfwGetKey(m_display->window, GLFW_KEY_A))
	{
		m_transform->SetRot(glm::vec3(pitch, yaw, roll + uspeed));
	}
	if (GLFW_PRESS == glfwGetKey(m_display->window, GLFW_KEY_D))
	{
		m_transform->SetRot(glm::vec3(pitch, yaw, roll - uspeed));
	}

	glm::vec3 f = *(m_transform->GetRot());
	double PI = atan(1) * 4;
	double fz = f.z * PI / 180;
	double c = cos(fz);
	double s = -sin(fz);

	//degeaba fac normalizarea, matematic, ca sin^2 + cos^2 = 1 oricum
	//dar mai sigur asa
	m_forward = glm::normalize(glm::vec3(s, c, 0));
	glm::vec3 up(0, 0, 1);
	glm::vec3 right = glm::cross(m_forward, up);

	if (GLFW_PRESS == glfwGetKey(m_display->window, GLFW_KEY_W))
	{
		m_transform->SetPos(speed * m_forward + (*(m_transform->GetPos())));
	}
	if (GLFW_PRESS == glfwGetKey(m_display->window, GLFW_KEY_S))
	{
		m_transform->SetPos(-speed * m_forward + (*(m_transform->GetPos())));
	}
	if (GLFW_PRESS == glfwGetKey(m_display->window, GLFW_KEY_Q))
	{
		m_transform->SetPos(-speed * right + (*(m_transform->GetPos())));
	}
	if (GLFW_PRESS == glfwGetKey(m_display->window, GLFW_KEY_E))
	{
		m_transform->SetPos(speed * right + (*(m_transform->GetPos())));
	}
	if (GLFW_PRESS == glfwGetKey(m_display->window, GLFW_KEY_SPACE))
	{
		Fire();
	}

	float x, y, z;
	x = m_transform->GetPos()->x;
	y = m_transform->GetPos()->y;
	z = m_transform->GetPos()->z;
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


	x = m_transform->GetPos()->x;
	y = m_transform->GetPos()->y;
	z = m_transform->GetPos()->z;

	float xm = x - hd;
	float xM = x + hd;
	float ym = y - hd;
	float yM = y + hd;

	int L = m_enemyManager->m_enemies->size();

	for (int j = 0; j < L; j++)
	{
		Enemy* e = m_enemyManager->m_enemies->at(j);
		//verifica daca se intersecteaza
		
		if (e->xm < xM && e->xM > xm &&
			e->ym < yM && e->yM > ym)
		{
			PlaySound("../data/Sounds/boom2.wav", NULL, SND_ASYNC | SND_FILENAME);
			e->TakeDamage();
			hp -= 2000;
			return;
		}
	}
}

void Player::Fire()
{
	m_projectileManager->add(m_transform);
}

Player::~Player()
{
	delete m_sprite;
	delete m_transform;
	delete m_projectileManager;
}
