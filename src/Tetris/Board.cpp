/*****************************************************************************************
/* File: Board.cpp
/* Description: Class that stores and manages the state of the board tiles as a 2D array
/*
/* Rachel Pearson 2022
/*
/*****************************************************************************************/

#include "Board.h"

/*
==================
Constructor
==================
*/
Board::Board() {
	InitializeBoard();
}

/*
==================
Initialise the board by setting all positions to EMPTY
==================
*/
void Board::InitializeBoard() {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			m_board[i][j] = EMPTY;
		}
	}
}

// ------ Getters & Setters -----
int Board::GetTile(int xTile, int yTile)
{
	return m_board[yTile][xTile];
}
// ------------------------------

/*
==================
Checks whether a given tile in the board is filled

Parameters:
>> xTile	The horizontal tile number (0 to BOARD_WIDTH-1)
>> yTile	The vertical tile number (0 to BOARD_HEIGHT-1)

Returns:
>> True if the tile at that position is filled, false if it
   is empty or occupied by a Tetromino
==================
*/
bool Board::IsTileFilled(int xTile, int yTile) {
	if (m_board[yTile][xTile] == EMPTY ||
		m_board[yTile][xTile] == TET||
		m_board[yTile][xTile] == TET_PIVOT) {
		return false;
	}
	return true;
}

/*
==================
Maps a Tetromino onto the board such that the board
states are updated with its values

Parameters:
>> tet		The Tetromino to map
==================
*/
void Board::MapTetromino(Tetromino* tet) {
	// Upper left tile of template on board
	int upperLeftX = tet->GetXTile(0);
	int upperLeftY = tet->GetYTile(0);

	// Map each index of template
	for (int i = 0; i < TET_TEMPLATE_SIZE; i++) {
		for (int j = 0; j < TET_TEMPLATE_SIZE; j++) {
			if (tet->GetTemplate(j, i) != 0 && tet->GetYTile(i) >= 0) {
				m_board[upperLeftY + i][upperLeftX + j] = tet->GetTemplate(j, i);
			}
		}
	}
}

/*
==================
Clears any Tetromino tiles from the board states
==================
*/
void Board::ClearTetromino() {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (m_board[i][j] == TET || m_board[i][j] == TET_PIVOT) {
				m_board[i][j] = EMPTY;
			}
			
		}
	}
}

/*
==================
Clears a given row from the board

Parameters:
>> row		The row to clear
==================
*/
void Board::ClearRow(int row) {
	for (int i = row; i > 0; i--) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			m_board[i][j] = m_board[i - 1][j];
		}
	}
}

/*
==================
Clears all filled rows that are found in the board

Returns:
>> The number of rows that were cleared
==================
*/
int Board::ClearFilledRows() {
	int fullRow = true;
	int rowsCleared = 0;

	// Scan from bottom of board to top
	for (int i = BOARD_HEIGHT - 1; i > 0; i--) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (!IsTileFilled(j, i)) {
				fullRow = false;
			}
		}
		if (fullRow) {
			ClearRow(i);
			// Put 'i' back if we cleared a row, because everything
			// has shifted down now
			i++;
			rowsCleared++;
		}
		fullRow = true;
	}
	return rowsCleared;
}

/*
==================
Places the current Tetromino onto the board by converting
any Tetromino tiles to standard filled board tiles

Parameters:
>> tet		The Tetromino to place

Returns:
>> True if the Tetromino was placed fully inside the board,
   false if part of it is above the board

==================
*/
bool Board::PlaceTetromino(Tetromino* tet) {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (GetTile(j, i) == TET || GetTile(j, i) == TET_PIVOT) {
				m_board[i][j] = tet->GetColor();
			}
		}
	}
	if (IsTetrominoAboveBoard(tet)) {
		return false;
	}
	return true;
}

/*
==================
Checks if any part of a given tetromino is above the board

Parameters:
>> tet		The Tetromino to check for being above the board

Returns:
>> True if the Tetromino is fully inside the board, false if 
   part of it is above the board

==================
*/
bool Board::IsTetrominoAboveBoard(Tetromino* tet) {
	// Check each index of template
	for (int i = 0; i < TET_TEMPLATE_SIZE; i++) {
		for (int j = 0; j < TET_TEMPLATE_SIZE; j++) {
			if (tet->GetTemplate(i, j) == TET ||
				tet->GetTemplate(j, i) == TET_PIVOT) {
				if (tet->GetYTile(i) < 0) {
					return true;
				}
			}
		}
	}
	return false;
}

/*
==================
Resets the board to its initial empty state
==================
*/
void Board::Reset() {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			m_board[i][j] = 0;
		}
	}

}