#include "TextureClip.h"

namespace ctm
{

//Constructor
TextureClip::TextureClip()
{}

TextureClip::TextureClip(Texture *Source, const Texture::Coordinate &TopLeft, const Texture::Coordinate &BottomRight):
source(Source),
topleft(TopLeft),
bottomright(BottomRight)
{}

//Set
void TextureClip::Set(Texture *Source, const Texture::Coordinate &TopLeft, const Texture::Coordinate &BottomRight)
{
	source = Source;
	topleft = TopLeft;
	bottomright = BottomRight;
}

//Get Source
const Texture &TextureClip::GetSource()
{
	return *source;
}

//Get Top Left
const Texture::Coordinate &TextureClip::GetTopLeft()
{
	return topleft;
}

//Get Bottom Right
const Texture::Coordinate &TextureClip::GetBottomRight()
{
	return bottomright;
}

//Use
void TextureClip::Use()
{
	source->Use(topleft, bottomright);
}

//Cleanup
void TextureClip::Cleanup()
{
	source->Cleanup();
}

}