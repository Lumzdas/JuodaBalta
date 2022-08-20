#include "Public/Rules.h"
#include "Public/Board.h"
#include "Public/Enums.h"
#include "Public/Coordinate.h"

namespace JuodaBalta {
	void Rules::LegalQueenMoves(
			FBoards & Boards,
			FBoard const & Board,
			FCoordinate const & Coordinate,
			EPlayer const Owner
	) {
		LegalBishopMoves(Boards, Board, Coordinate, Owner);
		LegalRookMoves(Boards, Board, Coordinate, Owner);
	}
}
