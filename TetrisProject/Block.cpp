#include "Block.h"

Block::Block() : posX(0), posY(0), color(0) {}

Block::Block(int x, int y)
{
	generate(x, y, 0);
}

void Block::generate(int x, int y, int col)
{
	posX = x;
	posY = y;
	color = col;

}