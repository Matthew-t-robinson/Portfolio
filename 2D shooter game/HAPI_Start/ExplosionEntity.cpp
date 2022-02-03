#include "ExplosionEntity.h"

void ExplosionEntity::Update(visualisation& vis, World& w)
{
	if (m_alive)
	{
		renderEntity(vis);
	}
}
//this sets the explosion sprite to be different depending on how many times its been called, making it animated
void ExplosionEntity::renderEntity(visualisation& vis)
{
	if (count == 6)
	{
		SpriteName = "ExplosionSprite2";
	}
	if (count == 12)
	{
		SpriteName = "ExplosionSprite3";
	}
	if (count == 18)
	{
		SpriteName = "ExplosionSprite4";
	}
	if (count == 24)
	{
		SpriteName = "ExplosionSprite5";
	}
	if (count == 30)
	{
		SpriteName = "ExplosionSprite6";
	}
	if (count == 36)
	{
		SpriteName = "ExplosionSprite7";
	}
	if (count == 42)
	{
		SpriteName = "ExplosionSprite8";
	}
	if (count == 48)
	{
		SpriteName = "ExplosionSprite9";
	}
	if (count == 54)
	{
		SpriteName = "ExplosionSprite10";
	}
	if (count == 60)
	{
		SpriteName = "ExplosionSprite11";
	}
	if (count == 66)
	{
		SpriteName = "ExplosionSprite12";
	}
	if (count > 66)
	{
		count = 0;
		m_alive = false;
	}
	vis.RenderSpritePlayer(SpriteName, posX, posY);
	count += 1;
}

void ExplosionEntity::SetBullet(Side side, float changingPosX, float changingPosY)
{
}
