#include "Tetromino.h"

Tetromino::Tetromino() : color(0), posX(0), posY(0), type(0) {};

void Tetromino::generate()
{
	color = rand() % 5;
	type = rand() % 7;
	setBlocks();
};

void Tetromino::setPosition(int x, int y)
{
	posX = x;
	posY = y;
}

void Tetromino::transfer(Tetromino& obj)
{
	std::swap(type, obj.type);
	std::swap(color, obj.color);
	std::swap(blocks, obj.blocks);
}

void Tetromino::setBlocks()
{
	switch (type)
	{
	case 0: // I
	{
		blocks[0].generate(0, 0, color);
		blocks[1].generate(-1, 0, color);
		blocks[2].generate(1, 0, color);
		blocks[3].generate(2, 0, color);
		break;
	}
	case 1: // O
	{
		blocks[0].generate(0, 0, color);
		blocks[1].generate(1, -1, color);
		blocks[2].generate(0, -1, color);
		blocks[3].generate(1, 0, color);
		break;
	}
	case 2: // T
	{
		blocks[0].generate(0, 0, color);
		blocks[1].generate(-1, 0, color);
		blocks[2].generate(1, 0, color);
		blocks[3].generate(0, -1, color);
		break;
	}
	case 3: // S
	{
		blocks[0].generate(0, 0, color);
		blocks[1].generate(-1, 0, color);
		blocks[2].generate(1, -1, color);
		blocks[3].generate(0, -1, color);
		break;
	}
	case 4: // Z
	{
		blocks[0].generate(0, 0, color);
		blocks[1].generate(1, 0, color);
		blocks[2].generate(-1, 0, color);
		blocks[3].generate(-1, -1, color);
		break;
	}
	case 5: // J
	{
		blocks[0].generate(0, 0, color);
		blocks[1].generate(-1, 0, color);
		blocks[2].generate(1, 0, color);
		blocks[3].generate(-1, -1, color);
		break;
	}
	case 6: // L
	{
		blocks[0].generate(0, 0, color);
		blocks[1].generate(-1, 0, color);
		blocks[2].generate(1, 0, color);
		blocks[3].generate(1, -1, color);
		break;
	}
	default:
		break;
	}
}