#pragma once
#include <foxAndDot-SDK/Tools/Executable.h>
#include <SFML/Window/Keyboard.hpp>

class Event_Handler : public Executable
{
	void handle_keyboard(const sf::Keyboard::Scancode& key_code, const bool& arg);
	void operator()() override;
};

