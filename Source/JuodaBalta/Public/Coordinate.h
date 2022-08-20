#pragma once

#include "Private/Primitives.h"
#include "Board.h"

namespace JuodaBalta {
	struct FCoordinate {
		FCoordinate(): X(0), Y(0) {}
		explicit FCoordinate(u8 Index);
		FCoordinate(i32 const InX, i32 const InY) : X(InX), Y(InY) {}

		i32 X, Y;

		u8 Index() const;
		static u8 constexpr Index(u8 const X, u8 const Y) {
			return Y * FBoard::NSide + X;
		}

		explicit operator bool() const;
		bool operator==(FCoordinate const & Other) const {
			return X == Other.X && Y == Other.Y;
		}
	};
}
