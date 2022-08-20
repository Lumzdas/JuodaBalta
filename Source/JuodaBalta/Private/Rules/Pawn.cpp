#include "Public/Rules.h"
#include "Public/Board.h"
#include "Public/Enums.h"
#include "Public/Coordinate.h"

namespace JuodaBalta {
	void Rules::LegalPawnMoves(
			FBoards & Boards,
			FBoard const & Board,
			FCoordinate const & Coordinate,
			EPlayer const Owner
	) {
		bool const PawnAtOrigin =
			Owner == EPlayer::White
				? Coordinate.Y == WhitePawnStartingY
				: Coordinate.Y == BlackPawnStartingY;

		bool const PawnNearEnd =
			Owner == EPlayer::White
				? Coordinate.Y == BlackPawnStartingY
				: Coordinate.Y == WhitePawnStartingY;

		i8 const StrideDirection = Owner == EPlayer::White ? 1 : -1;

		u8 const FromIndex = Coordinate.Index();

		PawnForwardPush(Boards, Board, FromIndex, Owner, StrideDirection, PawnAtOrigin, PawnNearEnd);
		PawnTake(Boards, Board, FromIndex, Owner, FCoordinate(Coordinate.X - 1, Coordinate.Y + StrideDirection), PawnNearEnd);
		PawnTake(Boards, Board, FromIndex, Owner, FCoordinate(Coordinate.X + 1, Coordinate.Y + StrideDirection), PawnNearEnd);
		PawnEnPassant(Boards, Board, FromIndex, Owner, FCoordinate(Coordinate.X - 1, Coordinate.Y), StrideDirection);
		PawnEnPassant(Boards, Board, FromIndex, Owner, FCoordinate(Coordinate.X + 1, Coordinate.Y), StrideDirection);
	}

	void Rules::PawnForwardPush(
			FBoards & Boards,
			FBoard const & Board,
			u8 const FromIndex,
			EPlayer const Owner,
			i8 const StrideDirection,
			bool const DoublePush,
			bool const PawnNearEnd
	) {
		// Due to promotion, a pawn cannot exist at the top/bottom of the board,
		// so it's safe to just add to the index, without checking the bounds of individual (X/Y) components
		u8 const FirstStep = FromIndex + FBoard::NSide * StrideDirection;
		EPiece const & FirstStepCandidate = Board.Pieces[FirstStep];
		if (FirstStepCandidate != EPiece::None)
			return;

		PawnMove(Boards, Board, FromIndex, Owner, PawnNearEnd, FirstStep);

		if (!DoublePush)
			return;

		u8 const SecondStep = FirstStep + FBoard::NSide * StrideDirection;
		EPiece const & SecondStepCandidate = Board.Pieces[SecondStep];
		if (SecondStepCandidate != EPiece::None)
			return;

		FBoard DoublePushBoard = Board.MovePiece(FromIndex, SecondStep);
		DoublePushBoard.DoublePushedPawnIndex = SecondStep;
		Boards.emplace_back(DoublePushBoard);
	}

	void Rules::PawnTake(
			FBoards & Boards,
			FBoard const & Board,
			u8 const FromIndex,
			EPlayer Owner,
			FCoordinate const & ToCoordinate,
			bool const PawnNearEnd
	) {
		if (ToCoordinate) {
			u8 const ToIndex = ToCoordinate.Index();
			EPiece const & TakeCandidate = Board.Pieces[ToIndex];
			if (Owner == EPlayer::White ? static_cast<i8>(TakeCandidate) < 0 : static_cast<i8>(TakeCandidate) > 0)
				PawnMove(Boards, Board, FromIndex, Owner, PawnNearEnd, ToIndex);
		}
	}

	void Rules::PawnEnPassant(
			FBoards & Boards,
			FBoard const & Board,
			u8 FromIndex,
			EPlayer Owner,
			FCoordinate const & DoublePusherCoordinate,
			i8 StrideDirection
	) {
		if (!DoublePusherCoordinate)
			return;

		u8 const DoublePusherIndex = DoublePusherCoordinate.Index();
		if (Board.DoublePushedPawnIndex == DoublePusherIndex) {
			FCoordinate const ToCoordinate = FCoordinate(DoublePusherCoordinate.X, DoublePusherCoordinate.Y + StrideDirection);
			u8 const ToIndex = ToCoordinate.Index();
			if (Board.Pieces[ToIndex] == EPiece::None) {
				Boards.emplace_back(
					Board
						.MovePiece(FromIndex, DoublePusherIndex)
						.MovePieceMutate(DoublePusherIndex, ToIndex)
				);
			}
		}
	}

	void Rules::PawnMove(
			FBoards & Boards,
			FBoard const & Board,
			u8 const FromIndex,
			EPlayer const Owner,
			bool const PawnNearEnd,
			u8 const ToIndex
	) {
		if (PawnNearEnd) {
			if (Owner == EPlayer::White) {
				Boards.emplace_back(Board.MovePiece(FromIndex, ToIndex).PromotePawnMutate(ToIndex, EPiece::WhiteRook));
				Boards.emplace_back(Board.MovePiece(FromIndex, ToIndex).PromotePawnMutate(ToIndex, EPiece::WhiteKnight));
				Boards.emplace_back(Board.MovePiece(FromIndex, ToIndex).PromotePawnMutate(ToIndex, EPiece::WhiteBishop));
				Boards.emplace_back(Board.MovePiece(FromIndex, ToIndex).PromotePawnMutate(ToIndex, EPiece::WhiteQueen));
			}
			else {
				Boards.emplace_back(Board.MovePiece(FromIndex, ToIndex).PromotePawnMutate(ToIndex, EPiece::BlackRook));
				Boards.emplace_back(Board.MovePiece(FromIndex, ToIndex).PromotePawnMutate(ToIndex, EPiece::BlackKnight));
				Boards.emplace_back(Board.MovePiece(FromIndex, ToIndex).PromotePawnMutate(ToIndex, EPiece::BlackBishop));
				Boards.emplace_back(Board.MovePiece(FromIndex, ToIndex).PromotePawnMutate(ToIndex, EPiece::BlackQueen));
			}
		}
		else {
			Boards.emplace_back(Board.MovePiece(FromIndex, ToIndex));
		}
	}
}
