#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <random>
#include "Board.h"

std::vector<std::string> splitString(const std::string& input, char delimiter)
{
	std::vector<std::string> tokens;
	std::stringstream ss(input);
	std::string token;

	while (std::getline(ss, token, delimiter))
	{
		tokens.push_back(token);
	}

	return tokens;
}

int getRandomNumber(int min, int max)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> distribution(min, max-1);
	return distribution(rng);
}

std::pair<int, int> Minimax(Board board, int depth, bool isMaximizing)
{
	if (depth == 0 || board.CheckWin() || board.GetAvailableCells().size() == 0)
	{
		return std::make_pair(board.Evaluate(), 69);
	}

	if (isMaximizing)
	{
		int maxIndex = 0;
		int maxEval = INT_MIN;
		for (auto i : board.GetAvailableCells())
		{
			Board copyBoard = board;
			copyBoard.MakeMove(i, 0);
			auto eval = Minimax(copyBoard, depth - 1, false);
			if (eval.first > maxEval)
			{
				maxEval = eval.first;
				maxIndex = i;
			}
		}
		return std::make_pair(maxEval, maxIndex);
	}
	else
	{
		int minEval = INT_MAX;
		int minIndex = 0;
		for (auto i : board.GetAvailableCells())
		{
			Board copyBoard = board;
			copyBoard.MakeMove(i, 1);
			auto eval = Minimax(copyBoard, depth - 1, true);
			if (eval.first < minEval)
			{
				minEval = eval.first;
				minIndex = i;
			}
		}
		return std::make_pair(minEval, minIndex);
	}
}

void RandomMoveAI(Board& board, int turn)
{
	int len = board.GetAvailableCells().size();
	if (len == 0)
		return;

	int i = getRandomNumber(0, len);
	int index = board.GetAvailableCells()[i];
	board.MakeMove(index, turn);
}

void SmartAI(Board& board, int turn)
{
	int len = board.GetAvailableCells().size();
	if (len == 0)
		return;

	bool maximizing = turn == 0 ? true : false;
	int index = Minimax(board, 8, maximizing).second;
	board.MakeMove(index, turn);
}

static bool printIntro = true;
int main()
{
	if (printIntro)
	{
		std::cout << "+------------------------------------+\n\n";
		std::cout << "| Welcome to the game of TIC TAC TOE |\n\n";
		std::cout << "+------------------------------------+\n\n";

		std::cout << "Your input should match an index on the board as shown below.\n\n";
		std::cout << " 0 | 1 | 2\n";
		std::cout << "---+---+---\n";
		std::cout << " 3 | 4 | 5\n";
		std::cout << "---+---+---\n";
		std::cout << " 6 | 7 | 8\n\n\n";

		printIntro = false;
	}

	int player = -1;
	bool smart = false;
	while (true)
	{
		std::cout << "Choose your role. You play as [0]X [1]O: ";
		std::cin >> player;

		bool fail = std::cin.fail();
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		
		if (fail || player < 0 || player > 1)
		{
			std::cout << "Wrong token!" << std::endl;
			continue;
		}

		std::cout << "Choose AI difficulty. Easy[0] Hard[1]: ";
		std::cin >> smart;

		std::cout << std::endl;
		break;
	}

	auto msg = smart ? "Hard" : "Easy";
	std::cout << "\nDifficulty: " << msg << std::endl;
	
	// Game Loop
	Board board;
	int turn = 0;
	int winner = -1;
	while (true)
	{
		if (turn == player)
		{
			board.Print();
			int index;
			std::cout << "Make your move: ";
			std::cin >> index;

			bool fail = std::cin.fail();
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			if (fail || index < 0 || index > 9)
			{
				std::cout << "Wrong token" << std::endl;
				continue;
			}

			if (!board.MakeMove(index, turn))
			{
				std::cout << "\nOccupied position!" << std::endl;
				continue;
			}
		}
		else
		{
			std::cout << "\nComputer made its move" << std::endl;
			if (smart)
				SmartAI(board, 1 - player);
			else
				RandomMoveAI(board, 1 - player);
		}

		if (board.CheckWin(winner) || board.GetAvailableCells().size() == 0)
			break;
		turn++;
		turn %= 2;
	}

	board.Print();
	std::string winnerMsg;
	if (winner == player)
		winnerMsg = "You win!";
	else if (winner == 1 - player)
		winnerMsg = "Computer wins!";
	else
		winnerMsg = "Draw!";
	std::cout << std::endl << winnerMsg << std::endl;

	std::cout << "\n\nPlay again? [y/n]: ";
	char choice;
	std::cin >> choice;
	if (choice == 'y' || choice == 'Y')
	{
		main();
	}
}