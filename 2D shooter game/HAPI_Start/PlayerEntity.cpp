#include "PlayerEntity.h"
void PlayerEntity::Update(visualisation& vis, World& w)
{
	const HAPI_TKeyboardData& keyScan = HAPI.GetKeyboardData();
	const HAPI_TControllerData& controllerScan = HAPI.GetControllerData(0);
	if (health <= 0)
	{
		m_alive = false;
	}
	if (m_alive)
	{
		//this calls the render for the player sprite
		vis.RenderSpritePlayer("PlayerSprite", posX, posY);
		//this takes the controller and keyboard inputs for the program
		if (keyScan.scanCode['W'] && keyScan.scanCode['A'])
		{
			if (posY == 0)
			{
				posX -= 4;
			}
			else
			{
				posX -= 4;
				posY -= 4;
			}

		}
		else if (keyScan.scanCode['W'] && keyScan.scanCode['D'])
		{
			posY -= 4;
			posX += 4;
		}
		else if (keyScan.scanCode['S'] && keyScan.scanCode['A'])
		{
			posY += 4;
			posX -= 4;
		}
		else if (keyScan.scanCode['S'] && keyScan.scanCode['D'])
		{
			posY += 4;
			posX += 4;
		}
		else if (keyScan.scanCode['W'])
		{
			posY -= 5;
		}
		else if (keyScan.scanCode['S'])
		{
			posY += 5;
		}
		else if (keyScan.scanCode['A'])
		{
			posX -= 5;
		}
		else if (keyScan.scanCode['D'])
		{
			posX += 5;
		}
		if ((controllerScan.isAttached && controllerScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > 15000) && (controllerScan.isAttached && controllerScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 15000))
		{
			posY -= 4;
			posX += 4;
		}
		else if ((controllerScan.isAttached && controllerScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 15000) && (controllerScan.isAttached && controllerScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -15000))
		{
			posX += 4;
			posY += 4;
		}
		else if ((controllerScan.isAttached && controllerScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -15000) && (controllerScan.isAttached && controllerScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > 15000))
		{
			posX -= 4;
			posY -= 4;
		}
		else if ((controllerScan.isAttached && controllerScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -15000) && (controllerScan.isAttached && controllerScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -15000))
		{
			posX -= 4;
			posY += 4;
		}
		else if (controllerScan.isAttached && controllerScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > 30000)
		{
			posY -= 5;
		}
		else if (controllerScan.isAttached && controllerScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 30000)
		{
			posX += 5;
		}
		else if (controllerScan.isAttached && controllerScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -30000)
		{
			posX -= 5;
		}
		else if (controllerScan.isAttached && controllerScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -30000)
		{
			posY += 5;
		}
		//this makes the controller rumble when it gets to the middle of the screen
		if ((posX > 482 && posY > 354 && posX < 542 && posY < 414))
		{
			HAPI.SetControllerRumble(0, 65535, 65535);
		}
		else
		{
			HAPI.SetControllerRumble(0, 0, 0);
		}
		//this fires the bullet if a is pressed on the controller and it is not held
		if ((controllerScan.isAttached && controllerScan.digitalButtons[HK_DIGITAL_A]) && w.aHeld == false)
		{
			w.fireBullet(true, posX, w.w_entityVector[0]->posY);
			w.aHeld = true;
		}
		if (controllerScan.isAttached && (controllerScan.digitalButtons[HK_DIGITAL_A] == false))
		{
			w.aHeld = false;
		}
		//this fires the bullet if space is pressed on the controller and it is not held
		if (keyScan.scanCode[HK_SPACE] && w.spaceHeld == false)
		{
			w.fireBullet(true, posX, w.w_entityVector[0]->posY);
			w.spaceHeld = true;
		}
		if ((keyScan.scanCode[HK_SPACE]) == false)
		{
			w.spaceHeld = false;
		}
		//this resets the game if b is pressed on the controller
		if (controllerScan.isAttached && controllerScan.digitalButtons[HK_DIGITAL_B])
		{
			for (size_t i = 1; i < w.w_entityVector.size(); i++)
			{
				w.w_entityVector[i]->m_alive = false;
				w.w_entityVector[i]->posX = 0;
				w.w_entityVector[i]->posY = 0;
				w.w_entityVector[i]->health = 1;
			}
			m_alive = true;
			health = 10;
			posX = 512;
			posY = 600;
			w.CurrentScore = 0;
			
		}
		//this resets the game if R is pressed on the keyboard
		if (keyScan.scanCode['R'])
		{
			for (size_t i = 1; i < w.w_entityVector.size(); i++)
			{
				w.w_entityVector[i]->m_alive = false;
				w.w_entityVector[i]->posX = 0;
				w.w_entityVector[i]->posY = 0;
				w.w_entityVector[i]->health = 1;
			}
			w.w_entityVector[0]->m_alive = true;
			w.w_entityVector[0]->health = 10;
			w.w_entityVector[0]->posX = 512;
			w.w_entityVector[0]->posY = 600;
			w.CurrentScore = 0;
		}
	}
}

void PlayerEntity::SetBullet(Side side, float changingPosX, float changingPosY)
{
}
