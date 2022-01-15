/*****************************************************************************************
/* File: Main.cpp
/* Description: The Main class - simply creates a GameController and starts the game
/*
/* Rachel Pearson 2022
/*
/*****************************************************************************************/

#include <windows.h>
#include "GameController.h"

int main() {
	GameController gameController;
	gameController.StartGame();

	return 0;
}