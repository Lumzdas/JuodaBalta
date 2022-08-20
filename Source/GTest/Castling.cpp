#include "gtest/gtest.h"

#include "Public/Solver.h"
#include "Public/Rules.h"
#include "Public/Enums.h"

#include "StartingBoard.h"

namespace JuodaBalta::Test {
	struct GTestCastlingBoard : public FEmptyBoard, public ::testing::Test {
		FBoard WhiteCastleScenario() {
			auto Scenario = FBoard(Board);
			Scenario.Pieces[WhiteKingIndex] = EPiece::WhiteKing;
			Scenario.Pieces[WhiteQueenRookIndex] = EPiece::WhiteRook;
			Scenario.Pieces[WhiteKingRookIndex] = EPiece::WhiteRook;
			return Scenario;
		}

		FBoard BlackCastleScenario() {
			auto Scenario = FBoard(Board);
			Scenario.Pieces[BlackKingIndex] = EPiece::BlackKing;
			Scenario.Pieces[BlackQueenRookIndex] = EPiece::BlackRook;
			Scenario.Pieces[BlackKingRookIndex] = EPiece::BlackRook;
			return Scenario;
		}
	};

	TEST_F(GTestCastlingBoard, WhiteKingCanCastle) {
		FBoards Boards;
		Rules::LegalMoves(Boards, WhiteCastleScenario(), WhiteKingIndex);

		EXPECT_EQ(Boards.size(), 5 + 2);
	}

	TEST_F(GTestCastlingBoard, BlackKingCanCastle) {
		FBoards Boards;
		Rules::LegalMoves(Boards, BlackCastleScenario(), BlackKingIndex);

		EXPECT_EQ(Boards.size(), 5 + 2);
	}

	TEST_F(GTestCastlingBoard, WhiteKingCantCastleWhenLeftPathContainsPiece) {
		FBoard Scenario = WhiteCastleScenario();
		Scenario.Pieces[WhiteQueenKnightIndex] = EPiece::WhiteKnight;

		FBoards Boards;
		Rules::LegalMoves(Boards, Scenario, WhiteKingIndex);

		EXPECT_EQ(Boards.size(), 5 + 1);
	}

	TEST_F(GTestCastlingBoard, WhiteKingCantCastleWhenRightPathContainsPiece) {
		FBoard Scenario = WhiteCastleScenario();
		Scenario.Pieces[WhiteKingKnightIndex] = EPiece::WhiteKnight;

		FBoards Boards;
		Rules::LegalMoves(Boards, Scenario, WhiteKingIndex);

		EXPECT_EQ(Boards.size(), 5 + 1);
	}

	TEST_F(GTestCastlingBoard, WhiteKingCantCastleWhenContested) {
		FBoard Scenario = WhiteCastleScenario();
		Scenario.Pieces[BlackKingIndex] = EPiece::BlackRook;

		FBoards Boards;
		Rules::LegalMoves(Boards, Scenario, WhiteKingIndex);

		EXPECT_EQ(Boards.size(), 5);
	}

	TEST_F(GTestCastlingBoard, WhiteKingCantCastleLeftWhenContestedLeft) {
		FBoard Scenario = WhiteCastleScenario();
		Scenario.Pieces[BlackQueenIndex] = EPiece::BlackRook;

		FBoards Boards;
		Rules::LegalMoves(Boards, Scenario, WhiteKingIndex);

		EXPECT_EQ(Boards.size(), 5 + 1);
	}

	TEST_F(GTestCastlingBoard, WhiteKingCantCastleRightWhenContestedRight) {
		FBoard Scenario = WhiteCastleScenario();
		Scenario.Pieces[BlackKingBishopIndex] = EPiece::BlackRook;

		FBoards Boards;
		Rules::LegalMoves(Boards, Scenario, WhiteKingIndex);

		EXPECT_EQ(Boards.size(), 5 + 1);
	}

	TEST_F(GTestCastlingBoard, WhiteKingCanCastleWhenRookContested) {
		FBoard Scenario = WhiteCastleScenario();
		Scenario.Pieces[BlackQueenRookIndex] = EPiece::BlackRook;

		FBoards Boards;
		Rules::LegalMoves(Boards, Scenario, WhiteKingIndex);

		EXPECT_EQ(Boards.size(), 5 + 2);
	}

	TEST_F(GTestCastlingBoard, WhiteKingCantCastleAfterMoving) {
		FBoards KingMoves;
		Rules::LegalMoves(KingMoves, WhiteCastleScenario(), WhiteKingIndex);

		u8 constexpr MoveKingTo = WhiteQueenIndex;

		FBoard Scenario = *std::find_if(KingMoves.begin(), KingMoves.end(), [&](FBoard const & KingMove) {
			return KingMove.Pieces[MoveKingTo] == EPiece::WhiteKing;
		});

		FBoards Boards;
		Rules::LegalMoves(Boards, Scenario, MoveKingTo);

		EXPECT_EQ(Boards.size(), 5);
	}

	TEST_F(GTestCastlingBoard, WhiteKingCantCastleLeftAfterLeftRookMoves) {
		FBoard Scenario = WhiteCastleScenario().MovePiece(WhiteQueenRookIndex, BlackQueenRookIndex);

		FBoards Boards;
		Rules::LegalMoves(Boards, Scenario, WhiteKingIndex);

		EXPECT_EQ(Boards.size(), 6);
	}

	TEST_F(GTestCastlingBoard, WhiteKingCantCastleRightAfterRightRookMoves) {
		FBoard Scenario = WhiteCastleScenario().MovePiece(WhiteKingRookIndex, BlackKingRookIndex);

		FBoards Boards;
		Rules::LegalMoves(Boards, Scenario, WhiteKingIndex);

		EXPECT_EQ(Boards.size(), 6);
	}
}
