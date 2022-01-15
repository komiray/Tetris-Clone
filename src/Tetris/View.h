/*****************************************************************************************
/* File: View.h
/* Description: Handles all drawing of the game to the screen
/*
/* Rachel Pearson 2022
/*
/*****************************************************************************************/

// ------ Includes -----
#include <stack>
#include "Graphics.h"
#include "Board.h"
// ---------------------

// ------ Constants -----
constexpr auto BORDER_SIZE = 5;
constexpr auto SCREEN_WIDTH = BOARD_WIDTH * TILE_SIZE + (BORDER_SIZE * 2) + 300;
constexpr auto SCREEN_HEIGHT = BOARD_HEIGHT * TILE_SIZE + (BORDER_SIZE * 2);

constexpr auto TXT_SIZE = 25;

constexpr auto START_TXT_WIDTH = 10 * TXT_SIZE;
constexpr auto GAME_OVER_TXT_WIDTH = 9 * TXT_SIZE;
constexpr auto SCORE_TXT_WIDTH = 6 * TXT_SIZE;
constexpr auto NEXT_TXT_WIDTH = 5 * TXT_SIZE;
constexpr auto STORED_TXT_WIDTH = 7 * TXT_SIZE;

constexpr auto GUI_BOX_SIZE = 200;

// ----------------------

// ------ Enums --------
enum { NEXT_TET, STORED_TET };
// ---------------------

#pragma once
class View
{
	public:
		View();
		~View();
		void SetNextTetromino(int shape, int color);
		void SetStoredTetromino(int shape, int color);
		void DrawBoard(Board* board, int tetColor);
		void DrawStartText();
		void DrawGameOverText(int finalScore);
		void DrawGUI(int currentScore);
		void Clear();
		void Update();

	private:
		Graphics* graphics;
		Tetromino* nextTet;			// The next Tetromino's values, stored to be drawn
		Tetromino* storedTet;		// The stored Tetromino's values, stored to be drawn
		void DrawBlock(int xPos, int yPos, int sprite);
		void DrawScoreText(int xPos, int yPos);
		void DrawNextText(int xPos, int yPos);
		void DrawStoredText(int xPos, int yPos);
		void DrawGUIBox(int xPos, int yPos, int width, int height);
		void DrawScore(int xPos, int yPos, int score);
		void DrawTetromino(int xPos, int yPos, int type);
};

