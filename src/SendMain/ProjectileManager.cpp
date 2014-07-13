#include "ProjectileManager.h"

ProjectileManager::ProjectileManager(Shader* sh, Transform* t)
{
	projectiles = new std::vector<Projectile*>;
	projectiles->reserve(MAX_NUM_PROJECTILES);
	m_shader = sh;
	time = clock();
}

void ProjectileManager::add(Transform* t)
{
	const int PERIOD = 250;
	if (clock() - time > PERIOD)
	{
		projectiles->push_back(new Projectile(m_shader, *t));
		time = clock();
	}
}

void ProjectileManager::remove(Projectile* p)
{
	int j;
	for (j = 0; j < projectiles->size(); j++)
	{
		if (projectiles->at(j) == p)
			break;
	}
	projectiles->erase(projectiles->begin() + j);
	delete p;
}

void ProjectileManager::UpdateDraw()
{
	for (int i = 0; i < projectiles->size(); i++)
	{
		Projectile* p = projectiles->at(i);
		if (p->isValid())
		{
			p->Update();
			p->Draw();
		}
		else
		{
			remove(p);
		}
	}
}

ProjectileManager::~ProjectileManager()
{
	for (int i = 0; i < projectiles->size(); i++)
	{
		delete projectiles->at(i);
	}
	delete projectiles;
}
