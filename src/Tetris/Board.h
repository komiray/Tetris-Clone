/*****************************************************************************************
/* File: Board.h
/* Description: Class that stores and manages the state of the board tiles as a 2D array
/*
/* Rachel Pearson 2022
/*
/*****************************************************************************************/

// ------ Includes -----
#include "Tetromino.h"
// ---------------------

// ----- Constants -----
constexpr auto BOARD_WIDTH = 10;
constexpr auto BOARD_HEIGHT = 20;
constexpr auto TILE_SIZE = 30;
// ---------------------

// ------ Enums --------
enum {
	EMPTY, TET, TET_PIVOT,
	BLUE, GREEN, ORANGE, RED, PURPLE, YELLOW
};
// ---------------------

#pragma once
class Board
{
	public:
		Board();
		int GetTile(int xTile, int yTile);
		int ClearFilledRows();
		void MapTetromino(Tetromino* tet);
		bool PlaceTetromino(Tetromino* tet);
		bool IsTetrominoAboveBoard(Tetromino* tet);
		bool IsTileFilled(int xTile, int yTile);
		void ClearTetromino();
		void Reset();

	private:
		int m_board[BOARD_HEIGHT][BOARD_WIDTH];		// The 2D array of board states
		void InitializeBoard();
		void ClearRow(int row);
};
