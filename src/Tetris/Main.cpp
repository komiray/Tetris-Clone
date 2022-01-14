/*****************************************************************************************
/* File: Main.cpp
/* Description: The Main class - simply creates a GameController and starts the game
/*
/* Rachel Pearson 2022
/*
/*****************************************************************************************/

#include <windows.h>
#include "GameController.h"

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
	GameController gameController;
	gameController.StartGame();

	return 0;
}