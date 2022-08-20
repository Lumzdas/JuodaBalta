#include "Public/Solver.h"
#include "Public/Enums.h"
#include "Public/Rules.h"

#ifdef JUODA_BALTA_STATS
#include <iostream>
#include <chrono>
#endif

#include <algorithm>

namespace JuodaBalta {
	FSolver::FSolver(FBoard const & Board, EPlayer const CPUColor, u8 const MaxSearchDepth) :
			StartingBoard(Board),
			CPUColor(CPUColor),
			MaxSearchDepth(MaxSearchDepth),
			EnemyColor(InvertPlayer(CPUColor))
	{}

	FMove FSolver::BestMove() {
		#ifdef JUODA_BALTA_STATS
		auto const Start = std::chrono::steady_clock::now();
		#endif

		FMove const Result = BestMoveInner();

		#ifdef JUODA_BALTA_STATS
		auto const End = std::chrono::steady_clock::now();
		#endif

		#ifdef JUODA_BALTA_STATS
		std::cout << "CPU took " << std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() << "ms" << std::endl;
		std::cout << "Node visits: " << NodeVisits << std::endl;
		#endif

		return Result;
	}

	FMove FSolver::BestMoveInner() {
		FMove BestMoveMemo;
		i32 Alpha = INT16_MIN;

		FBoards Boards;
		Boards.reserve(32 * sizeof(FBoard));
		LegalMoves(Boards, StartingBoard, CPUColor);

		for (auto const & LegalBoard : Boards) {
			#ifdef JUODA_BALTA_STATS
			NodeVisits++;
			#endif

			i32 const Score = ABMin(LegalBoard, Alpha, INT16_MAX, 2);
			FMove const Move = LegalBoard.ToMove(StartingBoard);

			if (Score > Alpha) {
				Alpha = Score;
				BestMoveMemo = Move;
			}
		}

		return BestMoveMemo;
	}

	i32 FSolver::ABMax(
			FBoard const & Board,
			i32 Alpha,
			i32 const Beta,
			u8 const Depth
	) {
		// King already taken, can't do much
		if (Board.CPUScore < -10000)
			return Board.CPUScore;

		FBoards Boards;
		Boards.reserve(32 * sizeof(FBoard));
		LegalMoves(Boards, Board, CPUColor);

		for (auto const & LegalBoard : Boards) {
			#ifdef JUODA_BALTA_STATS
			NodeVisits++;
			#endif

			i32 Score;
			if (Depth >= MaxSearchDepth && Board.CPUScore == LegalBoard.CPUScore)
				Score = LegalBoard.CPUScore;
			else
				Score = ABMin(LegalBoard, Alpha, Beta, Depth + 1);

			if (Score > Alpha)
				Alpha = Score;

			// Beta Prune
			if (Score >= Beta)
				break;
		}

		return Alpha;
	}

	i32 FSolver::ABMin(
			FBoard const & Board,
			i32 const Alpha,
			i32 Beta,
			u8 const Depth
	) {
		// King already taken, can't do much
		if (Board.CPUScore > 10000)
			return Board.CPUScore;

		FBoards Boards;
		Boards.reserve(32 * sizeof(FBoard));
		LegalMoves(Boards, Board, EnemyColor);

		for (auto const & LegalBoard : Boards) {
			#ifdef JUODA_BALTA_STATS
			NodeVisits++;
			#endif

			i32 Score;
			if (Depth >= MaxSearchDepth && Board.CPUScore == LegalBoard.CPUScore)
				Score = LegalBoard.CPUScore;
			else
				Score = ABMax(LegalBoard, Alpha, Beta, Depth + 1);

			if (Score < Beta)
				Beta = Score;

			// Alpha prune
			if (Score <= Alpha)
				break;
		}

		return Beta;
	}

	void FSolver::SortAsc(FBoardIterator Start, FBoardIterator End) {
		std::sort(Start, End, [](FBoard const & First, FBoard const & Second) {
			return First.CPUScore < Second.CPUScore;
		});
	}

	void FSolver::SortDesc(FBoardIterator Start, FBoardIterator End) {
		std::sort(Start, End, [](FBoard const & First, FBoard const & Second) {
			return First.CPUScore > Second.CPUScore;
		});
	}

	void FSolver::LegalMoves(
			FBoards & Boards,
			FBoard const & Board,
			EPlayer const Owner
	) const {
		Rules::LegalMoves(Boards, Board, Owner);

		for (auto & LegalBoard : Boards)
			LegalBoard.CPUScore = LegalBoard.Score(CPUColor);

		Owner == CPUColor
			? SortDesc(Boards.begin(), Boards.end())
			: SortAsc(Boards.begin(), Boards.end());
	}
}
