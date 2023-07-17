#include <iostream>
#include "Board.h"

Board::Board()
{
	for (int i = 0; i < 9; i++)
	{
		m_board[i] = ' ';
		m_availableCells.push_back(i);
	}
}

void Board::Print()
{
	std::cout << "\n\n";
	std::cout << ' ' << m_board[0] << ' ' << "|" << ' ' << m_board[1] << ' ' << "|" << ' ' << m_board[2] << std::endl;
	std::cout << "---+---+---" << std::endl;
	std::cout << ' ' << m_board[3] << ' ' << "|" << ' ' << m_board[4] << ' ' << "|" << ' ' << m_board[5] << std::endl;
	std::cout << "---+---+---" << std::endl;
	std::cout << ' ' << m_board[6] << ' ' << "|" << ' ' << m_board[7] << ' ' << "|" << ' ' << m_board[8] << std::endl;
	std::cout << "\n\n";
}

bool Board::MakeMove(int index, int turn)
{
	if (index < 0 || index >= 9)
	{
		std::cerr << "Index out of bounds!" << std::endl;
		return false;
	}
	if (m_board[index] != ' ')
	{
		std::cout << "The index is already occupied!" << std::endl;
		return false;
	}

	char c = turn == 0 ? 'X' : 'O';
	m_board[index] = c;
	m_availableCells.erase(std::remove(m_availableCells.begin(), m_availableCells.end(), index), m_availableCells.end());
	return true;
}

bool Board::CheckWin(int& winner)
{
	auto check3 = [this, &winner](int index1, int index2, int index3) -> bool
	{
		if (((m_board[index1] == m_board[index2]) && (m_board[index2] == m_board[index3])) && m_board[index1] != ' ')
		{
			winner = m_board[index1] == 'X' ? 0 : 1;
			return true;
		}
		return false;
	};

	//horizontal
	if (check3(0, 1, 2))
		return true;
	if (check3(3, 4, 5))
		return true;
	if (check3(6, 7, 8))
		return true;

	//vertical
	if (check3(0, 3, 6))
		return true;
	if (check3(1, 4, 7))
		return true;
	if (check3(2, 5, 8))
		return true;

	//diagonal
	if (check3(0, 4, 8))
		return true;
	if (check3(2, 4, 6))
		return true;

	return false;
}

bool Board::CheckWin()
{
	auto check3 = [this](int index1, int index2, int index3) -> bool
	{
		if (((m_board[index1] == m_board[index2]) && (m_board[index2] == m_board[index3])) && m_board[index1] != ' ')
		{
			return true;
		}
		return false;
	};

	//horizontal
	if (check3(0, 1, 2))
		return true;
	if (check3(3, 4, 5))
		return true;
	if (check3(6, 7, 8))
		return true;

	//vertical
	if (check3(0, 3, 6))
		return true;
	if (check3(1, 4, 7))
		return true;
	if (check3(2, 5, 8))
		return true;

	//diagonal
	if (check3(0, 4, 8))
		return true;
	if (check3(2, 4, 6))
		return true;

	return false;
}

int Board::Evaluate()
{
	int winner = -1;
	bool win = CheckWin(winner);

	if (!win)
	{
		return 0;
	}
	else
	{
		return winner == 0 ? 1 : -1;
	}
}

const std::vector<int>& Board::GetAvailableCells() const
{
	return m_availableCells;
}