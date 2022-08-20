#pragma once

#include "Private/Primitives.h"

#include <vector>

namespace JuodaBalta {
	struct FMove;
	struct FCoordinate;
	enum class EPiece : i8;
	enum class EPlayer : i8;

	struct FBoard {
		FBoard() : Pieces() {}

		static i32 constexpr PawnValue = 10;
		static i32 constexpr RookValue = 35;
		static i32 constexpr KnightValue = 33;
		static i32 constexpr BishopValue = 30;
		static i32 constexpr QueenValue = 70;
		static i32 constexpr KingValue = 15000;

		static u8 constexpr NSide = 8;
		static u8 constexpr NPositions = NSide * NSide;

		EPiece Pieces[NPositions];

		FBoard MovePiece(FCoordinate const & From, FCoordinate const & To) const;
		FBoard MovePiece(u8 FromIndex, u8 ToIndex) const;
		FBoard & MovePieceMutate(u8 FromIndex, u8 ToIndex);
		FBoard & PromotePawnMutate(u8 Index, EPiece ToPiece);

		i32 WhiteScore = 0;
		i32 CPUScore = 0;
		i32 Score(EPlayer Player) const;
		static i32 ChessPieceValue(EPiece Piece);

		bool bWhiteQueenCastle = true;
		bool bWhiteKingCastle = true;
		bool bBlackQueenCastle = true;
		bool bBlackKingCastle = true;
		FBoard DisableWhiteCastling() const;
		FBoard DisableBlackCastling() const;

		u8 DoublePushedPawnIndex = 0;

		FMove ToMove(FBoard const & StartingBoard) const;
	};

	typedef std::vector<FBoard> FBoards;
	typedef std::vector<JuodaBalta::FBoard>::iterator FBoardIterator;
}
