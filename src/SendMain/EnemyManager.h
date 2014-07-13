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

	std::vector<Enemy*> *m_enemies;
private:
	static const unsigned int NUM_TYPES = 2;
	
};

