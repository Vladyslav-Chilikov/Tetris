#ifndef BLOCK_H
#define BLOCK_H

class Block
{
public:
	Block();
	Block(int x, int y);
	void generate(int x, int y, int col);

	int posX, posY;	// coordinates to define block position in tetromino figure
	int color;
};

#endif // !BLOCK_H

