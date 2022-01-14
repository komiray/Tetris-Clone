/*****************************************************************************************
/* File: Tetromino.cpp
/* Description: The Tetromino object - has a shape, color, position, and template which is
/*				used to map it to the board. Can manipulate its own template e.g. rotation
/*
/* Rachel Pearson 2022
/*
/*****************************************************************************************/

#include "Tetromino.h"

/*
==================
Constructor
==================
*/
Tetromino::Tetromino(int shape, int color) {
	m_shape = shape;
	m_color = color;

	Initialise();
}

// ------ Getters & Setters -----
int Tetromino::GetPivotXTile() {
	return m_pivotXTile;
}

void Tetromino::SetPivotXTile(int x) {
	m_pivotXTile = x;
}

int Tetromino::GetPivotYTile() {
	return m_pivotYTile;
}

void Tetromino::SetPivotYTile(int y) {
	m_pivotYTile = y;
}

/*
==================
Get the horizontal board tile that a given index maps to
==================
*/
int Tetromino::GetXTile(int indexX) {
	return (indexX + m_pivotXTile - GetPivotXIndex());
}

/*
==================
Get the vertical board tile that a given index maps to
==================
*/
int Tetromino::GetYTile(int indexY) {
	return (indexY + m_pivotYTile - GetPivotYIndex());
}

int Tetromino::GetTemplate(int indexX, int indexY)
{
	return m_template[indexY][indexX];
}

/*
==================
Get the horizontal index of the pivot within the template
==================
*/
int Tetromino::GetPivotXIndex() {
	for (int i = 0; i < TET_TEMPLATE_SIZE; i++) {
		for (int j = 0; j < TET_TEMPLATE_SIZE; j++) {
			if (m_template[i][j] == 2) {
				return j;
			}
		}
	}
	return -1;
}

/*
==================
Get the vertical index of the pivot within the template
==================
*/
int Tetromino::GetPivotYIndex() {
	for (int i = 0; i < TET_TEMPLATE_SIZE; i++) {
		for (int j = 0; j < TET_TEMPLATE_SIZE; j++) {
			if (m_template[i][j] == 2) {
				return i;
			}
		}
	}
	return -1;
}

int Tetromino::GetColor() {
	return m_color;
}

void Tetromino::SetColor(int color) {
	m_color = color;
}

int Tetromino::GetShape() {
	return m_shape;
}

void Tetromino::SetShape(int shape) {

	m_shape = shape;

	for (int i = 0; i < TET_TEMPLATE_SIZE; i++) {
		for (int j = 0; j < TET_TEMPLATE_SIZE; j++) {
			m_template[i][j] = m_templates[shape][i][j];
		}
	}
}
// ------------------------------

/*
==================
Initialises the Tetromino by setting its template to the
correct one for its shape
==================
*/
void Tetromino::Initialise() {
	for (int i = 0; i < TET_TEMPLATE_SIZE; i++) {
		for (int j = 0; j < TET_TEMPLATE_SIZE; j++) {
			m_template[i][j] = m_templates[m_shape][i][j];
		}
	}
}

/*
==================
Rotates the Tetromino 90 degrees clockwise by changing its template
The center of rotation is the pivot - the tile marked as 2 / TET_PIVOT
==================
*/
void Tetromino::Rotate() {
	int m_newRotation[TET_TEMPLATE_SIZE][TET_TEMPLATE_SIZE];

	for (int i = 0; i < TET_TEMPLATE_SIZE; i++) {
		for (int j = 0; j < TET_TEMPLATE_SIZE; j++) {
			m_newRotation[i][j] = m_template[(TET_TEMPLATE_SIZE - 1) - j][i];
		}
	}

	for (int i = 0; i < TET_TEMPLATE_SIZE; i++) {
		for (int j = 0; j < TET_TEMPLATE_SIZE; j++) {
			m_template[i][j] = m_newRotation[i][j];
		}
	}
}

/*
==================
Rotates the Tetromino 90 degrees anticlockwise by changing its template
The center of rotation is the pivot - the tile marked as 2 / TET_PIVOT
==================
*/
void Tetromino::ReverseRotate() {
	int m_newRotation[TET_TEMPLATE_SIZE][TET_TEMPLATE_SIZE];

	for (int i = 0; i < TET_TEMPLATE_SIZE; i++) {
		for (int j = 0; j < TET_TEMPLATE_SIZE; j++) {
			m_newRotation[i][j] = m_template[j][(TET_TEMPLATE_SIZE - 1) - i];
		}
	}

	for (int i = 0; i < TET_TEMPLATE_SIZE; i++) {
		for (int j = 0; j < TET_TEMPLATE_SIZE; j++) {
			m_template[i][j] = m_newRotation[i][j];
		}
	}
}

