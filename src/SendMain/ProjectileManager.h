#pragma once

#include "Projectile.h"
#include <vector>
#include <time.h>

class ProjectileManager
{
public:
	ProjectileManager(Shader* sh, Transform* t);
	void add(Transform *t);
	void remove(Projectile* p);
	void UpdateDraw();
	~ProjectileManager();
	static const int MAX_NUM_PROJECTILES = 50;
private:
	Shader* m_shader;
	std::vector<Projectile*> *projectiles;
	time_t time;
};