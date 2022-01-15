/*****************************************************************************************
/* File: Graphics.h
/* Description: Performs all graphical functions using SDL - completely independent from 
/*				the rest of the game such that SDL could easily be swapped for another 
/*				library if desired
/*
/* Rachel Pearson 2022
/*
/*****************************************************************************************/

// ------ Includes -----
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
// ---------------------

// ------ Enums --------
enum {
	BLOCK_BLUE, BLOCK_GREEN, BLOCK_ORANGE,
	BLOCK_RED, BLOCK_PURPLE, BLOCK_YELLOW,
	GAME_START_TXT, GAME_OVER_TXT,
	NEXT_TXT, STORED_TXT, SCORE_TXT,
};
// ---------------------

// --- Color struct for passing into SDL functions ---
struct Color {
	int r;
	int g;
	int b;
};
// ----------------------------------------------------

#pragma once
class Graphics
{
	public:
		Graphics(int screen_width, int screen_height);
		~Graphics();
		void DrawRectangle(int xPos, int yPos, int width, int height, Color color);
		void DrawSprite(int xPos, int yPos, int width, int height, int sprite);
		void DrawNumSprite(int xPos, int yPos, int size, int num);
		void ClearScreen();
		void UpdateScreen();

		// Some default colors for passing into SDL functions
		Color BLACK = { 0, 0, 0 };
		Color WHITE = { 255, 255, 255 };
		Color RED = { 255, 0, 0 };
		Color BLUE = { 0, 0, 255 };

	private:
		void LoadSprites();

		SDL_Window* m_window;
		SDL_Surface* m_windowSurface;
		SDL_Renderer* m_renderer;

		// Block sprites
		SDL_Texture* block_blue;
		SDL_Texture* block_green;
		SDL_Texture* block_orange;
		SDL_Texture* block_red;
		SDL_Texture* block_purple;
		SDL_Texture* block_yellow;

		// Text sprites
		SDL_Texture* game_start_txt;
		SDL_Texture* game_over_txt;
		SDL_Texture* score_txt;
		SDL_Texture* next_txt;
		SDL_Texture* stored_txt;
		SDL_Texture* numbers;
};
