#include "ProjectileManager.h"
#include <windows.h>
#include <mmsystem.h>

ProjectileManager::ProjectileManager(Shader* sh, glm::vec3* forward, EnemyManager* em)
{
	m_enemyManager = em;
	m_projectiles = new std::vector<Projectile*>;
	m_projectiles->reserve(MAX_NUM_PROJECTILES);
	m_shader = sh;
	m_time = clock();
	m_forward = forward;
}

void ProjectileManager::add(Transform* t)
{
	const int PERIOD = 270;
	if (clock() - m_time > PERIOD)
	{
		m_projectiles->push_back(new Projectile(m_shader, *t, *m_forward));
		m_time = clock();
		PlaySound("../data/Sounds/shot.wav", NULL, SND_ASYNC | SND_FILENAME);
	}
}

void ProjectileManager::remove(Projectile* p)
{
	int j;
	for (j = 0; j < m_projectiles->size(); j++)
	{
		if (m_projectiles->at(j) == p)
			break;
	}
	m_projectiles->erase(m_projectiles->begin() + j);
	delete p;
}

void ProjectileManager::Update()
{
	
	for (int i = 0; i < m_projectiles->size(); i++)
	{
		Projectile* p = m_projectiles->at(i);
		
		float minDistance = 2.0f;
		int L = m_enemyManager->m_enemies->size();

		for (int j = 0; j < L; j++)
		{
			Enemy* e = m_enemyManager->m_enemies->at(j);
			if (fabs(e->xM - p->xM) < minDistance)
			{
				//verifica daca se intersecteaza
				bool result = check(e, p);
				if (result)
				{
					PlaySound("../data/Sounds/boom.wav", NULL, SND_ASYNC | SND_FILENAME);
					remove(p);
					e->hp -= 40;
					return;
				}
			}
		}
		

		if (p->isValid())
		{
			p->Update();
		}
		else
		{
			remove(p);
		}
	}
}

void ProjectileManager::Draw()
{
	for (int i = 0; i < m_projectiles->size(); i++)
	{
		Projectile* p = m_projectiles->at(i);
		p->Draw();
	}
}

bool ProjectileManager::check(Enemy* e, Projectile* p)
{
	if (e->xm < p->xM && e->xM > p->xm &&
		e->ym < p->yM && e->yM > p->ym)
		return true;
	return false;
}

ProjectileManager::~ProjectileManager()
{
	for (int i = 0; i < m_projectiles->size(); i++)
	{
		delete m_projectiles->at(i);
	}
	delete m_projectiles;
}
