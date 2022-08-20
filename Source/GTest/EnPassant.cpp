#include "gtest/gtest.h"

#include "Public/Solver.h"
#include "Public/Rules.h"
#include "Public/Enums.h"

#include "StartingBoard.h"

#include <algorithm>

namespace JuodaBalta::Test {
	struct GTestEnPassantBoard : public FEmptyBoard, public ::testing::Test {
		FCoordinate const AttackerCoordinate = FCoordinate(2, 4);
		FCoordinate const VictimStartCoordinate = FCoordinate(3, 6);
		FCoordinate const VictimEndCoordinate = FCoordinate(3, 4);
		FCoordinate const AboveVictimEndCoordinate = FCoordinate(3, 5);

		FBoard EnPassantScenario() {
			auto Scenario = FBoard(Board);
			Scenario.Pieces[AttackerCoordinate.Index()] = EPiece::WhitePawn;
			Scenario.Pieces[VictimStartCoordinate.Index()] = EPiece::BlackPawn;

			FBoards LegalVictimMoves;
			Rules::LegalMoves(LegalVictimMoves, Scenario, VictimStartCoordinate.Index());
			FBoard DoublePush = *std::find_if(LegalVictimMoves.begin(), LegalVictimMoves.end(), [&](FBoard const & LegalBoard) {
				return LegalBoard.Pieces[VictimEndCoordinate.Index()] == EPiece::BlackPawn;
			});

			return DoublePush;
		}
	};

	TEST_F(GTestEnPassantBoard, PawnCanPerformEnPassant) {
		FBoards Boards;
		Rules::LegalMoves(Boards, EnPassantScenario(), AttackerCoordinate.Index());

		EXPECT_EQ(Boards.size(), 2);

		// One of the resultant boards has the black pawn taken
		EXPECT_EQ(
				1,
				std::count_if(Boards.begin(), Boards.end(), [&](FBoard const & LegalBoard) {
					return LegalBoard.Pieces[VictimEndCoordinate.Index()] == EPiece::None;
				})
		);
	}

	TEST_F(GTestEnPassantBoard, PawnCantPerformEnPassantWhenBlocked) {
		FBoard Scenario = EnPassantScenario();
		Scenario.Pieces[0] = EPiece::BlackKnight;
		Scenario.MovePieceMutate(0, AboveVictimEndCoordinate.Index());

		FBoards Boards;
		Rules::LegalMoves(Boards, Scenario, AttackerCoordinate.Index());

		EXPECT_EQ(Boards.size(), 2);

		// None of the resultant boards has the black pawn taken
		EXPECT_EQ(
				0,
				std::count_if(Boards.begin(), Boards.end(), [&](FBoard const & LegalBoard) {
					return LegalBoard.Pieces[VictimEndCoordinate.Index()] == EPiece::None;
				})
		);
	}
}
