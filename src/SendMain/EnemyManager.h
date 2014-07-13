#pragma once

#include "Enemy.h"
#include "Shader.h"
#include <vector>

class EnemyManager
{
public:
	EnemyManager(Shader* sh, int number);
	void UpdateDraw();

	~EnemyManager();
private:
	static const unsigned int NUM_TYPES = 2;
	
	std::vector<Enemy*> *m_enemies;
};

