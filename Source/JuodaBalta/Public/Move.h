#pragma once

#include "Private/Primitives.h"

namespace JuodaBalta {
	struct FCoordinate;

	struct FMove {
		FMove() : From(0), To(0) {}

		explicit FMove(FCoordinate const & From, FCoordinate const & To);

		explicit FMove(u8 const From, u8 const To) : From(From), To(To) {}

		explicit FMove(
			u8 const KingFrom,
			u8 const KingTo,
			i8 const RookFrom,
			i8 const RookTo
		) :
			From(KingFrom),
	    To(KingTo),
	    RookFrom(RookFrom),
	    RookTo(RookTo)
		{}

		u8 From;
		u8 To;

		i8 PieceToTake = -1;

		// Is only ever used for castling
		i8 RookFrom = -1;
		i8 RookTo = -1;
	};
}
