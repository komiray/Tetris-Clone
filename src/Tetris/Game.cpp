/*****************************************************************************************
/* File: Game.cpp
/* Description: Manages the game state - keeps track of game variables, tells player to
/*				move, tells board to update, etc. Holds Board and TetrominoController
/*				objects
/*
/* Rachel Pearson 2022
/*
/*****************************************************************************************/

#include "Game.h"

/*
==================
Constructor
Initialises Board, TetrominoController, and variables
Spawns the first Tetromino
==================
*/
Game::Game() {
	srand((unsigned)time(NULL));

	m_board = new Board;
	m_tetController = new TetrominoController(m_board);

	m_storedShape = -1;
	m_storedColor = -1;

	m_score = 0;
	m_nextShape = I;
	// Random color value
	m_nextColor = rand() % (YELLOW - BLUE + 1) + BLUE;

	SpawnNextTetromino();
}

/*
==================
Deconstructor
==================
*/
Game::~Game() {
	delete(m_board);
	delete(m_tetController);
}

Board* Game::GetBoard() {
	return m_board;
}

// ------ Getters & Setters -----
int Game::GetScore() {
	return m_score;
}

int Game::GetNextShape() {
	return m_nextShape;
}

int Game::GetNextColor() {
	return m_nextColor;
}

int Game::GetStoredShape() {
	return m_storedShape;
}

int Game::GetStoredColor() {
	return m_storedColor;
}

int Game::GetTetrominoColor() {
	return m_tetController->GetTetromino()->GetColor();
}

bool Game::HasStoredTetromino() {
	return (m_storedShape != -1);
}
// ------------------------------

/*
==================
Attempts to clear rows and adds score based on rows cleared
==================
*/
void Game::ClearRows()
{
	int rowsCleared;
	rowsCleared = m_board->ClearFilledRows();

	switch (rowsCleared) {
		case 0:
			break;
		case 1:
			m_score += SINGLE_ROW_SCORE;
			break;
		case 2:
			m_score += DOUBLE_ROW_SCORE;
			break;
		case 3:
			m_score += TRIPLE_ROW_SCORE;
			break;
		default:
			m_score += TETRIS_ROW_SCORE;
			break;
		}
}

/*
==================
Attempts to move the player Tetromino

Parameters:
>> direction	The direction to attempt movement in

Returns:
>> True if the player could move, false if it could not
==================
*/
bool Game::PlayerMove(int direction)
{
	if (m_tetController->IsValidMovement(direction)) {
		m_tetController->MoveTetromino(direction);
		m_board->ClearTetromino();
		m_board->MapTetromino(m_tetController->GetTetromino());
		return true;
	}
	return false;
}

/*
==================
Attempts to rotate the player Tetromino, does nothing on failure
==================
*/
void Game::PlayerRotate()
{
	m_tetController->RotateTetromino();
	m_board->ClearTetromino();
	m_board->MapTetromino(m_tetController->GetTetromino());
}

/*
==================
Attempts to place the player Tetromino

Returns:
>> True if the player Tetromino could be placed, false if not
==================
*/
bool Game::PlayerPlace() {
	bool success = m_board->PlaceTetromino(m_tetController->GetTetromino());
	if (success) {
		ClearRows();
	}
	return success;
}

/*
==================
Spawns the next Tetromino in the list, with a random color
==================
*/
void Game::SpawnNextTetromino() {
	m_tetController->SpawnTetromino(m_nextShape, m_nextColor);

	if (m_nextShape == Z) {
		m_nextShape = I;
	}
	else {
		m_nextShape++;
	}
	m_nextColor = rand() % (YELLOW - BLUE + 1) + BLUE;

	m_board->ClearTetromino();
	m_board->MapTetromino(m_tetController->GetTetromino());
}

/*
==================
Stores the current Tetromino and spawns the next
==================
*/
void Game::StoreTetromino() {
	m_storedShape = m_tetController->GetTetromino()->GetShape();
	m_storedColor = m_tetController->GetTetromino()->GetColor();
	SpawnNextTetromino();
}

/*
==================
Releases the stored Tetromino
==================
*/
void Game::ReleaseStoredTetromino() {
	m_tetController->SpawnTetromino(m_storedShape, m_storedColor);
	m_storedShape = -1;
	m_storedColor = -1;
}

/*
==================
Resets the Tetromino, board, score, and next shape
==================
*/
void Game::Reset()
{
	m_tetController->ResetTetromino();
	m_board->Reset();
	m_score = 0;
	m_nextShape = I + 1;
	m_nextColor = rand() % (YELLOW - BLUE + 1) + BLUE;
	m_storedShape = -1;
	m_storedColor = -1;

	m_board->ClearTetromino();
	m_board->MapTetromino(m_tetController->GetTetromino());
}
