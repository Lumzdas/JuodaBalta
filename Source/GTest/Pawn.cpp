#include "gtest/gtest.h"

#include "Public/Solver.h"
#include "Public/Rules.h"
#include "Public/Enums.h"

#include "StartingBoard.h"

namespace JuodaBalta::Test {
	struct GTestPawnBoard : public FEmptyBoard, public ::testing::Test {
		FCoordinate PawnCoordinate = FCoordinate(3, 1);
		FCoordinate PushedPawnCoordinate = FCoordinate(3, 2);
		FCoordinate DoublePushedPawnCoordinate = FCoordinate(3, 3);
		FCoordinate PawnTakeLeftCoordinate = FCoordinate(2, 2);
		FCoordinate PawnTakeRightCoordinate = FCoordinate(4, 2);

		FBoard PawnAtStartScenario() {
			auto Scenario = FBoard(Board);
			Scenario.Pieces[PawnCoordinate.Index()] = EPiece::WhitePawn;
			return Scenario;
		}
	};

	TEST_F(GTestPawnBoard, PawnCanDoublePushFromStart) {
		FBoards Boards;
		Rules::LegalMoves(Boards, PawnAtStartScenario(), PawnCoordinate.Index());

		EXPECT_EQ(Boards.size(), 2);
	}

	TEST_F(GTestPawnBoard, PawnCantDoublePushFromElsewhere) {
		FBoards Boards;
		Rules::LegalMoves(
				Boards,
				PawnAtStartScenario().MovePiece(PawnCoordinate, PushedPawnCoordinate),
				PushedPawnCoordinate.Index());

		EXPECT_EQ(Boards.size(), 1);
	}

	TEST_F(GTestPawnBoard, PawnCantPushWhenBlocked) {
		FBoard Scenario = PawnAtStartScenario();
		Scenario.Pieces[PushedPawnCoordinate.Index()] = EPiece::BlackKnight;

		FBoards Boards;
		Rules::LegalMoves(Boards, Scenario, PawnCoordinate.Index());

		EXPECT_EQ(Boards.size(), 0);
	}

	TEST_F(GTestPawnBoard, PawnCantDoublePushWhenBlocked) {
		FBoard Scenario = PawnAtStartScenario();
		Scenario.Pieces[DoublePushedPawnCoordinate.Index()] = EPiece::BlackKnight;

		FBoards Boards;
		Rules::LegalMoves(Boards, Scenario, PawnCoordinate.Index());

		EXPECT_EQ(Boards.size(), 1);
	}

	TEST_F(GTestPawnBoard, PawnCanTakeLeft) {
		FBoard Scenario = PawnAtStartScenario();
		Scenario.Pieces[PawnTakeLeftCoordinate.Index()] = EPiece::BlackKnight;

		FBoards Boards;
		Rules::LegalMoves(Boards, Scenario, PawnCoordinate.Index());

		EXPECT_EQ(Boards.size(), 2 + 1);
	}

	TEST_F(GTestPawnBoard, PawnCanTakeRight) {
		FBoard Scenario = PawnAtStartScenario();
		Scenario.Pieces[PawnTakeRightCoordinate.Index()] = EPiece::BlackKnight;

		FBoards Boards;
		Rules::LegalMoves(Boards, Scenario, PawnCoordinate.Index());

		EXPECT_EQ(Boards.size(), 2 + 1);
	}
}
