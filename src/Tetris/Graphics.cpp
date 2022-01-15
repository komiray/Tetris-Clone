/*****************************************************************************************
/* File: Graphics.cpp
/* Description: Performs all graphical functions using SDL - completely independent from
/*				the rest of the game such that SDL could easily be swapped for another
/*				library if desired
/*
/* Rachel Pearson 2022
/*
/*****************************************************************************************/

#include "Graphics.h"

constexpr auto NUM_BOUND_RECT_SIZE = 96;

/*
==================
Constructor
Creates window, sets up renderer, loads sprites
==================
*/
Graphics::Graphics(int screen_width, int screen_height) {
	SDL_Init(SDL_INIT_VIDEO);
	m_window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, 
								SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, 0);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	m_windowSurface = SDL_GetWindowSurface(m_window);

	SDL_Surface* icon;
	icon = IMG_Load("sprites/block_red.png");
	SDL_SetWindowIcon(m_window, icon);
	SDL_FreeSurface(icon);

	LoadSprites();
}

Graphics::~Graphics() {
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_FreeSurface(m_windowSurface);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

/*
==================
Draws a filled rectangle

Parameters:
>> xPos		Horizontal position to draw the top-left of the rectangle at
>> yPos		Vertical position to draw the top-left of the rectangle at
>> width	Width of rectangle
>> height	Height of rectangle
>> color	Color of rectangle
==================
*/
void Graphics::DrawRectangle(int xPos, int yPos, int width, int height, Color color) {
	SDL_Rect m_rect = {xPos, yPos, width, height};

	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(m_renderer, &m_rect);
}

/*
==================
Draws a sprite

Parameters:
>> xPos		Horizontal position to draw the top-left of the sprite at
>> yPos		Vertical position to draw the top-left of the sprite at
>> width	Width of sprite
>> height	Height of sprite
>> sprite	Sprite to draw
==================
*/
void Graphics::DrawSprite(int xPos, int yPos, int width, int height, int sprite) {
	 
	SDL_Rect rect = {xPos, yPos, width, height};

	switch (sprite) {
		case BLOCK_BLUE:
			SDL_RenderCopy(m_renderer, block_blue, NULL, &rect);
			break;
		case BLOCK_GREEN:
			SDL_RenderCopy(m_renderer, block_green, NULL, &rect);
			break;
		case BLOCK_ORANGE:
			SDL_RenderCopy(m_renderer, block_orange, NULL, &rect);
			break;
		case BLOCK_RED:
			SDL_RenderCopy(m_renderer, block_red, NULL, &rect);
			break;
		case BLOCK_PURPLE:
			SDL_RenderCopy(m_renderer, block_purple, NULL, &rect);
			break;
		case BLOCK_YELLOW:
			SDL_RenderCopy(m_renderer, block_yellow, NULL, &rect);
			break;
		case GAME_START_TXT:
			SDL_RenderCopy(m_renderer, game_start_txt, NULL, &rect);
			break;
		case GAME_OVER_TXT:
			SDL_RenderCopy(m_renderer, game_over_txt, NULL, &rect);
			break;
		case SCORE_TXT:
			SDL_RenderCopy(m_renderer, score_txt, NULL, &rect);
			break;
		case NEXT_TXT:
			SDL_RenderCopy(m_renderer, next_txt, NULL, &rect);
			break;
		case STORED_TXT:
			SDL_RenderCopy(m_renderer, stored_txt, NULL, &rect);
			break;
	}
}

/*
==================
Draws a given digit from the number sprite

Parameters:
>> xPos		Horizontal position to draw the top-left of the sprite at
>> yPos		Vertical position to draw the top-left of the sprite at
>> size		Width/height of number
>> num		Digit to draw (0-9)
==================
*/
void Graphics::DrawNumSprite(int xPos, int yPos, int size, int num) {
	SDL_Rect srcRect = { num * NUM_BOUND_RECT_SIZE, 0,
						NUM_BOUND_RECT_SIZE, NUM_BOUND_RECT_SIZE };
	SDL_Rect rect = { xPos, yPos, size, size };
	SDL_RenderCopy(m_renderer, numbers, &srcRect, &rect);
}

/*
==================
Clears the screen
==================
*/
void Graphics::ClearScreen() {
	SDL_RenderClear(m_renderer);
}


/*
==================
Updates the screen
==================
*/
void Graphics::UpdateScreen()
{
	SDL_RenderPresent(m_renderer);
}


/*
==================
Loads sprites from file and stores as SDL_Texture
==================
*/
void Graphics::LoadSprites() {
	IMG_Init(IMG_INIT_PNG);

	SDL_Surface* sprite;

	sprite = IMG_Load("sprites/block_blue.png");
	block_blue = SDL_CreateTextureFromSurface(m_renderer, sprite);
	SDL_FreeSurface(sprite);

	sprite = IMG_Load("sprites/block_green.png");
	block_green = SDL_CreateTextureFromSurface(m_renderer, sprite);
	SDL_FreeSurface(sprite);

	sprite = IMG_Load("sprites/block_orange.png");
	block_orange = SDL_CreateTextureFromSurface(m_renderer, sprite);
	SDL_FreeSurface(sprite);

	sprite = IMG_Load("sprites/block_red.png");
	block_red = SDL_CreateTextureFromSurface(m_renderer, sprite);
	SDL_FreeSurface(sprite);

	sprite = IMG_Load("sprites/block_purple.png");
	block_purple = SDL_CreateTextureFromSurface(m_renderer, sprite);
	SDL_FreeSurface(sprite);

	sprite = IMG_Load("sprites/block_yellow.png");
	block_yellow = SDL_CreateTextureFromSurface(m_renderer, sprite);
	SDL_FreeSurface(sprite);

	sprite = IMG_Load("sprites/game_start_txt.png");
	game_start_txt = SDL_CreateTextureFromSurface(m_renderer, sprite);
	SDL_FreeSurface(sprite);

	sprite = IMG_Load("sprites/game_over_txt.png");
	game_over_txt = SDL_CreateTextureFromSurface(m_renderer, sprite);
	SDL_FreeSurface(sprite);

	sprite = IMG_Load("sprites/score_txt.png");
	score_txt = SDL_CreateTextureFromSurface(m_renderer, sprite);
	SDL_FreeSurface(sprite);

	sprite = IMG_Load("sprites/next_txt.png");
	next_txt = SDL_CreateTextureFromSurface(m_renderer, sprite);
	SDL_FreeSurface(sprite);

	sprite = IMG_Load("sprites/stored_txt.png");
	stored_txt = SDL_CreateTextureFromSurface(m_renderer, sprite);
	SDL_FreeSurface(sprite);

	sprite = IMG_Load("sprites/numbers.png");
	numbers = SDL_CreateTextureFromSurface(m_renderer, sprite);
	SDL_FreeSurface(sprite);
}