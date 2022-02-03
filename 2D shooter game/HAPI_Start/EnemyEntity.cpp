#include "EnemyEntity.h"


void EnemyEntity::Update(visualisation& vis, World &w)
{	

	if (health <= 0)
	{
		m_alive = false;
	}
	if (m_alive == true)
	{
		fireBullet = rand() % 1000;
		//this moves the enemy a certain way depending on its route
		switch (route)
		{
		default:
			break;
		case 1:
			if (posX <= 20)
			{
				posY += 5;
			}
			if (posX >= 940)
			{
				posY -= 5;
			}
			if((posY <= 20))
			{
				posX -= 5;
			}
			if (posY >= 500)
			{
				posX += 5;
			}
			renderEntity(vis);
			break;
		case 2:
			if (posX <= 100)
			{
				posY -= 5;
			}
			if (posX >= 840)
			{
				posY += 5;
			}
			if (posY <= 100)
			{
				posX += 5;
			}
			if (posY >= 400)
			{
				posX -= 5;
			}
			renderEntity(vis);
			break;

		}
		//this fires a bullet randomly
		if (fireBullet <= 10)
		{
			w.fireBullet(false, posX, posY);
		}
	}
	
}
//this calls for the sprite to be rendered
void EnemyEntity::renderEntity(visualisation& vis)
{
	vis.RenderSpritePlayer("EnemySprite", posX, posY);
	
}

void EnemyEntity::SetBullet(Side side, float changingPosX, float changingPosY)
{
}
