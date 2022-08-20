#include "Public/Rules.h"
#include "Public/Board.h"
#include "Public/Enums.h"
#include "Public/Coordinate.h"

namespace JuodaBalta {
	void Rules::LegalKnightMoves(
			FBoards & Boards,
			FBoard const & Board,
			FCoordinate const & Coordinate,
			EPlayer const Owner
	) {
		static u8 constexpr NDeltas = 8;
		static i8 const Deltas[NDeltas * 2] = {
				-1, 2,    // up left
				1, 2,		  // up right
				2, 1,     // right up
				2, -1,	  // right down
				-1, -2,   // down left
				1, -2,	// down right
				-2, 1,  // left up
				-2, -1	// left down
		};

		for (u8 i = 0; i < NDeltas * 2; i += 2) {
			AddCandidateIfValid(
				Boards,
				Board,
				Coordinate,
				FCoordinate(Coordinate.X + Deltas[i], Coordinate.Y + Deltas[i + 1]),
				Owner
			);
		}
	}
}
