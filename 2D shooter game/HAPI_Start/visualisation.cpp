#include "visualisation.h"
#include"sprite.h"
#include"Rectangle.h"
#include <unordered_map>

visualisation::~visualisation()
{
	for (auto& p : m_spriteMap)
		delete p.second;
}

//this intialises the window
bool visualisation::Initialise()
{
	if (!HAPI.Initialise(m_screenWidth, m_screenHeight))
		return false;
	mScreen = HAPI.GetScreenPointer();
	HAPI.GetFPS();
	HAPI.SetShowFPS(true);

	return true;
}

//this creates a new sprite, calls for it to be loaded in the sprite class and then adds it into the sprite map so that it can be rendered later
bool visualisation::CreateSprite(const std::string& spriteName, const std::string& filename)
{
	sprite* newSprite = new sprite();
	if (!newSprite->Load(filename))
	{
		HAPI.UserMessage("Load failed", "ERROR");
		delete newSprite;
		return false;
	}

	m_spriteMap[spriteName] = newSprite;
	return true;
}

//this renders the sprite called from the sprite map
void visualisation::RenderSpriteBG(const std::string& spriteName, float posX, float posY)
{
	mScreen = HAPI.GetScreenPointer();
	if (m_spriteMap.find(spriteName) == m_spriteMap.end())
	{
		HAPI.UserMessage("spritemap failure", "Error");
		return;
	}

	m_spriteMap[spriteName]->RenderBG(mScreen, m_screenWidth, posX, posY);
}
//this renders the sprite called from the sprite map
void visualisation::RenderSpritePlayer(const std::string& spriteName, float posX, float posY)
{
	Rectangle screenRect(0, (float)m_screenWidth, 0, (float)m_screenHeight);
	mScreen = HAPI.GetScreenPointer();
	if (m_spriteMap.find(spriteName) == m_spriteMap.end())
	{
		HAPI.UserMessage("spritemap failure", "Error");
		return;
	}

	m_spriteMap[spriteName]->RenderPlayer(mScreen, posX, posY, screenRect);
}


