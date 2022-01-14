/*****************************************************************************************
/* File: TetrominoController.cpp
/* Description: Controls the player Tetromino object - handles spawning and movement
/*
/* Rachel Pearson 2022
/*
/*****************************************************************************************/

#include "TetrominoController.h"

/*
==================
Constructor
==================
*/
TetrominoController::TetrominoController(Board* board) {
	srand((unsigned)time(NULL));

	m_board = board;
	m_tetromino = new Tetromino(-1, -1);
}

/*
==================
Destructor
==================
*/
TetrominoController::~TetrominoController() {
	delete(m_tetromino);
}

// ------ Getters & Setters -----
Tetromino* TetrominoController::GetTetromino() {
	return m_tetromino;
}
// ------------------------------

/*
==================
Spawns a 'new' Tetromino (really just changes the values of the
same one)

Parameters:
>> shape	Shape of the 'new' Tetromino
>> color	Color of the 'new' Tetromino
==================
*/
void TetrominoController::SpawnTetromino(int shape, int color) {
	ResetTetromino();
	m_tetromino->SetShape(shape);
	m_tetromino->SetColor(color);
}

/*
==================
Moves the Tetromino 1 tile by incrementing the position of its pivot

Parameters:
>> direction	Direction to move the Tetromino in
==================
*/
void TetrominoController::MoveTetromino(int direction) {
	switch (direction) {
	case DOWN:
		m_tetromino->SetPivotYTile(m_tetromino->GetPivotYTile() + 1);
		break;
	case LEFT:
		m_tetromino->SetPivotXTile(m_tetromino->GetPivotXTile() - 1);
		break;
	case RIGHT:
		m_tetromino->SetPivotXTile(m_tetromino->GetPivotXTile() + 1);
		break;
	}
}

/*
==================
Attempts to rotate the tetromino:
- Starts by rotating normally, and checks if this is valid
- Then attempts a wall kick (moves from the wall), and
  checks if this is valid
- If not, reverse the rotation and give up

Returns:
>> True if the Tetromino was rotated successfully, false if
   not
==================
*/
bool TetrominoController::RotateTetromino() {
	m_tetromino->Rotate();
	if (IsValidTetrominoPosition()) {
		return true;
	}
	else if (WallKickTetromino()) {
		return true;
	}
	else {
		m_tetromino->ReverseRotate();
		return false;
	}
}

/*
==================
Resets the Tetromino to its starting position and
resets its shape
==================
*/
void TetrominoController::ResetTetromino()
{
	m_tetromino->SetPivotXTile(TET_START_X);
	m_tetromino->SetPivotYTile(TET_START_Y);
	m_tetromino->SetShape(I);
}

/*
==================
Attempts a wall kick; tries 1 left, then 1 right, and gives
up if neither of these are valid positions

Returns:
>> True if a wall kick was performed successfully, false if
   not
==================
*/
bool TetrominoController::WallKickTetromino() {
	// Try moving 1 to the left
	m_tetromino->SetPivotXTile(m_tetromino->GetPivotXTile() - 1);
	if (IsValidTetrominoPosition()) {
		return true;
	}
	// Try moving 1 to the right
	else {
		m_tetromino->SetPivotXTile(m_tetromino->GetPivotXTile() + 2);
		if (IsValidTetrominoPosition()) {
			return true;
		}
	}
	// If none of that worked, set position back and give up
	m_tetromino->SetPivotXTile(m_tetromino->GetPivotXTile() - 1);
	return false;
}

/*
==================
Check whether movement in a given direction is possible

Parameters:
>> direction	Direction to check for possible movement

Returns:
>> True if movement is possible in that direction, false
   if not
==================
*/
bool TetrominoController::IsValidMovement(int direction) {
	int yTile;
	int xTile;

	switch (direction) {
		case DOWN:
			for (int i = 0; i < TET_TEMPLATE_SIZE; i++) {
				for (int j = 0; j < TET_TEMPLATE_SIZE; j++) {
					// Each board tile of the template
					yTile = m_tetromino->GetYTile(i);
					xTile = m_tetromino->GetXTile(j);

					if (m_tetromino->GetTemplate(j, i) == TET ||
						m_tetromino->GetTemplate(j, i) == TET_PIVOT) {
						// Bottom of board reached
						if (yTile + 1 == BOARD_HEIGHT) {
							return false;
						}
						// If Tetromino is at most 1 block above the board,
						// and the tile below is filled
						else if (yTile >= -1 && m_board->IsTileFilled(xTile, yTile + 1)) {
							return false;
						}
					}
				}
			}
			return true;
			break;

		case LEFT:
			for (int i = 0; i < TET_TEMPLATE_SIZE; i++) {
				for (int j = 0; j < TET_TEMPLATE_SIZE; j++) {
					// Each board tile of the template
					yTile = m_tetromino->GetYTile(i);
					xTile = m_tetromino->GetXTile(j);

					if (m_tetromino->GetTemplate(j, i) == TET ||
						m_tetromino->GetTemplate(j, i) == TET_PIVOT) {
						// Left border reached
						if (xTile - 1 == -1) {
							return false;
						}
						// If tile is actually within the board, and the tile to the left
						// is filled
						else if (yTile >= 0 && m_board->IsTileFilled(xTile - 1, yTile)) {
							return false;
						}
					}
				}
			}
			return true;
			break;

		case RIGHT:
			for (int i = 0; i < TET_TEMPLATE_SIZE; i++) {
				for (int j = 0; j < TET_TEMPLATE_SIZE; j++) {
					// Each board tile of the template
					yTile = m_tetromino->GetYTile(i);
					xTile = m_tetromino->GetXTile(j);

					if (m_tetromino->GetTemplate(j, i) == TET ||
						m_tetromino->GetTemplate(j, i) == TET_PIVOT) {
						// Right border reached
						if (xTile + 1 == BOARD_WIDTH) {
							return false;
						}
						// If tile is actually within the board, and the tile to the right
						// is filled
						else if (yTile >= 0 && m_board->IsTileFilled(xTile + 1, yTile)) {
							return false;
						}
					}
				}
			}
			return true;
			break;
		default:
			return false;
	}
}

/*
==================
Checks whether the current position of the Tetromino is
a valid position on the board (not colliding or out-of-bounds)

Returns:
>> True if the current position is valid, false if not
==================
*/
bool TetrominoController::IsValidTetrominoPosition() {
	int xTile;
	int yTile;

	for (int i = 0; i < TET_TEMPLATE_SIZE; i++) {
		for (int j = 0; j < TET_TEMPLATE_SIZE; j++) {
			// Each tile of template
			yTile = m_tetromino->GetYTile(i);
			xTile = m_tetromino->GetXTile(j);

			if (m_tetromino->GetTemplate(j, i) == TET ||
				m_tetromino->GetTemplate(j, i) == TET_PIVOT) {
				// If tile is outside the bounds of the board
				if (yTile >= BOARD_HEIGHT ||
					xTile >= BOARD_WIDTH || xTile < 0) {
					return false;
				}
				// If tile is filled
				else if (m_board->IsTileFilled(xTile, yTile)) {
					return false;
				}
			}
		}
	}

	return true;
}