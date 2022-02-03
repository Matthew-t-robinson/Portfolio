#include "BulletEntity.h"
//this updates the bullet, checking if its outside of the visible screen and stopping it from being rendered if it is
// it also moves the bullet in a certain direction depending on its side
void BulletEntity::Update(visualisation& vis, World& w)
{
	if (posY < 0)
	{
		health = 0;
	}
	if (posY > 768)
	{
		health = 0;
	}
	if (health <= 0)
	{
		m_side = Side::eNeutral;
		m_alive = false;
	}
	if (m_side == Side::eEnemy)
	{

		posY += 10;
	}
	else if (m_side == Side::ePlayer)
	{

		posY -= 10;
	}
	else if (m_side == Side::eNeutral)
	{

	}
	if (m_alive == true)
	{

		renderEntity(vis);
	}
}

//this calls for the bullet sprite to be rendered
void BulletEntity::renderEntity(visualisation& vis)
{
	
	vis.RenderSpritePlayer("BulletSprite", posX, posY);
}

//this sets the bullets side and position
void BulletEntity::SetBullet(Side side, float changingPosX, float changingPosY)
{
	m_side = side;
	posX = changingPosX;
	posY = changingPosY;
}
