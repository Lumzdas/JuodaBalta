#pragma once

#include "Public/Coordinate.h"
#include "Public/Enums.h"

namespace JuodaBalta::Test {
	u8 constexpr WhiteQueenRookIndex = FCoordinate::Index(0, 0);
	u8 constexpr WhiteQueenKnightIndex = FCoordinate::Index(1, 0);
	u8 constexpr WhiteQueenBishopIndex = FCoordinate::Index(2, 0);
	u8 constexpr WhiteQueenIndex = FCoordinate::Index(3, 0);
	u8 constexpr WhiteKingIndex = FCoordinate::Index(4, 0);
	u8 constexpr WhiteKingBishopIndex = FCoordinate::Index(5, 0);
	u8 constexpr WhiteKingKnightIndex = FCoordinate::Index(6, 0);
	u8 constexpr WhiteKingRookIndex = FCoordinate::Index(7, 0);

	u8 constexpr BlackQueenRookIndex = FCoordinate::Index(0, 7);
	u8 constexpr BlackQueenKnightIndex = FCoordinate::Index(1, 7);
	u8 constexpr BlackQueenBishopIndex = FCoordinate::Index(2, 7);
	u8 constexpr BlackQueenIndex = FCoordinate::Index(3, 7);
	u8 constexpr BlackKingIndex = FCoordinate::Index(4, 7);
	u8 constexpr BlackKingBishopIndex = FCoordinate::Index(5, 7);
	u8 constexpr BlackKingKnightIndex = FCoordinate::Index(6, 7);
	u8 constexpr BlackKingRookIndex = FCoordinate::Index(7, 7);

	struct FEmptyBoard {
		FBoard Board;
	};

	struct FStartingBoard : public FEmptyBoard {
		FStartingBoard() : FEmptyBoard() {
			for (u8 i = FCoordinate::Index(0, 1); i <= FCoordinate::Index(7, 1); i++)
				Board.Pieces[i] = EPiece::WhitePawn;
			for (u8 i = FCoordinate::Index(0, 6); i <= FCoordinate::Index(7, 6); i++)
				Board.Pieces[i] = EPiece::BlackPawn;

			Board.Pieces[WhiteQueenRookIndex]   = EPiece::WhiteRook;
			Board.Pieces[WhiteQueenKnightIndex] = EPiece::WhiteKnight;
			Board.Pieces[WhiteQueenBishopIndex] = EPiece::WhiteBishop;
			Board.Pieces[WhiteQueenIndex]       = EPiece::WhiteQueen;
			Board.Pieces[WhiteKingIndex]        = EPiece::WhiteKing;
			Board.Pieces[WhiteKingBishopIndex]  = EPiece::WhiteBishop;
			Board.Pieces[WhiteKingKnightIndex]  = EPiece::WhiteKnight;
			Board.Pieces[WhiteKingRookIndex]    = EPiece::WhiteRook;

			Board.Pieces[BlackQueenRookIndex]   = EPiece::BlackRook;
			Board.Pieces[BlackQueenKnightIndex] = EPiece::BlackKnight;
			Board.Pieces[BlackQueenBishopIndex] = EPiece::BlackBishop;
			Board.Pieces[BlackQueenIndex]       = EPiece::BlackQueen;
			Board.Pieces[BlackKingIndex]        = EPiece::BlackKing;
			Board.Pieces[BlackKingBishopIndex]  = EPiece::BlackBishop;
			Board.Pieces[BlackKingKnightIndex]  = EPiece::BlackKnight;
			Board.Pieces[BlackKingRookIndex]    = EPiece::BlackRook;
		}
	};
}
