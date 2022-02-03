#include "Entity.h"
#include "sprite.h"
#include "visualisation.h"
//this checks to see if 2 entitys are enemies of eachother
bool Entity::IsEnemyOf(Side otherSide)
{
	if ((GetSide() == Side::ePlayer) && (otherSide == Side::eEnemy))
	{
		return true;
	}
	else if (GetSide() == Side::eEnemy && otherSide == Side::ePlayer)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//this checks if the entities rectangles are overlapping and if they are it returns that they are colliding
bool Entity::checkCollisionWith(Entity* other)
{

	sprite One;
	sprite Two;
	Rectangle OneSprite;
	Rectangle TwoSprite;
	OneSprite = textureRec;
	TwoSprite = other->textureRec;
	OneSprite.Translate(posX,posY);
	TwoSprite.Translate(other->posX, other->posY);
	
	if ((OneSprite.right < TwoSprite.left || OneSprite.left > TwoSprite.right) || (OneSprite.bottom < TwoSprite.top || OneSprite.top > TwoSprite.bottom))
	{
					
		return false;
	}
	else
	{

				/*std::cout << "collision" << std::endl;*/
		return true;
	}
		

}

//this gets the collision rectangle for an entity
Rectangle Entity::getRec()
{
	sprite rec;
	Rectangle rectangle;
	rectangle = rec.GetSpriteRectangle(SpriteName);
	return rectangle;
}
