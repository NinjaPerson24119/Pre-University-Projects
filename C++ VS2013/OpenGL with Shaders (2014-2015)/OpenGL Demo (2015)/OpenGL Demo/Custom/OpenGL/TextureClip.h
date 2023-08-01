#ifndef CTM_TEXTURECLIP_H
#define CTM_TEXTURECLIP_H

#include "Material.h"
#include "Texture.h"

namespace ctm
{

//////
//Texture Clip
class TextureClip : Material
{
public:
	//Base
		TextureClip();
		TextureClip(Texture *Source, const Texture::Coordinate &TopLeft, const Texture::Coordinate &BottomRight);
	//Set
		void Set(Texture *Source, const Texture::Coordinate &TopLeft, const Texture::Coordinate &BottomRight);
	//Get
		const Texture &GetSource();
		const Texture::Coordinate &GetTopLeft();
		const Texture::Coordinate &GetBottomRight();
	//Use
		void Use();
		void Cleanup();
private:
	Texture::Coordinate topleft, bottomright;
	Texture *source;
};
//////

}

#endif