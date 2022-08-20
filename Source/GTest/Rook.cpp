#include "gtest/gtest.h"

#include "Public/Solver.h"
#include "Public/Rules.h"
#include "Public/Enums.h"

#include "StartingBoard.h"

namespace JuodaBalta::Test {
	struct GTestRookBoard : public FEmptyBoard, public ::testing::Test {
		FCoordinate const RookCoordinate = FCoordinate(0, 0);
		FCoordinate const RightOfRookCoordinate = FCoordinate(1, 0);
		FCoordinate const AboveRookCoordinate = FCoordinate(0, 1);

		FBoard RookScenario() {
			auto Scenario = FBoard(Board);
			Scenario.Pieces[RookCoordinate.Index()] = EPiece::WhiteRook;
			return Scenario;
		}
	};

	TEST_F(GTestRookBoard, RookCanPerform14Moves) {
		FBoards Boards;
		Rules::LegalMoves(Boards, RookScenario(), RookCoordinate.Index());

		EXPECT_EQ(Boards.size(), 14);
	}

	TEST_F(GTestRookBoard, BlockedRookCanTakeButCantProceed) {
		FBoard Scenario = RookScenario();
		Scenario.Pieces[RightOfRookCoordinate.Index()] = EPiece::BlackKnight;
		Scenario.Pieces[AboveRookCoordinate.Index()] = EPiece::BlackKnight;

		FBoards Boards;
		Rules::LegalMoves(Boards, Scenario, RookCoordinate.Index());

		EXPECT_EQ(Boards.size(), 2);
	}
}
