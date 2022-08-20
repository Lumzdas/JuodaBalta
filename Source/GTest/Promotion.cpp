#include "gtest/gtest.h"

#include "Public/Rules.h"
#include "Public/Enums.h"

#include "StartingBoard.h"

#include <algorithm>

namespace JuodaBalta::Test {
	struct GTestPawnPromotionBoard : public FEmptyBoard, public ::testing::Test {
		FCoordinate FarFromEndCoordinate = FCoordinate(0, 2);
		FCoordinate FarFromEndMoveCoordinate = FCoordinate(0, 3);
		FCoordinate NearEndCoordinate = FCoordinate(0, 6);
		FCoordinate NearEndMoveCoordinate = FCoordinate(0, 7);

		FBoard PromotionScenario() {
			auto Scenario = FBoard(Board);
			Scenario.Pieces[NearEndCoordinate.Index()] = EPiece::WhitePawn;
			return Scenario;
		}

		FBoard NonPromotionScenario() {
			auto Scenario = FBoard(Board);
			Scenario.Pieces[FarFromEndCoordinate.Index()] = EPiece::WhitePawn;
			return Scenario;
		}
	};

	TEST_F(GTestPawnPromotionBoard, PawnPromotesToFourVariants) {
		FBoards Boards;
		Rules::LegalMoves(Boards, PromotionScenario(), EPlayer::White);

		EXPECT_EQ(Boards.size(), 4);

		// None of the resultant boards contain a pawn
		EXPECT_EQ(
			0,
			std::count_if(Boards.begin(), Boards.end(), [&](FBoard const & LegalBoard) {
				return LegalBoard.Pieces[NearEndMoveCoordinate.Index()] == EPiece::WhitePawn;
			})
		);
	}

	TEST_F(GTestPawnPromotionBoard, PawnIsNotPromotedWhenNotApproachingEnd) {
		FBoards Boards;
		Rules::LegalMoves(Boards, NonPromotionScenario(), EPlayer::White);

		EXPECT_EQ(Boards.size(), 1);

		// Result contains a single pawn
		EXPECT_EQ(
				1,
				std::count_if(Boards.begin(), Boards.end(), [&](FBoard const & LegalBoard) {
					return LegalBoard.Pieces[FarFromEndMoveCoordinate.Index()] == EPiece::WhitePawn;
				})
		);
	}
}
