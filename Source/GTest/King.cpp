#include "gtest/gtest.h"

#include "Public/Solver.h"
#include "Public/Rules.h"
#include "Public/Enums.h"

#include "StartingBoard.h"

namespace JuodaBalta::Test {
	struct GTestKingBoard : public FEmptyBoard, public ::testing::Test {
		FCoordinate const KingCoordinate = FCoordinate(0, 0);
		FCoordinate const RightOfKingCoordinate = FCoordinate(1, 0);
		FCoordinate const AboveKingCoordinate = FCoordinate(0, 1);

		FBoard KingScenario() {
			auto Scenario = FBoard(Board);
			Scenario.Pieces[KingCoordinate.Index()] = EPiece::WhiteKing;
			Scenario.bWhiteKingCastle = false; // This woud happen organically in a normal game
			Scenario.bWhiteQueenCastle = false; // This woud happen organically in a normal game
			return Scenario;
		}
	};

	TEST_F(GTestKingBoard, KingCanPerformManyMoves) {
		FBoards Boards;
		Rules::LegalMoves(Boards, KingScenario(), KingCoordinate.Index());

		EXPECT_EQ(Boards.size(), 3);
	}

	TEST_F(GTestKingBoard, BlockedKingCanStillPerformManyMoves) {
		FBoard Scenario = KingScenario();
		Scenario.Pieces[RightOfKingCoordinate.Index()] = EPiece::BlackKnight;
		Scenario.Pieces[AboveKingCoordinate.Index()] = EPiece::BlackKnight;

		FBoards Boards;
		Rules::LegalMoves(Boards, Scenario, KingCoordinate.Index());

		EXPECT_EQ(Boards.size(), 3);
	}
}
