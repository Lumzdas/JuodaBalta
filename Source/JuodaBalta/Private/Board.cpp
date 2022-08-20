#include "Public/Board.h"
#include "Public/Enums.h"
#include "Public/Move.h"
#include "Public/Coordinate.h"
#include "Public/Rules.h"

namespace JuodaBalta {
	FBoard FBoard::MovePiece(FCoordinate const & From, FCoordinate const & To) const {
		return MovePiece(From.Index(), To.Index());
	}

	FBoard FBoard::MovePiece(u8 const FromIndex, u8 const ToIndex) const {
		auto Copy = FBoard(*this);
		Copy.MovePieceMutate(FromIndex, ToIndex);
		return Copy;
	}

	FBoard & FBoard::MovePieceMutate(u8 FromIndex, u8 ToIndex) {
		EPiece & From = Pieces[FromIndex];
		EPiece & To = Pieces[ToIndex];

		DoublePushedPawnIndex = 0;

		if (static_cast<i8>(To) > 0)
			WhiteScore -= ChessPieceValue(To);
		else
			WhiteScore += ChessPieceValue(To);

		u8 constexpr WhiteQueenRookIndex = 0;
		u8 constexpr WhiteBishopRookIndex = NSide - 1;
		u8 constexpr BlackQueenRookIndex = NSide * (NSide - 1);
		u8 constexpr BlackBishopRookIndex = NSide * NSide - 1;

		if (FromIndex == WhiteQueenRookIndex || ToIndex == WhiteQueenRookIndex)
			bWhiteQueenCastle = false;
		else if (FromIndex == WhiteBishopRookIndex || ToIndex == WhiteBishopRookIndex)
			bWhiteKingCastle = false;
		else if (FromIndex == BlackQueenRookIndex || ToIndex == BlackQueenRookIndex)
			bBlackQueenCastle = false;
		else if (FromIndex == BlackBishopRookIndex || ToIndex == BlackBishopRookIndex)
			bBlackKingCastle = false;

		To = From;
		From = EPiece::None;

		return *this;
	}

	FBoard & FBoard::PromotePawnMutate(u8 Index, EPiece ToPiece) {
		if (static_cast<i8>(ToPiece) > 0) {
			WhiteScore = WhiteScore - PawnValue + ChessPieceValue(ToPiece);
		}
		else {
			WhiteScore = WhiteScore + PawnValue - ChessPieceValue(ToPiece);;
		}

		Pieces[Index] = ToPiece;

		return *this;
	}

	i32 FBoard::Score(EPlayer const Player) const {
		return Player == EPlayer::White ? WhiteScore : -WhiteScore;
	}

	FBoard FBoard::DisableWhiteCastling() const {
		auto Copy = FBoard(*this);
		Copy.bWhiteQueenCastle = false;
		Copy.bWhiteKingCastle = false;
		return Copy;
	}

	FBoard FBoard::DisableBlackCastling() const {
		auto Copy = FBoard(*this);
		Copy.bBlackQueenCastle = false;
		Copy.bBlackKingCastle = false;
		return Copy;
	}

	FMove FBoard::ToMove(FBoard const & StartingBoard) const {
		return FMove(0, 0);
//		u8 MissingPiece = -1;
//		u8 ExtraPiece = -1;
//
//		u8 MissingRook = -1;
//		u8 ExtraRook = -1;
//
//		for (u8 i = 0; i < NPositions; i++) {
//			if (Pieces[i] != StartingBoard.Pieces[i]) {
//				if (Pieces[i] == EPiece::None) {
//					if (StartingBoard.Pieces[i] == EPiece::WhiteRook || StartingBoard.Pieces[i] == EPiece::BlackRook)
//						MissingRook = i;
//					else
//						MissingPiece = i;
//				}
//				else {
//					if (Pieces[i] == EPiece::WhiteRook || Pieces[i] == EPiece::BlackRook)
//						ExtraRook = i;
//					else
//						ExtraPiece = i;
//				}
//			}
//		}
//
//		// Castling
//		if (MissingPiece > -1 && MissingRook > -1) {
//			return FMove(MissingPiece, ExtraPiece, MissingRook, ExtraRook);
//		}
//
//		return FMove(std::max(MissingPiece, MissingRook), std::max(ExtraPiece, ExtraRook));
	}

	i32 FBoard::ChessPieceValue(EPiece const Piece) {
		switch(Piece) {
			case EPiece::None:
				return 0;
			case EPiece::WhitePawn: case EPiece::BlackPawn:
				return PawnValue;
			case EPiece::WhiteRook: case EPiece::BlackRook:
				return RookValue;
			case EPiece::WhiteKnight: case EPiece::BlackKnight:
				return KnightValue;
			case EPiece::WhiteBishop: case EPiece::BlackBishop:
				return BishopValue;
			case EPiece::WhiteQueen: case EPiece::BlackQueen:
				return QueenValue;
			case EPiece::WhiteKing: case EPiece::BlackKing:
				return KingValue;
		}

		return 0;
	}
}
