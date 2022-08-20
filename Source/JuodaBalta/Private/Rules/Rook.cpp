#include "Public/Rules.h"
#include "Public/Board.h"
#include "Public/Enums.h"
#include "Public/Coordinate.h"

namespace JuodaBalta {
	void Rules::LegalRookMoves(FBoards & Boards, FBoard const & Board, FCoordinate const & Coordinate, EPlayer const Owner) {
		static u8 constexpr NDirections = 4;
		static i8 constexpr Directions[NDirections * 2] = {
				0, 1,		// up
				1, 0,		// right
				0, -1,	// down
				-1, 0		// left
		};

		for (u8 i = 0; i < NDirections * 2; i += 2) {
			for (
				auto Delta = 1;
				AddCandidateIfValid(
					Boards,
					Board,
					Coordinate,
					FCoordinate(Coordinate.X + Directions[i] * Delta,  Coordinate.Y + Directions[i + 1] * Delta),
					Owner
				);
				Delta++
			);
		}
	}
}
