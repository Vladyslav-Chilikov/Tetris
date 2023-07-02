#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <random>

#include <SFML/Graphics.hpp>

#include "Tetromino.h"
#include "GameField.h"

class GameLogic
{
public:
    GameLogic();
    ~GameLogic();
    void render();
	int launch();   // to start the game
	void init();    // basic initialization
    void figureGeneration();

    void drawBackground();
    void drawFigure(Tetromino& fig);
    void drawText();
    void drawExistingBlocks();

    void moveHorizontal(int direction);  // move the figure by x
    void moveVertical();    // move the figure by y axxis
    void rotate();

    void gameOver();
  
	int speed;
    const int cellSize;   // amount of pixels per 1 in game cell
	unsigned long score;   
	
    bool isRunning; // game loop
    bool activeTetrExpired;

	Tetromino activeTetr;
	Tetromino nextTetr[2];

    GameField gf; // represents blocks and cells on field
    sf::RenderWindow* rw;

    sf::Texture block_textures[5];
};

#endif // !GAME_LOGIC_H
