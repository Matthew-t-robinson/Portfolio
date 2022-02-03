#include "World.h"
#include"visualisation.h"
#include"PlayerEntity.h"
#include"EnemyEntity.h"
#include"BulletEntity.h"
#include"ExplosionEntity.h"

void World::LoadLevel()
{
	//this calls for all of the sprites to be created
	if (!w_vis.CreateSprite("Background", "Data\\background.png"))
	{
		HAPI.UserMessage("MISSING TEXTURE BACKGROUND", "ERROR");
		return;
	}
	if (!w_vis.CreateSprite("PlayerSprite", "Data\\playerModel.png"))
	{
		HAPI.UserMessage("MISSING TEXTURE PLAYER", "ERROR");
		return;
	}
	if (!w_vis.CreateSprite("EnemySprite", "Data\\enemyModel.png"))
	{
		HAPI.UserMessage("MISSING TEXTURE ENEMY", "ERROR");
		return;
	}
	if (!w_vis.CreateSprite("BulletSprite", "Data\\laserBullet.tga"))
	{
		HAPI.UserMessage("MISSING TEXTURE BULLET", "ERROR");
		return;
	}
	if (!w_vis.CreateSprite("ExplosionSprite1", "Data\\Explosion1.png"))
	{
		HAPI.UserMessage("MISSING TEXTURE EXPLOSION", "ERROR");
		return;
	}
	if (!w_vis.CreateSprite("ExplosionSprite2", "Data\\Explosion2.png"))
	{
		HAPI.UserMessage("MISSING TEXTURE EXPLOSION", "ERROR");
		return;
	}
	if (!w_vis.CreateSprite("ExplosionSprite3", "Data\\Explosion3.png"))
	{
		HAPI.UserMessage("MISSING TEXTURE EXPLOSION", "ERROR");
		return;
	}
	if (!w_vis.CreateSprite("ExplosionSprite4", "Data\\Explosion4.png"))
	{
		HAPI.UserMessage("MISSING TEXTURE EXPLOSION", "ERROR");
		return;
	}
	if (!w_vis.CreateSprite("ExplosionSprite5", "Data\\Explosion5.png"))
	{
		HAPI.UserMessage("MISSING TEXTURE EXPLOSION", "ERROR");
		return;
	}
	if (!w_vis.CreateSprite("ExplosionSprite6", "Data\\Explosion6.png"))
	{
		HAPI.UserMessage("MISSING TEXTURE EXPLOSION", "ERROR");
		return;
	}
	if (!w_vis.CreateSprite("ExplosionSprite7", "Data\\Explosion7.png"))
	{
		HAPI.UserMessage("MISSING TEXTURE EXPLOSION", "ERROR");
		return;
	}
	if (!w_vis.CreateSprite("ExplosionSprite8", "Data\\Explosion8.png"))
	{
		HAPI.UserMessage("MISSING TEXTURE EXPLOSION", "ERROR");
		return;
	}
	if (!w_vis.CreateSprite("ExplosionSprite9", "Data\\Explosion9.png"))
	{
		HAPI.UserMessage("MISSING TEXTURE EXPLOSION", "ERROR");
		return;
	}
	if (!w_vis.CreateSprite("ExplosionSprite10", "Data\\Explosion10.png"))
	{
		HAPI.UserMessage("MISSING TEXTURE EXPLOSION", "ERROR");
		return;
	}
	if (!w_vis.CreateSprite("ExplosionSprite11", "Data\\Explosion11.png"))
	{
		HAPI.UserMessage("MISSING TEXTURE EXPLOSION", "ERROR");
		return;
	}
	if (!w_vis.CreateSprite("ExplosionSprite12", "Data\\Explosion12.png"))
	{
		HAPI.UserMessage("MISSING TEXTURE EXPLOSION", "ERROR");
		return;
	}
	//this creates the player entity and adds it to the entity vector
	std::string file = "Data\\playerModel.png";
	PlayerEntity* newPlayer = new PlayerEntity();
	newPlayer->m_alive = true;
	newPlayer->health = 10;
	newPlayer->SpriteName = file;
	newPlayer->textureRec = newPlayer->getRec();
	w_entityVector.push_back(newPlayer);
	file = "Data\\enemyModel.png";
	w_enemyIndexStart = (int)w_entityVector.size();
	//this creates the enemy entities and adds it to the entity vector
	for (size_t i = 0; i < 40; i++)
	{

		EnemyEntity* newEnemy = new EnemyEntity;
		newEnemy->m_alive = false;
		newEnemy->SpriteName = file;
		newEnemy->textureRec = newPlayer->getRec();
		w_entityVector.push_back(newEnemy);
	}
	w_enemyIndexEnd = (int)w_entityVector.size();
	w_explosionIndexStart = (int)w_entityVector.size();
	//this creates the explosion entities and adds it to the entity vector
	for (size_t i = 0; i < 10; i++)
	{
		ExplosionEntity* newExplosion = new ExplosionEntity;
		newExplosion->m_alive = false;
		newExplosion->SpriteName = "ExplosionSprite1";
		w_entityVector.push_back(newExplosion);
	}
	w_explosionIndexEnd = (int)w_entityVector.size();
	HAPI.SetShowFPS(true);
	HAPI.LimitFrameRate(60);
	file = "Data\\laserBullet.tga";
	w_bulletIndexStart = (int)w_entityVector.size();
	//this creates the bullet entities and adds it to the entity vector
	for (int i = 0; i < 100; i++)
	{
		BulletEntity* newBullet = new BulletEntity;
		newBullet->m_alive = false;
		newBullet->health = 1;
		newBullet->SpriteName = file;
		newBullet->textureRec = newBullet->getRec();
		w_entityVector.push_back(newBullet);
	}
	
}

World::~World()
{
	for (auto& p : w_entityVector)
		delete p;
}

void World::Run()
{
	//this creats for the window to be created
	if (!w_vis.Initialise())
	{
		return;
	}

	LoadLevel();
	const HAPI_TKeyboardData& KeyData = HAPI.GetKeyboardData();
	
	//this updates the game while the game is open
	while (HAPI.Update())
	{
		//this checks to see if the player is alive before rendering the program
		if (w_entityVector[0]->m_alive)
		{
			w_vis.RenderSpriteBG("Background", 0, 0);

			//this renders the score and the players health onto the screen
			score = std::to_string(CurrentScore);
			HAPI.RenderText(800, 25, HAPI_TColour::WHITE, "SCORE: " + score, 20, eRegular);
			currentHealth = std::to_string(w_entityVector[0]->health);
			HAPI.RenderText(800, 50, HAPI_TColour::WHITE, "HEALTH: " + currentHealth, 20, eRegular);

			//this loop is so that there is a delay between the enemys spawning
			if (countForEnemy == 50)
			{
				spawnEnemy();
				countForEnemy = 0;
			}
			//this calls for all the entities to be updated
			for (Entity* p : w_entityVector)
			{

				p->Update(w_vis, *this);


			}
			//this goes through every entity and checks it against every other entity. 
			//If they are both alive, are enemies of eachother and aren't the same sprite it will check if they are colliding.
			for (size_t e1 = 0; e1 < w_entityVector.size(); e1++)
			{

				for (size_t e2 = 0; e2 < w_entityVector.size(); e2++)
				{

					if ((w_entityVector[e1]->m_alive) && (w_entityVector[e2]->m_alive))
					{

						if (w_entityVector[e1]->IsEnemyOf(w_entityVector[e2]->GetSide()))
						{

							if (w_entityVector[e1]->SpriteName != w_entityVector[e2]->SpriteName)
							{
									if (w_entityVector[e1]->checkCollisionWith(w_entityVector[e2]) == true) 
									{
										//this damages the entities that collided and adds there score to the current score
										takeDamage(w_entityVector[e1], w_entityVector[e2]->GetDamage());
										
										addScore(w_entityVector[e1]->GetScore());
										
										//this creates an expolsion if the entities health is either 0 or less than 0 and if the sprite is not a bullet.
										if ((w_entityVector[e1]->SpriteName != "Data\\laserBullet.tga") && (w_entityVector[e1]->health <= 0))
										{
											spawnExplosion(w_entityVector[e1]->posX, w_entityVector[e1]->posY);
										}
										if ((w_entityVector[e2]->SpriteName != "Data\\laserBullet.tga") && (w_entityVector[e2]->health <= 0))
										{
											spawnExplosion(w_entityVector[e2]->posX, w_entityVector[e2]->posY);
										}
									}
							}
						}
					}
				}
			}
			
			
			countForEnemy += 1;
		}
		//if the player is not alive it will show the score and the screen and tell the player they died
		// the only inputs that can be taken are to restart the game
		else
		{
			const HAPI_TKeyboardData& keyScan = HAPI.GetKeyboardData();
			const HAPI_TControllerData& controllerScan = HAPI.GetControllerData(0);
			HAPI.RenderText(400, 300, HAPI_TColour::WHITE, "SCORE: " + score, 40, eRegular);
			currentHealth = std::to_string(w_entityVector[0]->health);
			HAPI.RenderText(420, 100, HAPI_TColour::WHITE, "YOU DIED ", 40, eRegular);
			if (keyScan.scanCode['R'])
			{
				for (size_t i =1 ; i < w_entityVector.size(); i++)
				{	
					w_entityVector[i]->m_alive = false;
					w_entityVector[i]->posX = 0;
					w_entityVector[i]->posY = 0;
					w_entityVector[i]->health = 1;
				}
				w_entityVector[0]->m_alive = true;
				w_entityVector[0]->health = 10;
				w_entityVector[0]->posX = 512;
				w_entityVector[0]->posY = 600;
				CurrentScore = 0;
			}
			if (controllerScan.isAttached && controllerScan.digitalButtons[HK_DIGITAL_B])
			{
				for (size_t i = 1; i < w_entityVector.size(); i++)
				{
					w_entityVector[i]->m_alive = false;
					w_entityVector[i]->posX = 0;
					w_entityVector[i]->posY = 0;
					w_entityVector[i]->health = 1;
				}
				w_entityVector[0]->m_alive = true;
				w_entityVector[0]->health = 10;
				w_entityVector[0]->posX = 512;
				w_entityVector[0]->posY = 600;
				CurrentScore = 0;
			}

		}
	}
}

void World::fireBullet(bool whichSide, float posX, float posY)
{
	bool found{ false };
	for (size_t i = w_bulletIndexStart; i < w_entityVector.size(); i++)
	{
		if (w_entityVector[i]->m_alive == false && found == false)
		{
			found = true;
			w_entityVector[i]->m_alive = true;
			w_entityVector[i]->health = 1;
			if (whichSide == true)
			{
				w_entityVector[i]->SetBullet(Side::ePlayer, posX, posY);
			}
			if (whichSide == false)
			{
				w_entityVector[i]->SetBullet(Side::eEnemy, posX, posY);
			}
		}
		if(w_entityVector[i]->m_alive == true && found == false)
		{ 
			i = i;
		}
	}
}

void World::takeDamage(Entity* takingDamage, int damage)
{
	takingDamage->health -= damage;
}

void World::addScore(int score)
{
	CurrentScore += score;
}

void World::spawnExplosion(float ChangePosX, float ChangePosY)
{
	bool found{ false };
	for (size_t i = w_explosionIndexStart; i < w_explosionIndexEnd; i++)
	{

		if (w_entityVector[i]->m_alive == false && found == false)
		{
			found = true;
			w_entityVector[i]->m_alive = true;
			w_entityVector[i]->posX = ChangePosX;
			w_entityVector[i]->posY = ChangePosY;
		}

		if (w_entityVector[i]->m_alive == true && found == false)
		{
			i = i;
		}
	}
}

void World::spawnEnemy()
{
	bool found{ false };
	for (size_t i = w_enemyIndexStart; i < w_enemyIndexEnd; i++)
	{

		if (w_entityVector[i]->m_alive == false && found == false)
		{
			found = true;
			w_entityVector[i]->m_alive = true;
			w_entityVector[i]->health = 1;
			w_entityVector[i]->route = rand() % 2 + 1;
			if (w_entityVector[i]-> route == 1)
			{
				w_entityVector[i]->posX = 20;
				w_entityVector[i]->posY = 20;
			}
			if (w_entityVector[i]-> route ==2)
			{
				w_entityVector[i]->posX = 100;
				w_entityVector[i]->posY = 100;
			}
			

		}
		if (w_entityVector[i]->m_alive == true && found == false)
		{
			i = i;
		}
	}
}
