#ifndef TETROMINO_H
#define TETROMINO_H

#include <utility>

#include "Block.h"

class Tetromino
{
public:
	Tetromino();
	void generate();
	void setPosition(int x, int y);
	void transfer(Tetromino& obj);
	void setBlocks();

	int type; // I, O, T, S, Z, J, L
	int color; // R, G, B, Y, P
	int posX, posY;	// figure position on game field
	Block blocks[4];
};

#endif // !TETROMINO_H
