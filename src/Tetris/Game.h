/*****************************************************************************************
/* File: Game.h
/* Description: Manages the game state - keeps track of game variables, tells player to
/*				move, tells board to update, etc. Holds Board and TetrominoController 
/*				objects
/*
/* Rachel Pearson 2022
/*
/*****************************************************************************************/

// ------ Includes -----
#include <stdlib.h>
#include <time.h>
#include "TetrominoController.h"
// ---------------------

// ------ Constants -----
constexpr auto SINGLE_ROW_SCORE = 40;
constexpr auto DOUBLE_ROW_SCORE = 100;
constexpr auto TRIPLE_ROW_SCORE = 300;
constexpr auto TETRIS_ROW_SCORE = 1200;
// ---------------------

#pragma once
class Game
{
	public:
		Game();
		~Game();
		Board* GetBoard();
		int GetScore();
		int GetNextShape();
		int GetNextColor();
		int GetStoredShape();
		int GetStoredColor();
		int GetTetrominoColor();
		void Update();
		bool PlayerMove(int direction);
		void PlayerRotate();
		bool PlayerPlace();
		void SpawnNextTetromino();
		void StoreTetromino();
		bool HasStoredTetromino();
		void ReleaseStoredTetromino();
		void Reset();

	private:
		TetrominoController* m_tetController;
		Board* m_board;
		int m_nextShape;		// Next Tetromino's shape
		int m_nextColor;		// Next Tetromino's color (random)
		int m_score;			// Current score
		int m_storedShape;		// Stored Tetromino's shape
		int m_storedColor;		// Stored Tetromino's color
};

