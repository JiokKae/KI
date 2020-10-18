#include "SmallBox.h"

void SmallBox::Init(BigBox* _parent)
{
	position.x = BIGBOX_MARGIN + BIGBOX_SIZE / 4;
	position.y = BIGBOX_MARGIN + BIGBOX_SIZE / 4;
	width = BIGBOX_SIZE / 2;
	height = BIGBOX_SIZE / 2;
	parent = _parent;
}

void SmallBox::ChangeParent(BigBox* _parent)
{
	if (GAMEMODE & BOX_CHANGE)
	{
		parent = _parent;
		width = _parent->GetWidth() / 2;
		height = _parent->GetHeight() / 2;
	}
	
}