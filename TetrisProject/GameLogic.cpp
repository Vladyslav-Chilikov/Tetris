#include "GameLogic.h"

GameLogic::GameLogic() : cellSize(20) { init(); };

GameLogic::~GameLogic()
{
    delete rw;
}

int GameLogic::launch()
{
    sf::Clock clock;
    float time;

    while (rw->isOpen())
    {
        if (gf.occupiedPositions[5 - 1][2 - 1] != -1)
        {
            gameOver();
        }
        time = clock.getElapsedTime().asMicroseconds();
        time = time / 1000;
        if ((time + speed) >= 1000)
        {
            moveVertical();
            clock.restart();
        }

        figureGeneration();
        gf.rowCleaningManager(score);
        render();

        sf::Event event;
        while (rw->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                rw->close();
            if (event.type == sf::Event::KeyPressed && isRunning)   // controls
            {
                if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) { moveHorizontal(-1); }
                if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) { moveVertical(); }
                if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) { moveHorizontal(1); }
                if (event.key.code == sf::Keyboard::R || event.key.code == sf::Keyboard::Space) { rotate(); }
            }
        }
    }
    return 0;
}

void GameLogic::init()
{
    srand(time(NULL));
    isRunning = true;
    speed = 700;
    score = 0;
    activeTetrExpired = true;

    block_textures[0].loadFromFile("assets/square_r.png");
    block_textures[1].loadFromFile("assets/square_g.png");
    block_textures[2].loadFromFile("assets/square_b.png");
    block_textures[3].loadFromFile("assets/square_y.png");
    block_textures[4].loadFromFile("assets/square_p.png");

    nextTetr[0].generate();
    nextTetr[1].generate();
    nextTetr[0].setPosition(20 * cellSize, 5 * cellSize);
    nextTetr[1].setPosition(20 * cellSize, 10 * cellSize);
    rw = new sf::RenderWindow(sf::VideoMode(600, 475), "Tetris");

    sf::Image icon;
    icon.loadFromFile("assets/icon.png");
    rw->setIcon(16, 16, icon.getPixelsPtr());
}

void GameLogic::drawBackground()
{
    sf::RectangleShape field(sf::Vector2f(600, 475));
    sf::Color fieldColor(150, 150, 150, 255);
    field.setFillColor(fieldColor);
    field.setPosition(sf::Vector2f(0, 0));
    rw->draw(field);

    sf::Texture bgSquare;
    bgSquare.loadFromFile("assets/square_bg.png");
    sf::RectangleShape bg(sf::Vector2f(static_cast<float>(cellSize), static_cast<float>(cellSize)));
    bg.setTexture(&bgSquare);
    for (int i = 1; i <= 10; ++i)
    {
        for (int j = 1; j <= 22; ++j)
        {
            bg.setPosition(sf::Vector2f(static_cast<float>(i * cellSize), static_cast<float>(j * cellSize)));
            rw->draw(bg);
        }
    }
}

void GameLogic::figureGeneration()
{
    if (activeTetrExpired && isRunning)  // if current figure have been placed and game needs to create a new one
    {
        activeTetr.transfer(nextTetr[0]);
        if (activeTetr.type)
        {
            activeTetr.setPosition(5 * cellSize, 2 * cellSize);
        }
        else
        {
            activeTetr.setPosition(5 * cellSize, cellSize);
        }
        nextTetr[0].transfer(nextTetr[1]);
        nextTetr[1].generate();
        activeTetrExpired = false;
    }
}

void GameLogic::render()
{
    rw->clear();

    drawBackground();
    drawText();

    drawExistingBlocks();

    drawFigure(activeTetr);
    drawFigure(nextTetr[0]);
    drawFigure(nextTetr[1]);

    rw->display();
}

void GameLogic::drawFigure(Tetromino& fig)
{
    sf::RectangleShape shapeBlock(sf::Vector2f(static_cast<float>(cellSize), static_cast<float>(cellSize)));
    shapeBlock.setTexture(&block_textures[fig.blocks[0].color]);
    for (int i = 0; i < 4; ++i)
    {
        shapeBlock.setPosition(sf::Vector2f(fig.posX + fig.blocks[i].posX * cellSize, fig.posY + fig.blocks[i].posY * cellSize));
        rw->draw(shapeBlock);
    }
}

void GameLogic::moveHorizontal(int direction)
{
    bool moveCondition = true;
    for (Block& block : activeTetr.blocks)
    {
        if (((activeTetr.posX + (block.posX + direction) * cellSize < 1 * cellSize) || (activeTetr.posX + (block.posX + direction) * cellSize > 10 * cellSize)) ||
            (gf.occupiedPositions[activeTetr.posX / cellSize + block.posX - 1 + direction][activeTetr.posY / cellSize + block.posY - 1] != -1))
        {
            moveCondition = false;
        }
    }

    if (moveCondition)
    {
        activeTetr.setPosition(activeTetr.posX + direction * cellSize, activeTetr.posY);
    }
}

void GameLogic::moveVertical()
{
    bool moveCondition = true;
    for (Block& block : activeTetr.blocks)
    {
        if ((activeTetr.posY + (block.posY + 1) * cellSize > 22 * cellSize))
        {
            moveCondition = false;
            activeTetrExpired = true;
        }
    }
    for (Block& block : activeTetr.blocks)
    {
        if ((gf.occupiedPositions[(activeTetr.posX / cellSize + block.posX) - 1][(activeTetr.posY / cellSize + block.posY + 1) - 1] != -1))
        {
            moveCondition = false;
            activeTetrExpired = true;
        }
    }
    if (moveCondition)
    {
        activeTetr.setPosition(activeTetr.posX, activeTetr.posY + 1 * cellSize);
    }

    if (activeTetrExpired)
    {
        for (Block& block : activeTetr.blocks)
        {
            int real_posX = activeTetr.posX / cellSize + block.posX;
            int real_posY = activeTetr.posY / cellSize + block.posY;
            gf.occupiedPositions[real_posX - 1][real_posY - 1] = block.color;
        }
    }
}

void GameLogic::rotate()
{
    Tetromino temp = activeTetr;
    int temp_x, temp_y;
    for (Block& block : activeTetr.blocks)
    {
        temp_x = block.posX * 0 - block.posY * 1;
        temp_y = block.posX * 1 + block.posY * 0;
        block.posX = temp_x;
        block.posY = temp_y;
    }
    bool offsetCondition = false;
    for (Block& block : activeTetr.blocks)
    {
        if (activeTetr.posX + (block.posX * cellSize) < (1 * cellSize))	// if figure block is out of field
        {
            activeTetr.posX += cellSize;
        }
        else if (activeTetr.posX + (block.posX * cellSize) > (10 * cellSize))
        {
            activeTetr.posX -= cellSize;
        }
        if (gf.occupiedPositions[activeTetr.posX / cellSize + block.posX - 1][activeTetr.posY / cellSize + block.posY - 1] != -1)
        {
            offsetCondition = true;
        }
    }

    if (offsetCondition)
    {
        bool offsetR = true, offsetL = true;
        for (Block& block : activeTetr.blocks)
        {
            if (activeTetr.posX + (block.posX * cellSize) == (10 * cellSize)) offsetR = false;
            if (gf.occupiedPositions[activeTetr.posX / cellSize + block.posX - 1 + 1][activeTetr.posY / cellSize + block.posY - 1] != -1)
                offsetR = false;
            if (activeTetr.posX + (block.posX * cellSize) == (1 * cellSize)) offsetL = false;
            if (gf.occupiedPositions[activeTetr.posX / cellSize + block.posX - 1 - 1][activeTetr.posY / cellSize + block.posY - 1] != -1)
                offsetL = false;
        }
        if (offsetR)
        {
            activeTetr.posX += cellSize;
        }
        else if (offsetL)
        {
            activeTetr.posX -= cellSize;
        }
        else
        {
            activeTetr = temp;
        }
    }
}

void GameLogic::drawText()
{
    sf::Font font;
    font.loadFromFile("assets/8bitOperatorPlus8-Bold.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setOutlineThickness(1.5);
    text.setOutlineColor(sf::Color::Black);

    text.setString("Next figure :");
    text.setPosition(sf::Vector2f(15 * cellSize, cellSize));
    rw->draw(text);

    text.setString("Score :");
    text.setPosition(sf::Vector2f(15 * cellSize, 15 * cellSize));
    rw->draw(text);

    text.setString(std::to_string(score));
    text.setPosition(sf::Vector2f(20 * cellSize, 15 * cellSize));
    rw->draw(text);
}

void GameLogic::drawExistingBlocks()
{
    sf::RectangleShape shapeBlock(sf::Vector2f(static_cast<float>(cellSize), static_cast<float>(cellSize)));
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 22; ++j)
        {
            if (gf.occupiedPositions[i][j] != -1)
            {
                shapeBlock.setTexture(&block_textures[gf.occupiedPositions[i][j]]);
                shapeBlock.setPosition(sf::Vector2f((i + 1) * cellSize, (j + 1) * cellSize));
                rw->draw(shapeBlock);
            }
        }
}

void GameLogic::gameOver()
{
    isRunning = false;
}