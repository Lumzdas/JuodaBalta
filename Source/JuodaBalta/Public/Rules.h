#pragma once

#include "Public/Board.h"
#include "Private/Primitives.h"

namespace JuodaBalta {
	struct Rules {
		static i8 constexpr WhitePawnStartingY = 1;
		static i8 constexpr BlackPawnStartingY = FBoard::NSide - 2;

		static void LegalMoves(FBoards & Boards, FBoard const & Board, EPlayer Player);
		static void LegalMoves(FBoards & Boards, FBoard const & Board, u8 PieceIndex);

		static void LegalPawnMoves(FBoards & Boards, FBoard const & Board, FCoordinate const & Coordinate, EPlayer Owner);
		static void LegalRookMoves(FBoards & Boards, FBoard const & Board, FCoordinate const & Coordinate, EPlayer Owner);
		static void LegalKnightMoves(FBoards & Boards, FBoard const & Board, FCoordinate const & Coordinate, EPlayer Owner);
		static void LegalBishopMoves(FBoards & Boards, FBoard const & Board, FCoordinate const & Coordinate, EPlayer Owner);
		static void LegalQueenMoves(FBoards & Boards, FBoard const & Board, FCoordinate const & Coordinate, EPlayer Owner);
		static void LegalKingMoves(FBoards & Boards, FBoard const & Board, FCoordinate const & Coordinate, EPlayer Owner);

	protected:
		// Pawn helpers
		static void PawnForwardPush(FBoards & Boards, FBoard const & Board, u8 FromIndex, EPlayer Owner, i8 StrideDirection, bool DoublePush, bool PawnNearEnd);
		static void PawnTake(FBoards & Boards, FBoard const & Board, u8 FromIndex, EPlayer Owner, FCoordinate const & ToCoordinate, bool PawnNearEnd);
		static void PawnEnPassant(FBoards & Boards, FBoard const & Board, u8 FromIndex, EPlayer Owner, FCoordinate const & DoublePusherCoordinate, i8 StrideDirection);
		static void PawnMove(FBoards & Boards, FBoard const & Board, u8 FromIndex, EPlayer Owner, bool PawnNearEnd, u8 ToIndex);

		// King helpers
		static bool HorizontalPathClear(FBoard const & Board, u8 Begin, u8 End);
		static bool KingsPathContested(FBoard const & Board, EPlayer Enemy, u8 KingStart, u8 KingMiddle, u8 KingEnd);
		static void WhiteQueenCastle(FBoards & Boards, FBoard const & Board);
		static void WhiteKingCastle(FBoards & Boards, FBoard const & Board);
		static void BlackQueenCastle(FBoards & Boards, FBoard const & Board);
		static void BlackKingCastle(FBoards & Boards, FBoard const & Board);

		static void Castle(
				FBoards & Boards,
				FBoard const & Board,
				EPlayer Enemy,
				u8 PathStart,
				u8 PathEnd,
				u8 KingStart,
				u8 KingEnd,
				u8 RookStart
		);

		static bool AddCandidateIfValid(
				FBoards & Boards,
				FBoard const & Board,
				FCoordinate const & FromCoordinate,
				FCoordinate const & ToCoordinate,
				EPlayer Owner
		);
	};
}
