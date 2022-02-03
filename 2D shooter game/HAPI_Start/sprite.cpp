#include "sprite.h"
#include "visualisation.h"
#include "Rectangle.h"
#include <unordered_map>
//this loads the sprite so that its ready to be used
bool sprite::Load(const std::string& filename)
{
	if (!HAPI.LoadTexture(filename, &s_texture, s_textureWidth, s_textureHeight))
	{
		//this outputs an error message if the texture can't be loaded 
		HAPI.UserMessage("help", "ERROR");
		return false;
	}
	return true;
}
//this renders the a sprite using basic rendering. It doesnt account for clipping or alpha
void sprite::RenderBG(BYTE* screen, int width, float posX,float posY)
{
    BYTE* tempTexture{ s_texture };
    BYTE* tempScreen{ screen + ((int)posX + (int)posY * (size_t)width) * 4 };
    int endOfLineScreenOffset = (width - s_textureWidth) * 4;

    for (int y = 0; y < s_textureHeight; y++)
    {
        for (int x = 0; x < s_textureWidth; x++)
        {

            memcpy(tempScreen, tempTexture, 4);
            tempTexture += 4;
            tempScreen += 4;
        }
        tempScreen += endOfLineScreenOffset;
    }
}
//this renders a sprite taking account for alpha and for clipping 
void sprite::RenderPlayer(BYTE* screen, float posX, float posY, const Rectangle& screenRect)
{
	Rectangle textureRect(0, (float)s_textureWidth, 0, (float)s_textureHeight);
	Rectangle clippedRect(textureRect);
	clippedRect.Translate(posX, posY);
	clippedRect.ClipTo(screenRect);
	clippedRect.Translate(-posX, -posY);

	if (posX < 0)
		posX = 0;
	if (posY < 0)
		posY = 0;

	BYTE* tempTexture{ s_texture + ((size_t)clippedRect.left + (size_t)clippedRect.top * (size_t)textureRect.Width()) * 4 };
	BYTE* tempScreen{ screen + ((size_t)posX + (size_t)posY * (size_t)screenRect.Width()) * 4 };

	int endOfLineScreenOffset = ((int)screenRect.Width() - (int)clippedRect.Width()) * 4;
	int textureOffSet = ((int)textureRect.Width() - (int)clippedRect.Width()) * 4;


	for (int y = 0; y < clippedRect.Height(); y++)
	{
		for (int x = 0; x < clippedRect.Width(); x++)
		{

			BYTE red = tempTexture[0];
			BYTE green = tempTexture[1];
			BYTE blue = tempTexture[2];
			BYTE alpha = tempTexture[3];
			if (alpha == 255)
			{
				memcpy(tempScreen, tempTexture, 4);
			}
			else if (alpha > 0)
			{
				float mod = alpha / 255.0f;
				tempScreen[0] = (BYTE)(mod * red + (1.0f - mod) * tempScreen[0]);
				tempScreen[1] = (BYTE)(mod * green + (1.0f - mod) * tempScreen[1]);
				tempScreen[2] = (BYTE)(mod * blue + (1.0f - mod) * tempScreen[2]);
			}
			tempTexture += 4;
			tempScreen += 4;
		}
		tempTexture += textureOffSet;
		tempScreen += endOfLineScreenOffset;
	}
}

//this gets the rectangle for a sprite
Rectangle sprite::GetSpriteRectangle(const std::string& fileName)
{
	Load(fileName);
	Rectangle textureBorder(0, (float)s_textureWidth-(s_textureWidth / 10), 0, (float)s_textureHeight-(s_textureHeight / 10));

	return textureBorder;
}

sprite::~sprite()
{
	delete[]s_texture;
}