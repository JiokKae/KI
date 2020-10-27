#include "Block.h"

HRESULT Block::Init()
{
	pos = {};
	width = 40;
	height = 20;
	isAlive = false;

	return S_OK;
}

void Block::Release()
{
}

void Block::Update()
{

}

void Block::Render(HDC hdc)
{
	if (isAlive) 
	{
		Rectangle(hdc, pos.x, pos.y, pos.x + width, pos.y + height);
	}
		
}

void Block::Appear(POINT pos)
{
	if (!isAlive)
	{
		this->pos = pos;
		isAlive = true;
	}
}
