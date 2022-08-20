#pragma once

#include "Private/Primitives.h"
#include "Public/Move.h"
#include "Public/Board.h"

#define JUODA_BALTA_STATS

namespace JuodaBalta {
	struct FBoard;
	enum class EPlayer : i8;

	class FSolver {
	public:
		FSolver(FBoard const & InBoard, EPlayer InCPUColor, u8 InMaxSearchDepth);

		FMove BestMove();

		u8 MaxSearchDepth;

	private:
		#ifdef JUODA_BALTA_STATS
		u32 NodeVisits = 0;
		#endif

		FBoard const StartingBoard;
		EPlayer const CPUColor;
		EPlayer const EnemyColor;

		FMove BestMoveInner();

		i32 ABMax(
				FBoard const & Board,
				i32 Alpha,
				i32 Beta,
				u8 Depth
		);

		i32 ABMin(
				FBoard const & Board,
				i32 Alpha,
				i32 Beta,
				u8 Depth
		);

		void LegalMoves(
				FBoards & Boards,
				FBoard const & Board,
				EPlayer Owner
		) const;

		static void SortAsc(FBoardIterator Start, FBoardIterator End);
		static void SortDesc(FBoardIterator Start, FBoardIterator End);
	};
}
