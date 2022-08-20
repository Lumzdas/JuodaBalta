#include "Public/Rules.h"
#include "Public/Board.h"
#include "Public/Enums.h"
#include "Public/Coordinate.h"

namespace JuodaBalta {
	void Rules::LegalBishopMoves(
			FBoards & Boards,
			FBoard const & Board,
			FCoordinate const & Coordinate,
			EPlayer const Owner
	) {
		static u8 constexpr NDirections = 4;
		static i8 const Directions[NDirections * 2] = {
				1, 1,		// right-up
				1, -1,	// right-down
				-1, -1,	// left-down
				-1, 1		// left-up
		};

		for (u8 i = 0; i < NDirections * 2; i += 2) {
			for (
					auto Delta = 1;
					AddCandidateIfValid(
						Boards,
						Board,
						Coordinate,
						FCoordinate(Coordinate.X + Directions[i] * Delta, Coordinate.Y + Directions[i + 1] * Delta),
						Owner
					);
					Delta++
					);
		}
	}
}
