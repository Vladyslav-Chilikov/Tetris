#ifndef GAME_FIELD_H
#define GAME_FIELD_H

class GameField
{
public:
	GameField();
	void rowCleaningManager(unsigned long& score);

	int occupiedPositions[10][22];

private:
	void clearRow(int num);
};

#endif // !GAME_FIELD_H

