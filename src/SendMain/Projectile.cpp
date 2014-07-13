#include "Projectile.h"


Projectile::Projectile(Shader* sh, Transform t)
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
	m_good = true;

	xm = m_transform.GetPos()->x - hd;
	xM = m_transform.GetPos()->x + hd;
	ym = m_transform.GetPos()->y - hd;
	yM = m_transform.GetPos()->y + hd;
}

void Projectile::Update()
{
	float x, y, z,speed = 0.01f;
	x = m_transform.GetPos()->x;
	y = m_transform.GetPos()->y;
	z = m_transform.GetPos()->z;

	m_transform.SetPos(glm::vec3(x, y + speed, z));
	
	// nu ar trebui sa fie /8 dupa algoritm, 
	// dar pare ca arata mai realist asa
	ym = m_transform.GetPos()->y - hd / 8;
	yM = m_transform.GetPos()->y + hd / 8;
	
	m_shader->Update(m_transform);
	if (y > 1)
	{
		m_good = false;
	}
}

void Projectile::Draw()
{
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
