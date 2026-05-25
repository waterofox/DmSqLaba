#include "Event_Handler.h"

#include "../Application.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

void Event_Handler::operator()()
{
	Application::is_click = false;
	Application::is_backspace = false;
	Application::recent_keyboard_input = '\0';

	sf::RenderWindow& window = Application::the_core.get_window();
	while (auto evnt = window.pollEvent())
	{
		if (evnt->is<sf::Event::Closed>())
		{
			window.close();
		}
		else if (evnt->is<sf::Event::KeyReleased>())
		{
			sf::Keyboard::Scancode code = evnt->getIf<sf::Event::KeyReleased>()->scancode;
			

			switch (code)
			{
			case sf::Keyboard::Scancode::W: 
			{
				Application::generate_signal.push_args(Sides::N);
				Application::the_core.emit(&Application::generate_signal);
			}break;
			case sf::Keyboard::Scancode::A: 
			{
				Application::generate_signal.push_args(Sides::W);
				Application::the_core.emit(&Application::generate_signal);
			} break;
			case sf::Keyboard::Scancode::S:
			{
				Application::generate_signal.push_args(Sides::S);
				Application::the_core.emit(&Application::generate_signal);
			}break;
			case sf::Keyboard::Scancode::D:
			{
				Application::generate_signal.push_args(Sides::E);
				Application::the_core.emit(&Application::generate_signal);
			}break;
			case sf::Keyboard::Scancode::Backspace :
			{
				Application::is_backspace = true;
			} break;
			default:
				break;
			}
		}
		else if (evnt->is<sf::Event::TextEntered>())
		{
			auto sign = evnt->getIf<sf::Event::TextEntered>();
			
			if (sign->unicode != '\b')
			{
				Application::recent_keyboard_input = sign->unicode;
			}
		}
		else if (evnt->is<sf::Event::MouseButtonReleased>())
		{
			sf::Vector2i pos = evnt->getIf<sf::Event::MouseButtonReleased>()->position;
			sf::Mouse::Button but = evnt->getIf<sf::Event::MouseButtonReleased>()->button;

			Application::is_click = true;
			Application::click_pos = pos;
			Application::click = but;
		}
	}
}