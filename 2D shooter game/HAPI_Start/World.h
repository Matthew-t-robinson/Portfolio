#pragma once
#include <vector>
#include "visualisation.h"
class visualisation;

class Entity;

class World
{
private:
	void LoadLevel();

	int w_bulletIndexStart{ 0 };
	int	w_explosionIndexStart{ 0 };
	int w_explosionIndexEnd{ 0 };
	int w_enemyIndexStart{ 0 };
	int w_enemyIndexEnd{ 0 };
	
	int countForEnemy{ 0 };

	
	
	

	std::string score;
	std::string currentHealth;
	visualisation w_vis;

	
	
public:
	~World();
	void Run();
	void World::fireBullet(bool whichSide, float posX, float posY);
	void World::takeDamage(Entity* takingDamage, int damage);
	void World::addScore(int score);
	void World::spawnExplosion(float posX, float posY);
	void World::spawnEnemy();
	int CurrentScore{ 0 };
	std::vector<Entity*> w_entityVector;
	bool spaceHeld{ false };
	bool aHeld{ false };
	
};

