#include "Keyboard.hpp"

const Uint8 *(Keyboard::Keyboard_State) = SDL_GetKeyboardState(nullptr);

bool Keyboard::isKeyDown(keycode key){
	return Keyboard_State[key];
}
