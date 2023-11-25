#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "enemy.hpp"

//define window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

//define SDL Window related variables
SDL_Window* window = NULL;
SDL_Renderer* windowRenderer = NULL;
SDL_Event currentEvent;

bool quit = false;

int mouseX, mouseY;

const int ENEMY_WIDTH = 50;
const int ENEMY_HEIGHT = 50;
std::vector<Enemy> enemies;

void spawn_enemy(int h, int w, int x, int y) {
    Enemy e;
    e.rect.h = h;
    e.rect.w = w;
    e.position.x = x;
    e.position.y = y;

    enemies.push_back(e);
}

void spawn_row_of_enemies() {
    for (int i = ENEMY_WIDTH; i < WINDOW_WIDTH; i += 100) {
        spawn_enemy(ENEMY_HEIGHT, ENEMY_WIDTH, i, -ENEMY_HEIGHT);
    }
}

bool initWindow() {

    bool success = true;

    //Try to initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {

        std::cout << "SDL initialization failed" << std::endl;
        success = false;

    }
    else {

        //Try to create the window
        window = SDL_CreateWindow(
            "Hello SDL2 Window!",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN);

        if (window == NULL) {

            std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
            success = false;

        } else {

            // Create a renderer for the current window
            windowRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            if (windowRenderer == NULL) {

                std::cout << "Failed to create the renderer: " << SDL_GetError() << std::endl;
                success = false;

            } else {

                //Set background color
                SDL_SetRenderDrawColor(windowRenderer, 255, 255, 255, 255);

                //Apply background color
                SDL_RenderClear(windowRenderer);
            }
        }
    }

    return success;
}

void processMovement() {
    for (auto &enemy : enemies) {
        // glm::vec2 pos = glm::vec2(enemy.rect.x, enemy.rect.y);
        enemy.position += enemy.direction * enemy.speed;
        enemy.rect.x = enemy.position.x - enemy.rect.w / 2;
        enemy.rect.y = enemy.position.y - enemy.rect.h / 2;
        //std::cout << "pos: " << enemy.direction.x * enemy.speed << std::endl;
        // pos += enemy.direction * enemy.speed;
    }
}

void processEvents() {

    //Check for events in queue
    SDL_PollEvent(&currentEvent);

    //User requests quit
    if (currentEvent.type == SDL_QUIT) {

        quit = true;
    }

    //Mouse event -> pressed button
    if (currentEvent.type == SDL_MOUSEBUTTONDOWN) {

        if (currentEvent.button.button == SDL_BUTTON_LEFT) {

            SDL_GetMouseState(&mouseX, &mouseY);
            std::cout << "Mouse left click => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
        }
    }

    //Mouse event -> mouse movement
    if (currentEvent.type == SDL_MOUSEMOTION) {

        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LMASK) {

            SDL_GetMouseState(&mouseX, &mouseY);
            std::cout << "Mouse move while left clicking => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
        }
    }

    //Keyboard event
    if (currentEvent.type == SDL_KEYDOWN) {

        switch (currentEvent.key.keysym.sym) {

        case SDLK_UP:
            spawn_row_of_enemies();
            std::cout << "Spawned." << std::endl;
            break;

        case SDLK_DOWN:
            break;

        case SDLK_LEFT:
            break;

        case SDLK_RIGHT:
            break;

        case SDLK_r:
            break;

        case SDLK_s:
            break;

        case SDLK_ESCAPE:

            quit = true;
            break;

        default:
            break;
        }
    }
}

void drawFrame() {

    //Clear the background
    SDL_SetRenderDrawColor(windowRenderer, 255, 255, 255, 255);
    SDL_RenderClear(windowRenderer);

    //Draw scene
    SDL_SetRenderDrawColor(windowRenderer, 255, 0, 0, 255);
    for (auto enemy : enemies) {
        SDL_RenderFillRect(windowRenderer, &enemy.rect);
    }

    //Update window
    SDL_RenderPresent(windowRenderer);
}

void cleanup() {

    //Destroy renderer
    if (windowRenderer) {

        SDL_DestroyRenderer(windowRenderer);
        windowRenderer = NULL;
    }

    //Destroy window
    if (window) {

        SDL_DestroyWindow(window);
        window = NULL;
    }

    //Quit SDL
    SDL_Quit();
}

int main(int argc, char* argv[]) {

    //Initialize window
    if (!initWindow()) {

        std::cout << "Failed to initialize" << std::endl;
        return -1;
    }



    //Game loop
    while (!quit) {
        processMovement();
        processEvents();
        drawFrame();
    }

    cleanup();
    return 0;
}
