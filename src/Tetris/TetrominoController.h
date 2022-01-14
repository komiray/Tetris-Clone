/*****************************************************************************************
/* File: TetrominoController.h
/* Description: Controls the player Tetromino object - handles spawning and movement
/*
/* Rachel Pearson 2022
/*
/*****************************************************************************************/

// ------ Includes -----
#include <stdlib.h>
#include <time.h>
#include "Tetromino.h"
#include "Board.h"
// ---------------------

// ------ Constants -----
constexpr auto TET_START_X = BOARD_WIDTH / 2;
constexpr auto TET_START_Y = -4;
// ----------------------

// ------ Enums --------
enum { DOWN, LEFT, RIGHT };
// ---------------------

#pragma once
class TetrominoController
{
	public:
		TetrominoController(Board *board);
		~TetrominoController();
		Tetromino* GetTetromino();
		void SpawnTetromino(int shape, int color);
		bool IsValidMovement(int direction);
		void MoveTetromino(int direction);
		bool RotateTetromino();
		void ResetTetromino();

	private:
		Tetromino* m_tetromino;
		Board* m_board;
		bool IsValidTetrominoPosition();
		bool WallKickTetromino();
};

