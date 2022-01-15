/*****************************************************************************************
/* File: GameController.cpp
/* Description: Main controller class - runs the main game loop, handles input, and tells
*               the model/view what to do based on this
/*
/* Rachel Pearson 2022
/*
/*****************************************************************************************/

#include "GameController.h"

const auto FPS = 30;
const auto INIT_FALL_RATE = 750;
const auto FALL_RATE_INCREMENT = 50;
const auto DIFFICULTY_INCREASE_RATE = 200;

GameController::GameController()
{
    m_game = new Game();
    m_view = new View();

    m_canReleaseStoredTet = true;
    m_canStoreTet = true;

    quit = false;
    
    m_fallRate = INIT_FALL_RATE;
    m_fallTime1 = 0;
    m_fallTime2 = 0;
}

/*
==================
Starts the game - runs the main game loop, checking for input and
telling game objects what to do
==================
*/
void GameController::StartGame() {
    // Initial START GAME message
    m_view->DrawBoard(m_game->GetBoard(), m_game->GetTetrominoColor());
    m_view->DrawStartText();
    m_view->Update();
    SDL_Delay(1000);

    SDL_Event event;

    m_fallTime1 = SDL_GetTicks();

    // Main game loop
    while (!quit) {
        // Close window
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            // Movement checking
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        m_game->PlayerMove(LEFT);
                        break;
                    case SDLK_RIGHT:
                        m_game->PlayerMove(RIGHT);
                        break;
                    case SDLK_DOWN:
                        if (!m_game->PlayerMove(DOWN)) {
                            if (!m_game->PlayerPlace()) {
                                GameOver();
                            }
                            m_game->SpawnNextTetromino();
                            m_canReleaseStoredTet = true;
                            m_canStoreTet = true;
                        }
                        break;
                    case SDLK_r:
                        m_game->PlayerRotate();
                        break;
                    case SDLK_h:
                        if (m_game->HasStoredTetromino()) {
                            if (m_canReleaseStoredTet) {
                                m_game->ReleaseStoredTetromino();
                                m_canStoreTet = false;
                            }
                        }
                        else if (m_canStoreTet) {
                            m_game->StoreTetromino();
                            m_game->SpawnNextTetromino();
                            m_canReleaseStoredTet = false;
                        }
                        break;
                    // Quit game
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                }
            }
        }

        // Update fall rate
        m_fallRate = INIT_FALL_RATE - FALL_RATE_INCREMENT * 
                     (m_game->GetScore() / DIFFICULTY_INCREASE_RATE);

        // If enough time has passed, make Tetromino fall
        m_fallTime2 = SDL_GetTicks();
        if ((m_fallTime2 - m_fallTime1) > m_fallRate) {
            if (m_game->PlayerMove(DOWN)) {
                m_fallTime1 = SDL_GetTicks();
            }
            else {
                if (!m_game->PlayerPlace()) {
                    GameOver();
                }
                m_game->SpawnNextTetromino();
                m_canReleaseStoredTet = true;
                m_canStoreTet = true;
            }
        }

        UpdateView();

        SDL_Delay(1000 / FPS);
    }

    QuitGame();
}

/*
==================
Update the view
==================
*/
void GameController::UpdateView() {
    m_view->Clear();
    m_view->SetNextTetromino(m_game->GetNextShape(), m_game->GetNextColor());
    m_view->SetStoredTetromino(m_game->GetStoredShape(), m_game->GetStoredColor());
    m_view->DrawGUI(m_game->GetScore());
    m_view->DrawBoard(m_game->GetBoard(), m_game->GetTetrominoColor());
    m_view->Update();
}

/*
==================
To be called when a GameOver condition is met, displays relevant GUI and
then restarts the game
==================
*/
void GameController::GameOver() {
    m_view->Clear();
    m_view->DrawBoard(m_game->GetBoard(), m_game->GetTetrominoColor());
    m_view->DrawGameOverText(m_game->GetScore());
    m_view->Update();
    SDL_Delay(4000);

    m_view->Clear();
    m_game->Reset();
    m_view->DrawBoard(m_game->GetBoard(), m_game->GetTetrominoColor());
    m_view->DrawStartText();
    m_view->Update();
    SDL_Delay(1000);
}

/*
==================
Delete objects on game quit
==================
*/
void GameController::QuitGame() {
    delete(m_game);
    delete(m_view);
}
