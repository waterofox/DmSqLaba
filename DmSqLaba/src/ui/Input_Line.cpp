#include "Input_Line.h"
#include "../Application.h"
#define Gray sf::Color(127,127,127)

void Input_Line::update()
{
	label.update();
	label.text->setPosition(body.getPosition());
	label.text->move(sf::Vector2f(0, 0));

	if (Application::is_click)
	{
		if (is_active)
		{
			if (!body.getGlobalBounds().contains(Application::the_core.get_window().mapPixelToCoords(Application::click_pos)))
			{
				is_active = false;
				body.setFillColor(Gray);
			}
		}
		else
		{
			if (body.getGlobalBounds().contains(Application::the_core.get_window().mapPixelToCoords(Application::click_pos)))
			{
				is_active = true;
				body.setFillColor(sf::Color::White);
			}
		}
	}

	if (is_active)
	{
		if (Application::recent_keyboard_input != '\0' and label.text->getString().getSize() < 8)
		{
			label.text->setString(label.text->getString() + Application::recent_keyboard_input);
		}
		else if (Application::key_status[sf::Keyboard::Scancode::Backspace])
		{
			if (label.text->getString().getSize() != 0)
			{
				label.text->setString(label.text->getString().substring(0, label.text->getString().getSize() - 1));
			}
		}
	}
}

void Input_Line::update_resource(const std::variant<sf::Texture*, sf::Font*>& resource)
{
	this->label.update_resource(resource);
}

sf::FloatRect Input_Line::get_component_bounds()
{
	return body.getGlobalBounds();
}

sf::FloatRect Input_Line::get_component_render_bounds()
{
	return body.getGlobalBounds();
}

sf::Drawable* Input_Line::as_drawable()
{
	return this;
}

void Input_Line::draw(sf::RenderTarget& target, sf::RenderStates staet) const
{
	target.draw(body, staet);
	target.draw(label, staet);
}

void Input_Line::clear_text()
{
	label.text->setString("");
}

std::string Input_Line::get_text()
{
	return label.text->getString().toAnsiString();
}

void Input_Line::set_text(const std::string& t)
{
	label.text->setString(t);
}


Input_Line::Input_Line()
{
	body.setFillColor(Gray);
	body.setOutlineThickness(2);
	body.setOutlineColor(sf::Color::Black);
	
	label.text->setFillColor(sf::Color::Black);
	label.text->setCharacterSize(72);
	label.text->scale(sf::Vector2f(0.2, 0.2));
	
	set_resource_and_type(0, Resource_Types::Font);

}
