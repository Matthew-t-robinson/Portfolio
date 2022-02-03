#pragma once
#include "visualisation.h"
#include "sprite.h"
#include "World.h"

enum class Side
{
	eNeutral,
	ePlayer,
	eEnemy
};

class Entity
{
private:
public:
	
	virtual ~Entity() = default;
	bool m_alive{ false };
	virtual void Update(visualisation &vis, World &w) = 0;
	virtual void SetBullet(Side side, float changingPosX, float changingPosY) = 0;
	virtual Side GetSide() const = 0;
	virtual int GetDamage() const = 0;
	virtual int GetScore() const = 0;
	bool IsEnemyOf(Side otherSide);
	bool checkCollisionWith(Entity* other);
	Rectangle getRec();
	float posX{ 512 };
	float posY{ 600 };
	int health{ 0 };
	int route{ 0 };
	std::string SpriteName;
	Rectangle textureRec{0,0,0,0};
};

