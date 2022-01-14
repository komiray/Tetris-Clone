/*****************************************************************************************
/* File: View.cpp
/* Description: Handles all drawing of the game to the screen using SDL - completely
/*				independent from the rest of the game such that it could be swapped out
/*				for another library if desired
/*
/* Rachel Pearson 2022
/*
/*****************************************************************************************/

#include "View.h"

/*
==================
Constructor
Initialises objects, including Graphics
==================
*/
View::View() {
	graphics = new Graphics(SCREEN_WIDTH, SCREEN_HEIGHT);
	nextTet = new Tetromino(-1, -1);
	storedTet = new Tetromino(-1, -1);
}

/*
==================
Destructor
==================
*/
View::~View() {
	delete(graphics);
	delete(nextTet);
	delete(storedTet);
}

// ------ Getters & Setters -----
void View::SetNextTetromino(int shape, int color) {
	nextTet->SetShape(shape);
	nextTet->SetColor(color);
}

void View::SetStoredTetromino(int shape, int color) {
	storedTet->SetShape(shape);
	storedTet->SetColor(color);
}
// ------------------------------

/*
==================
Draws a block sprite to the screen

Parameters:
>> xPos		Horizontal position to draw the block at
>> yPos		Vertical position to draw the block at
>> color	Color of the block to draw
==================
*/
void View::DrawBlock(int xPos, int yPos, int color) {
	int sprite;

	switch (color) {
		case (BLUE):
			sprite = BLOCK_BLUE;
			break;
		case (GREEN):
			sprite = BLOCK_GREEN;
			break;
		case (ORANGE):
			sprite = BLOCK_ORANGE;
			break;
		case (RED):
			sprite = BLOCK_RED;
			break;
		case (PURPLE):
			sprite = BLOCK_PURPLE;
			break;
		case (YELLOW):
			sprite = BLOCK_YELLOW;
			break;
		default:
			sprite = BLOCK_BLUE;
			break;
	}

	graphics->DrawSprite(xPos, yPos, TILE_SIZE, TILE_SIZE, sprite);
}

/*
==================
Draws a black rectangle with a white outline for containing GUI
elements

Parameters:
>> xPos		Horizontal position to draw the top-left of the GUI box at
>> yPos		Vertical position to draw the top-left of the GUI box at
>> width	Width of the GUI box
>> height	Height of the GUI box
==================
*/
void View::DrawGUIBox(int xPos, int yPos, int width, int height) {
	graphics->DrawRectangle(xPos, yPos, width + (BORDER_SIZE * 2), height + (BORDER_SIZE * 2), 
							graphics->WHITE);
	graphics->DrawRectangle(xPos + BORDER_SIZE, yPos + BORDER_SIZE, width, height, graphics->BLACK);
}

/*
==================
Draws the "GAME START" text that appears when the game starts,
to the middle of the screen
==================
*/
void View::DrawStartText() {
	int xPos = (SCREEN_WIDTH - START_TXT_WIDTH) / 2;
	int yPos = (SCREEN_HEIGHT - TXT_SIZE) / 2;

	graphics->DrawSprite(xPos, yPos, START_TXT_WIDTH, TXT_SIZE, GAME_START_TXT);
}

/*
==================
Draws the "GAME OVER" text that appears when the game ends,
to the middle of the screen

Parameters:
>> finalScore	The player's score, to be drawn with the
				game over text
==================
*/
void View::DrawGameOverText(int finalScore) {
	int padding = 35;
	int spacing = 12;

	int xPos = (SCREEN_WIDTH - GAME_OVER_TXT_WIDTH) / 2;
	int yPos = (SCREEN_HEIGHT - TXT_SIZE) / 2;

	graphics->DrawSprite(xPos, yPos, GAME_OVER_TXT_WIDTH, TXT_SIZE, GAME_OVER_TXT);
	DrawScoreText(xPos, yPos + padding);
	DrawScore(xPos + SCORE_TXT_WIDTH + spacing, yPos + padding, finalScore);
}

/*
==================
Draws the text that says "SCORE: "

Parameters:
>> xPos		Horizontal position to draw the text at
>> yPos		Vertical position to draw the text at
==================
*/
void View::DrawScoreText(int xPos, int yPos) {
	graphics->DrawSprite(xPos, yPos, SCORE_TXT_WIDTH, TXT_SIZE, SCORE_TXT);
}

/*
==================
Draws the text that says "SCORE: "

Parameters:
>> xPos		Horizontal position to draw the top-left of the text at
>> yPos		Vertical position to draw the top-left of the text at
==================
*/
void View::DrawNextText(int xPos, int yPos) {
	graphics->DrawSprite(xPos, yPos, NEXT_TXT_WIDTH, TXT_SIZE, NEXT_TXT);
}

/*
==================
Draws the text that says "STORED: "

Parameters:
>> xPos		Horizontal position to draw the top-left of the text at
>> yPos		Vertical position to draw the top-left of the text at
==================
*/
void View::DrawStoredText(int xPos, int yPos) {
	graphics->DrawSprite(xPos, yPos, STORED_TXT_WIDTH, TXT_SIZE, STORED_TXT);
}

void View::DrawScore(int xPos, int yPos, int score) {
	std::stack<int> digits;

	if (score == 0) {
		graphics->DrawNumSprite(xPos, yPos, TXT_SIZE, 0);
	}
	else {
		// Take digits through modulo (hence backwards) and push onto stack
		while (score >= 1) {
			digits.push(score % 10);
			score /= 10;
		}

		int offset = 0;
		while (digits.size() > 0)
		{
			// Take digits back off stack, in order
			graphics->DrawNumSprite(xPos + offset, yPos, TXT_SIZE, digits.top());
			digits.pop();
			offset += TXT_SIZE;
		}
	}
}

/*
==================
Draws the next Tetromino or the stored Tetromino

Parameters:
>> xPos		Horizontal position to draw the Tetromino at
>> yPos		Vertical position to draw the Tetromino at
>> type		The type of Tetromino to draw - the next one or the
			stored one
==================
*/
void View::DrawTetromino(int xPos, int yPos, int type) {
	Tetromino* tet;
	if (type == NEXT_TET) {
		tet = nextTet;
	}
	else {
		tet = storedTet;
	}
	for (int i = 0; i < TET_TEMPLATE_SIZE; i++) {
		for (int j = 0; j < TET_TEMPLATE_SIZE; j++) {
			if (tet->GetTemplate(j, i) == TET ||
				tet->GetTemplate(j, i) == TET_PIVOT) {
				DrawBlock((xPos + TILE_SIZE * j), (yPos + TILE_SIZE * i), 
						   tet->GetColor());
			}
		}
	}
}

/*
==================
Draws the board - filled tiles, Tetromino tiles, and the bordered
box surrounding the board

Parameters:
>> board		The board to draw
>> tetColor		The color of the current Tetromino on the board
==================
*/
void View::DrawBoard(Board* board, int tetColor) {
	int xPos = 0;
	int yPos = 0;

	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			xPos = j * TILE_SIZE + BORDER_SIZE;
			yPos = i * TILE_SIZE + BORDER_SIZE;
			if (board->GetTile(j, i) != EMPTY) {
				int color;
				if (board->GetTile(j, i) == TET ||
					board->GetTile(j, i) == TET_PIVOT) {
					color = tetColor;
				}
				else {
					color = board->GetTile(j, i);
				}
				DrawBlock(xPos, yPos, color);
			}

		}
	}
}

/*
==================
Draws all GUI - everything on the screen other than the board

Parameters:
>> currentScore		The player's current score to be displayed
==================
*/
void View::DrawGUI(int currentScore) {
	int boardWidth = BOARD_WIDTH * TILE_SIZE;
	int boardHeight = BOARD_HEIGHT * TILE_SIZE;
	int totalBoardWidth = BOARD_WIDTH * TILE_SIZE + (BORDER_SIZE * 2);
	int hTetrominoPadding = (TET_TEMPLATE_SIZE * TILE_SIZE) / 3;
	int vTetrominoPadding = (TET_TEMPLATE_SIZE * TILE_SIZE) / 4;
	int hPadding = 50;
	int vPadding = 25;
	int vTextPadding = 20;
	int spacing = 12;

	// Draw board outline
	DrawGUIBox		(0, 0, boardWidth, boardHeight);

	DrawScoreText	(totalBoardWidth + hPadding, vPadding);
	DrawScore		(totalBoardWidth + hPadding + SCORE_TXT_WIDTH + spacing, vPadding, 
					currentScore);

	// Draw next tetromino box
	DrawGUIBox		(totalBoardWidth + hPadding,
					(SCREEN_HEIGHT / 2) - GUI_BOX_SIZE - vPadding,
					GUI_BOX_SIZE, GUI_BOX_SIZE);
	DrawNextText	(totalBoardWidth + hPadding + (GUI_BOX_SIZE / 2) - (NEXT_TXT_WIDTH / 2),
					(SCREEN_HEIGHT / 2) - GUI_BOX_SIZE - vPadding + TXT_SIZE);
	DrawTetromino	(totalBoardWidth + hPadding + (GUI_BOX_SIZE / 2) - hTetrominoPadding,
					(SCREEN_HEIGHT / 2) - (GUI_BOX_SIZE / 2) - vPadding - vTetrominoPadding,
					NEXT_TET);

	// Draw stored tetromino box
	DrawGUIBox		(totalBoardWidth + hPadding, 
					(SCREEN_HEIGHT / 2) + vPadding, 
					GUI_BOX_SIZE, GUI_BOX_SIZE);
	DrawStoredText	(totalBoardWidth + hPadding + (GUI_BOX_SIZE / 2) - (STORED_TXT_WIDTH / 2),
					(SCREEN_HEIGHT / 2) + vPadding + vTextPadding);
	if (storedTet->GetShape() != -1) {
		DrawTetromino	(totalBoardWidth + hPadding + (GUI_BOX_SIZE / 2) - hTetrominoPadding,
						(SCREEN_HEIGHT / 2) + (GUI_BOX_SIZE / 2) + vPadding - vTetrominoPadding,
						STORED_TET);
	}
}

/*
==================
Clears the view
==================
*/
void View::Clear() {
	graphics->ClearScreen();
}

/*
==================
Updates the view
==================
*/
void View::Update() {
	graphics->UpdateScreen();
}
