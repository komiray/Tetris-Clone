/*****************************************************************************************
/* File: GameController.h
/* Description: Main controller class - initialises game objects, runs the main game loop, 
/*				handles input, and tells the model/view what to do based on this
/*
/* Rachel Pearson 2022
/*
/*****************************************************************************************/

// ------ Includes -----
#include "Game.h"
#include "View.h"
// ---------------------

#pragma once
class GameController
{
	public:
		GameController();
		void StartGame();

	private:
		void GameOver();
		void UpdateAll();
		void QuitGame();
		Game* m_game;
		View* m_view;
		bool m_canReleaseStoredTet;		// True when it is valid for a Tetromino to be released
		bool m_canStoreTet;				// True when it is valid for a Tetromino to be stored

		unsigned long m_fallRate;		// Number of ms between Tetromino falling

		unsigned long m_fallTime1;		// m_fallTime2 - m_fallTime1 gives the number of ms
		unsigned long m_fallTime2;		// since the Tetromino last fell

		bool quit;
};


