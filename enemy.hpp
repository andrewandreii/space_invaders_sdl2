#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

struct Enemy {
	SDL_Rect rect;
	SDL_Color color;
	glm::vec2 position;
	glm::vec2 direction = glm::vec2(0, 1);
	float speed = 0.05;
};

#endif