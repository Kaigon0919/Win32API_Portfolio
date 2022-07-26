#include "stdafx.h"
#include "GameSprite.h"


GameSprite::GameSprite(GameImage* const _image, const Vector2f _pos,const Vector2f _size) : m_Image(_image), m_Rect(_pos,_size)
{

}


GameSprite::~GameSprite()
{
}
