#include "Public/Move.h"
#include "Public/Coordinate.h"

namespace JuodaBalta {
	FMove::FMove(FCoordinate const & InFrom, FCoordinate const & InTo) {
		From = InFrom.Index();
		To = InTo.Index();
	}
}
