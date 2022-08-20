#include "Public/Rules.h"
#include "Public/Coordinate.h"
#include "Public/Enums.h"

namespace JuodaBalta {
	void Rules::LegalMoves(FBoards & Boards, FBoard const & Board, EPlayer const Player) {
		for (auto i = 0; i < FBoard::NPositions; i++) {
			auto const & Piece = Board.Pieces[i];
			if (Player == EPlayer::White ? static_cast<i8>(Piece) > 0 : static_cast<i8>(Piece) < 0)
				Rules::LegalMoves(Boards, Board, i);
		}
	}

	bool Rules::AddCandidateIfValid(
			FBoards & Boards,
			FBoard const & Board,
			FCoordinate const & FromCoordinate,
			FCoordinate const & ToCoordinate,
			EPlayer const Owner
	) {
		if (!ToCoordinate)
			return false;

		auto const Candidate = static_cast<i8>(Board.Pieces[ToCoordinate.Index()]);
		bool const NoPieceOnPosition = Candidate == 0;

		if (NoPieceOnPosition || (Owner == EPlayer::White ? Candidate < 0 : Candidate > 0)) {
			Boards.emplace_back(Board.MovePiece(FromCoordinate, ToCoordinate));
			return NoPieceOnPosition;
		}

		return false;
	}

	void Rules::LegalMoves(FBoards & Boards, FBoard const & Board, u8 const PieceIndex) {
		switch(Board.Pieces[PieceIndex]) {
			case EPiece::None:
				break;
			case EPiece::WhitePawn:
				LegalPawnMoves(Boards, Board, FCoordinate(PieceIndex), EPlayer::White);
				break;
			case EPiece::BlackPawn:
				LegalPawnMoves(Boards, Board, FCoordinate(PieceIndex), EPlayer::Black);
				break;
			case EPiece::WhiteRook:
				LegalRookMoves(Boards, Board, FCoordinate(PieceIndex), EPlayer::White);
				break;
			case EPiece::BlackRook:
				LegalRookMoves(Boards, Board, FCoordinate(PieceIndex), EPlayer::Black);
				break;
			case EPiece::WhiteKnight:
				LegalKnightMoves(Boards, Board, FCoordinate(PieceIndex), EPlayer::White);
				break;
			case EPiece::BlackKnight:
				LegalKnightMoves(Boards, Board, FCoordinate(PieceIndex), EPlayer::Black);
				break;
			case EPiece::WhiteBishop:
				LegalBishopMoves(Boards, Board, FCoordinate(PieceIndex), EPlayer::White);
				break;
			case EPiece::BlackBishop:
				LegalBishopMoves(Boards, Board, FCoordinate(PieceIndex), EPlayer::Black);
				break;
			case EPiece::WhiteQueen:
				LegalQueenMoves(Boards, Board, FCoordinate(PieceIndex), EPlayer::White);
				break;
			case EPiece::BlackQueen:
				LegalQueenMoves(Boards, Board, FCoordinate(PieceIndex), EPlayer::Black);
				break;
			case EPiece::WhiteKing:
				LegalKingMoves(Boards, Board, FCoordinate(PieceIndex), EPlayer::White);
				break;
			case EPiece::BlackKing:
				LegalKingMoves(Boards, Board, FCoordinate(PieceIndex), EPlayer::Black);
				break;
		}
	}
}
