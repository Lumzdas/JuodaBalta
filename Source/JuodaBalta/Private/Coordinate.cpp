#include "Public/Coordinate.h"
#include "Public/Board.h"

namespace JuodaBalta {
	FCoordinate::FCoordinate(u8 const Index) {
		X = Index % FBoard::NSide;
		Y = Index / FBoard::NSide;
	}

	u8 FCoordinate::Index() const {
		return Index(X, Y);
	}

	FCoordinate::operator bool() const {
		return X >= 0 && X < FBoard::NSide && Y >= 0 && Y < FBoard::NSide;
	}
}
