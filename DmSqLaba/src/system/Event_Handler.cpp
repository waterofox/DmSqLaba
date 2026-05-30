#include "Event_Handler.h"

#include "../Application.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

void Event_Handler::handle_keyboard(const sf::Keyboard::Scancode& key_code, const bool& arg)
{

	Application::key_status[key_code] = arg;
	if (!arg)
	{
		switch (key_code)
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
		}break;
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
		default:
			break;
		}
	}
}

void Event_Handler::operator()()
{

	Application::is_click = false;
	Application::recent_keyboard_input = '\0';

	sf::RenderWindow& window = Application::the_core.get_window();
	while (auto evnt = window.pollEvent())
	{
		if (evnt->is<sf::Event::Closed>())
		{
			window.close();
		}

		if (Application::animated_transition)
		{
			break;
		}

		if (evnt->is<sf::Event::KeyReleased>())
		{
			sf::Keyboard::Scancode code = evnt->getIf<sf::Event::KeyReleased>()->scancode;
			handle_keyboard(code, false);
		}
		else if (evnt->is<sf::Event::KeyPressed>())
		{
			sf::Keyboard::Scancode code = evnt->getIf<sf::Event::KeyPressed>()->scancode;
			handle_keyboard(code, true);
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

	if (Application::animated_transition)
	{


		sf::View& camera = *Application::the_core.get_view("main");
		Entity& chunk = *static_cast<Entity*>((*Application::the_core.get_actual_scene())["chunk"]);
		switch (Application::transition_destination)
		{
		case Sides::N: 
		{
			if (camera.getCenter().y <= chunk.getGlobalBounds().getCenter().y)
			{
				Application::animated_transition = false;
				camera.setCenter(chunk.getGlobalBounds().getCenter());
			}
			else
			{
				camera.move(sf::Vector2f(0, -1 * 500 * Application::the_core.get_delta_time().asSeconds()));
			}
		} break;
		case Sides::S:
		{
			if (camera.getCenter().y >= chunk.getGlobalBounds().getCenter().y)
			{
				Application::animated_transition = false;
				camera.setCenter(chunk.getGlobalBounds().getCenter());
			}
			else
			{
				camera.move(sf::Vector2f(0, 1 * 500 * Application::the_core.get_delta_time().asSeconds()));
			}
		} break;
		case Sides::E:
		{
			if (camera.getCenter().x >= chunk.getGlobalBounds().getCenter().x)
			{
				Application::animated_transition = false;
				camera.setCenter(chunk.getGlobalBounds().getCenter());
			}
			else
			{
				camera.move(sf::Vector2f(1 * 500 * Application::the_core.get_delta_time().asSeconds(),0));
			}
		} break;
		case Sides::W:
		{
			if (camera.getCenter().x <= chunk.getGlobalBounds().getCenter().x)
			{
				Application::animated_transition = false;
				camera.setCenter(chunk.getGlobalBounds().getCenter());
			}
			else
			{
				camera.move(sf::Vector2f(-1 * 500 * Application::the_core.get_delta_time().asSeconds(),0));
			}
		} break;
		default:
			break;
		}

		Group& i_g = *static_cast<Group*>((*Application::the_core.get_actual_scene())["group"]);
		i_g.setPosition(Application::the_core.get_window().mapPixelToCoords(sf::Vector2i(0, 0)));
	}
}