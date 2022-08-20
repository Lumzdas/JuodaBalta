#include "Public/Rules.h"
#include "Public/Board.h"
#include "Public/Enums.h"
#include "Public/Coordinate.h"

#include <algorithm>

namespace JuodaBalta {
	void Rules::LegalKingMoves(
			FBoards & Boards,
			FBoard const & Board,
			FCoordinate const & Coordinate,
			EPlayer const Owner
	) {
		FBoard const BoardWithoutCastling = Owner == EPlayer::White ? Board.DisableWhiteCastling() : Board.DisableBlackCastling();

		for (auto DX = -1; DX < 2; DX++) {
			for (auto DY = -1; DY < 2; DY++) {
				AddCandidateIfValid(
					Boards,
					BoardWithoutCastling,
					Coordinate,
					FCoordinate(Coordinate.X + DX, Coordinate.Y + DY),
					Owner
				);
			}
		}

		if (Owner == EPlayer::White) {
			if (Board.bWhiteQueenCastle)
				WhiteQueenCastle(Boards, BoardWithoutCastling);
			if (Board.bWhiteKingCastle)
				WhiteKingCastle(Boards, BoardWithoutCastling);
		} else {
			if (Board.bBlackQueenCastle)
				BlackQueenCastle(Boards, BoardWithoutCastling);
			if (Board.bBlackKingCastle)
				BlackKingCastle(Boards, BoardWithoutCastling);
		}
	}

	void Rules::WhiteQueenCastle(FBoards & Boards, FBoard const & Board) {
		u8 constexpr PathStart = FCoordinate::Index(1, 0);
		u8 constexpr PathEnd = FCoordinate::Index(3, 0);
		u8 constexpr KingStart = FCoordinate::Index(4, 0);
		u8 constexpr KingEnd = FCoordinate::Index(2, 0);
		u8 constexpr RookStart = FCoordinate::Index(0, 0);

		Castle(Boards, Board, EPlayer::Black, PathStart, PathEnd, KingStart, KingEnd, RookStart);
	}

	void Rules::WhiteKingCastle(FBoards & Boards, FBoard const & Board) {
		u8 constexpr PathStart = FCoordinate::Index(5, 0);
		u8 constexpr PathEnd = FCoordinate::Index(6, 0);
		u8 constexpr KingStart = FCoordinate::Index(4, 0);
		u8 constexpr KingEnd = FCoordinate::Index(6, 0);
		u8 constexpr RookStart = FCoordinate::Index(7, 0);

		Castle(Boards, Board, EPlayer::Black, PathStart, PathEnd, KingStart, KingEnd, RookStart);
	}

	void Rules::BlackQueenCastle(FBoards & Boards, FBoard const & Board) {
		u8 constexpr PathStart = FCoordinate::Index(1, 7);
		u8 constexpr PathEnd = FCoordinate::Index(3, 7);
		u8 constexpr KingStart = FCoordinate::Index(4, 7);
		u8 constexpr KingEnd = FCoordinate::Index(2, 7);
		u8 constexpr RookStart = FCoordinate::Index(0, 7);

		Castle(Boards, Board, EPlayer::White, PathStart, PathEnd, KingStart, KingEnd, RookStart);
	}

	void Rules::BlackKingCastle(FBoards & Boards, FBoard const & Board) {
		u8 constexpr PathStart = FCoordinate::Index(5, 7);
		u8 constexpr PathEnd = FCoordinate::Index(6, 7);
		u8 constexpr KingStart = FCoordinate::Index(4, 7);
		u8 constexpr KingEnd = FCoordinate::Index(6, 7);
		u8 constexpr RookStart = FCoordinate::Index(7, 7);

		Castle(Boards, Board, EPlayer::White, PathStart, PathEnd, KingStart, KingEnd, RookStart);
	}

	void Rules::Castle(
			FBoards & Boards,
			FBoard const & Board,
			EPlayer const Enemy,
			u8 const PathStart,
			u8 const PathEnd,
			u8 const KingStart,
			u8 const KingEnd,
			u8 const RookStart
	) {
		if (!HorizontalPathClear(Board, PathStart, PathEnd))
			return;

		u8 const KingMiddle = KingStart + (KingEnd - KingStart) / 2;
		if (KingsPathContested(Board, Enemy, KingStart, KingMiddle, KingEnd))
			return;

		Boards.emplace_back(
			Board
				.MovePiece(KingStart, KingEnd)
				.MovePieceMutate(RookStart, KingMiddle)
		);
	}

	bool Rules::HorizontalPathClear(FBoard const & Board, u8 const Begin, u8 const End) {
		for (u8 i = Begin; i <= End; i++) {
			if (Board.Pieces[i] != EPiece::None)
				return false;
		}

		return true;
	}

	bool Rules::KingsPathContested(FBoard const & Board, EPlayer const Enemy, u8 const KingStart, u8 const KingMiddle, u8 const KingEnd) {
		FBoards EnemyMoves;
		EnemyMoves.reserve(8);
		Rules::LegalMoves(EnemyMoves, Board, Enemy);

		return std::any_of(EnemyMoves.begin(), EnemyMoves.end(), [&](FBoard const & EnemyBoard) {
			return EnemyBoard.Pieces[KingStart] != Board.Pieces[KingStart]
				  || EnemyBoard.Pieces[KingMiddle] != EPiece::None
					|| EnemyBoard.Pieces[KingEnd] != EPiece::None;
		});
	}
}
