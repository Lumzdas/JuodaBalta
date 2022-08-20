#include "gtest/gtest.h"

#include "Public/Solver.h"
#include "Public/Rules.h"
#include "Public/Enums.h"

#include "StartingBoard.h"

namespace JuodaBalta::Test {
	struct GTestQueenBoard : public FEmptyBoard, public ::testing::Test {
		FCoordinate const QueenCoordinate = FCoordinate(1, 1);
		FCoordinate const AboveAndRightFromQueenCoordinate = FCoordinate(2, 2);
		FCoordinate const RightOfQueenCoordinate = FCoordinate(2, 1);
		FCoordinate const AboveQueenCoordinate = FCoordinate(1, 2);

		FBoard QueenScenario() {
			auto Scenario = FBoard(Board);
			Scenario.Pieces[QueenCoordinate.Index()] = EPiece::WhiteQueen;
			return Scenario;
		}
	};

	TEST_F(GTestQueenBoard, QueenCanPerformManyMoves) {
		FBoards Boards;
		Rules::LegalMoves(Boards, QueenScenario(), QueenCoordinate.Index());

		EXPECT_EQ(Boards.size(), 23);
	}

	TEST_F(GTestQueenBoard, BlockedQueenCanTakeButCantProceed) {
		FBoard Scenario = QueenScenario();
		Scenario.Pieces[AboveAndRightFromQueenCoordinate.Index()] = EPiece::BlackKnight;
		Scenario.Pieces[RightOfQueenCoordinate.Index()] = EPiece::BlackKnight;
		Scenario.Pieces[AboveQueenCoordinate.Index()] = EPiece::BlackKnight;

		FBoards Boards;
		Rules::LegalMoves(Boards, Scenario, QueenCoordinate.Index());

		EXPECT_EQ(Boards.size(), 8);
	}
}
