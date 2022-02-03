#pragma once
#include "HAPI_lib.h"
#include "Rectangle.h"
#include <unordered_map>
using namespace HAPISPACE;

class sprite
{
	private:
		BYTE* s_texture{ nullptr };
		int s_textureWidth;
		int s_textureHeight;
	public:
		bool Load(const std::string& filename);
		void RenderBG(BYTE* screen, int width, float posX, float posY);
		void RenderPlayer(BYTE* screen, float posX, float posY, const Rectangle& screenRect);
		Rectangle GetSpriteRectangle(const std::string& fileName);
		~sprite();
};

