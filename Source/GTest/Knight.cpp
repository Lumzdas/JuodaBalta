#include "gtest/gtest.h"

#include "Public/Solver.h"
#include "Public/Rules.h"
#include "Public/Enums.h"

#include "StartingBoard.h"

namespace JuodaBalta::Test {
	struct GTestKnightBoard : public FEmptyBoard, public ::testing::Test {
		FCoordinate const KnightCoordinate = FCoordinate(1, 1);
		FCoordinate const RightOfKnightCoordinate = FCoordinate(2, 1);
		FCoordinate const AboveKnightCoordinate = FCoordinate(1, 2);

		FBoard KnightScenario() {
			auto Scenario = FBoard(Board);
			Scenario.Pieces[KnightCoordinate.Index()] = EPiece::WhiteKnight;
			return Scenario;
		}
	};

	TEST_F(GTestKnightBoard, KnightCanPerformManyMoves) {
		FBoards Boards;
		Rules::LegalMoves(Boards, KnightScenario(), KnightCoordinate.Index());

		EXPECT_EQ(Boards.size(), 4);
	}

	TEST_F(GTestKnightBoard, BlockedKnightCanStillPerformManyMoves) {
		FBoard Scenario = KnightScenario();
		Scenario.Pieces[RightOfKnightCoordinate.Index()] = EPiece::BlackKnight;
		Scenario.Pieces[AboveKnightCoordinate.Index()] = EPiece::BlackKnight;

		FBoards Boards;
		Rules::LegalMoves(Boards, Scenario, KnightCoordinate.Index());

		EXPECT_EQ(Boards.size(), 4);
	}
}
