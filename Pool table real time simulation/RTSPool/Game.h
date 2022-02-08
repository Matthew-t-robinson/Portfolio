#pragma once
#include<vector>
#include"Circles.h"
#include"Walls.h"
class Game
{
private:

public:
	void run();
	void collision();
	void movingCollision(Circles* one, Circles* two);
	float CosOfAngle(sf::Vector2f A, sf::Vector2f B);
	std::vector<Circles*> g_balls;
	std::vector<Walls*> g_walls;
	int bounces{ 0 };
	int HighScore{ 0 };
};

