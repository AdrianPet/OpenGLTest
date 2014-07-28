#include "EnemyManager.h"
#include <stdlib.h>
#include <time.h>

EnemyManager::EnemyManager(Shader* sh, int number)
{
	m_enemies = new std::vector<Enemy*>;
	m_enemies->reserve(number);
	float enemySize = 0.3f;
	srand(time(NULL));

	for (int i = 0; i < number; i++)
		m_enemies->push_back(new Enemy(sh, enemySize, rand() % NUM_TYPES));
}

void EnemyManager::Update()
{
	for (int i = 0; i < m_enemies->size(); i++)
	{
		Enemy* e = m_enemies->at(i);
		if (e->hp < 0)
		{
			delete e;
			m_enemies->erase(m_enemies->begin() + i);
			i--;
			continue;
		}
		e->Update();
	}
}

void EnemyManager::Draw()
{
	for (int i = 0; i < m_enemies->size(); i++)
	{
		Enemy* e = m_enemies->at(i);
		e->Draw();
	}
}

EnemyManager::~EnemyManager()
{
	for (int i = 0; i < m_enemies->size(); i++)
	{
		delete m_enemies->at(i);
	}
	delete m_enemies;
}
