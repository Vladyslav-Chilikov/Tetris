#include "GameField.h"

GameField::GameField()
{
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 22; ++j)
		{
			occupiedPositions[i][j] = -1;
		}
}

void GameField::rowCleaningManager(unsigned long& score)
{
	bool clearCondition = true;
	for (int j = 21; j >= 0; --j)
	{
		for (int i = 9; i >= 0; --i)
		{
			if (occupiedPositions[i][j] == -1) { clearCondition = false; }
		}
		if (clearCondition)
		{
			clearRow(j);
			score += 100;
		}
		else clearCondition = true;
	}
}

void GameField::clearRow(int num)
{
	for (int i = 0; i < 10; ++i)
	{
		occupiedPositions[i][num] = -1;
	}
	for (int j = num; j >= 0; --j)
		for (int i = 0; i < 10; ++i)
		{
			if (j != 0)
				occupiedPositions[i][j] = occupiedPositions[i][j - 1];
			else
				occupiedPositions[i][j] = -1;
		}
}