#pragma once

#include "Projectile.h"
#include "EnemyManager.h"
#include <vector>
#include <time.h>

class ProjectileManager
{
public:
	ProjectileManager(Shader* sh, glm::vec3* forward, EnemyManager* em);
	void add(Transform *t);
	void remove(Projectile* p);
	void Update();
	void Draw();
	~ProjectileManager();
	static const int MAX_NUM_PROJECTILES = 3;
private:
	bool check(Enemy* e, Projectile* p);

	glm::vec3* m_forward;
	Shader* m_shader;
	EnemyManager* m_enemyManager;
	std::vector<Projectile*> *m_projectiles;
	time_t m_time;
};