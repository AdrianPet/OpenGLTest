#include "Projectile.h"


Projectile::Projectile(Shader* sh, Transform t, glm::vec3 forward)
{
	float dim = 0.1f;
	hd = dim / 2.0f;
	Vertex verts[] = {
		Vertex(glm::vec3(hd, hd, 0), glm::vec2(1, 1)),
		Vertex(glm::vec3(hd, -hd, 0), glm::vec2(1, 0)),
		Vertex(glm::vec3(-hd, -hd, 0), glm::vec2(0, 0)),
		Vertex(glm::vec3(-hd, hd, 0), glm::vec2(0, 1))
	};

	m_shader = sh;
	m_sprite = new Sprite(verts, sizeof(verts) / sizeof(verts[0]), "../data/Textures/projectile.png");
	m_transform = t;
	m_forward = forward;
	m_good = true;

	xm = m_transform.GetPos()->x - hd;
	xM = m_transform.GetPos()->x + hd;
	ym = m_transform.GetPos()->y - hd;
	yM = m_transform.GetPos()->y + hd;
}

void Projectile::Update()
{
	float x, y, z,speed = 0.01f;
	
	m_transform.SetPos(speed * m_forward + (*(m_transform.GetPos())));
	
	x = m_transform.GetPos()->x;
	y = m_transform.GetPos()->y;
	z = m_transform.GetPos()->z;

	xm = x - hd;
	xM = x + hd;
	ym = y - hd;
	yM = y + hd;

	if (y > 1 || y < -1 || x > 1 || x < -1)
	{
		m_good = false;
	}
}

void Projectile::Draw()
{
	m_shader->Update(m_transform);
	m_sprite->Draw();
}

bool Projectile::isValid()
{
	return m_good;
}

Projectile::~Projectile()
{
	delete m_sprite;
}
