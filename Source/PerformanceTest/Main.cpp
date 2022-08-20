#include "Public/Solver.h"
#include "Public/Enums.h"

#include "StartingBoard.h"

#include <iostream>

using namespace JuodaBalta;

int main() {
	FSolver Solver(Test::FStartingBoard().Board, EPlayer::White, 9);
	std::cout << "Searching for best move..." << std::endl;
	Solver.BestMove();
}
