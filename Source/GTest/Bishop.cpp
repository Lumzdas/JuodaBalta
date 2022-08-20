#include "gtest/gtest.h"

#include "Public/Solver.h"
#include "Public/Rules.h"
#include "Public/Enums.h"

#include "StartingBoard.h"

namespace JuodaBalta::Test {
	struct GTestBishopBoard : public FEmptyBoard, public ::testing::Test {
		FCoordinate const BishopCoordinate = FCoordinate(1, 1);
		FCoordinate const AboveAndRightFromBishopCoordinate = FCoordinate(2, 2);

		FBoard BishopScenario() {
			auto Scenario = FBoard(Board);
			Scenario.Pieces[BishopCoordinate.Index()] = EPiece::WhiteBishop;
			return Scenario;
		}
	};

	TEST_F(GTestBishopBoard, BishopCanPerformManyMoves) {
		FBoards Boards;
		Rules::LegalMoves(Boards, BishopScenario(), BishopCoordinate.Index());

		EXPECT_EQ(Boards.size(), 9);
	}

	TEST_F(GTestBishopBoard, BlockedBishopCanTakeButCantProceed) {
		FBoard Scenario = BishopScenario();
		Scenario.Pieces[AboveAndRightFromBishopCoordinate.Index()] = EPiece::BlackKnight;

		FBoards Boards;
		Rules::LegalMoves(Boards, Scenario, BishopCoordinate.Index());

		EXPECT_EQ(Boards.size(), 4);
	}
}
