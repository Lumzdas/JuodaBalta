#include "gtest/gtest.h"

#include "Public/Rules.h"
#include "Public/Enums.h"

#include "StartingBoard.h"

namespace JuodaBalta::Test {
	struct GTestStartingBoard : public FStartingBoard, public ::testing::Test {};

	TEST_F(GTestStartingBoard, FirstTurnContains20Moves) {
		FBoards Boards;
		Rules::LegalMoves(Boards, Board, EPlayer::White);

		EXPECT_EQ(Boards.size(), 20);
	}
}
