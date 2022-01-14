/*****************************************************************************************
/* File: Tetromino.h
/* Description: The Tetromino object - has a shape, color, position, and template which is
/*				used to map it to the board. Can manipulate its own template e.g. rotation
/*
/* Rachel Pearson 2022
/*
/*****************************************************************************************/

// ------ Constants -----
constexpr auto TET_TEMPLATE_SIZE = 4;
// ----------------------

// ------ Enums --------
enum { I, J, L, O, S, T, Z };
// ---------------------


#pragma once
class Tetromino
{
public:
	Tetromino(int shape, int color);
	int GetPivotXTile();
	void SetPivotXTile(int x);
	int GetPivotYTile();
	void SetPivotYTile(int y);
	int GetColor();
	void SetColor(int color);
	int GetShape();
	void SetShape(int shape);
	int GetXTile(int indexX);
	int GetYTile(int indexY);
	int GetTemplate(int indexX, int indexY);
	void Rotate();
	void ReverseRotate();

private:
	void Initialise();
	int GetPivotXIndex();
	int GetPivotYIndex();

	int m_shape;
	int m_color;

	// Pivot tiles are the tile that the Tetromino rotates around,
	// and the Tetromino is stored using them here
	int m_pivotXTile;		// Horizontal tile of the board the pivot is on
	int m_pivotYTile;		// Vertical tile of the board the pivot is on
	
	// The Tetromino's template, stores its shape as a 2D array
	int m_template[TET_TEMPLATE_SIZE][TET_TEMPLATE_SIZE];

	// Constant for all possible templates, one for each shape;
	// 1 = regular Tetromino tile, 2 = pivot tile
	const int m_templates[7][TET_TEMPLATE_SIZE][TET_TEMPLATE_SIZE] 
										= {
											{
											{1, 0, 0, 0},
											{1, 0, 0, 0},
											{2, 0, 0, 0},
											{1, 0, 0, 0},
											},
											{
											{1, 0, 0, 0},
											{1, 2, 1, 0},
											{0, 0, 0, 0},
											{0, 0, 0, 0},
											},
											{
											{0, 0, 1, 0},
											{1, 2, 1, 0},
											{0, 0, 0, 0},
											{0, 0, 0, 0},
											},
											{
											{1, 1, 0, 0},
											{2, 1, 0, 0},
											{0, 0, 0, 0},
											{0, 0, 0, 0},
											},
											{
											{0, 1, 1, 0},
											{1, 2, 0, 0},
											{0, 0, 0, 0},
											{0, 0, 0, 0},
											},
											{
											{0, 1, 0, 0},
											{1, 2, 1, 0},
											{0, 0, 0, 0},
											{0, 0, 0, 0},
											},
											{
											{1, 1, 0, 0},
											{0, 2, 1, 0},
											{0, 0, 0, 0},
											{0, 0, 0, 0},
											}
											};
};

