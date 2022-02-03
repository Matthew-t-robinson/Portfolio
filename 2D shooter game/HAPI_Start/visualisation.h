#pragma once

#include "HAPI_lib.h"
using namespace HAPISPACE;

#include <unordered_map>
#include "Rectangle.h"
class sprite;

class Rectangle;

class visualisation
{
	private:
		int m_screenWidth{1024};
		int m_screenHeight{ 768 };
		BYTE* mScreen{ nullptr };
		std::unordered_map<std::string, sprite* > m_spriteMap;
	public:

		~visualisation();

		bool Initialise();
		
		bool CreateSprite(const std::string& spriteName, const std::string& filename);

		void RenderSpriteBG(const std::string& spriteName, float posX, float posY);
		void RenderSpritePlayer(const std::string& spriteName, float posX, float posY);
		
};

