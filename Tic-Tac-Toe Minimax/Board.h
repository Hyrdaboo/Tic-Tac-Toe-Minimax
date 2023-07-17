#pragma once
#include <vector>

/// <summary>
/// 0 is X and 1 is O
/// </summary>
class Board
{
private:
	char m_board[9];
	std::vector<int> m_availableCells;

public:
	Board();
	void Print();
	bool MakeMove(int index, int turn);
	bool CheckWin(int& winner);
	bool CheckWin();
	int Evaluate();
	const std::vector<int>& GetAvailableCells() const;
};