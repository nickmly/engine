#pragma once
#include "SDL.h"
class InputManager
{
public:
	InputManager();
	~InputManager();
	bool IsKeyDown(SDL_Keycode key);
};

