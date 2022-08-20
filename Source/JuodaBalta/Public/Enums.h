#pragma once

#include "Private/Primitives.h"

namespace JuodaBalta {
	enum class EPlayer : i8 {
		White = 1,
		Black = -1,
	};

	EPlayer InvertPlayer(EPlayer const Player);

	enum class EPiece : i8 {
		None = 0,

		WhitePawn = 1,
		WhiteRook = 2,
		WhiteKnight = 3,
		WhiteBishop = 4,
		WhiteQueen = 5,
		WhiteKing = 6,

		BlackPawn = -1,
		BlackRook = -2,
		BlackKnight = -3,
		BlackBishop = -4,
		BlackQueen = -5,
		BlackKing = -6,
	};
}
