#include "Group.h"

void Group::update()
{
	for (auto& comp : comps)
	{
		comp.first->setPosition(getPosition());
		comp.first->move(comp.second);
	}
}


void Group::update_resource(const std::variant<sf::Texture*, sf::Font*>&)
{
}

sf::FloatRect Group::get_component_bounds()
{
	return sf::FloatRect();
}

sf::FloatRect Group::get_component_render_bounds()
{
	return sf::FloatRect();
}

sf::Drawable* Group::as_drawable()
{
	return nullptr;
}

Group::Group()
{
	type_of_resource = Resource_Types::Undefined;
	visible = false;
}

void Group::add(sf::Transformable* comp, const sf::Vector2f& margin)
{
	comps[comp] = margin;
}

void Group::remove(sf::Transformable* comp)
{
	if (comps.find(comp) != comps.end())
	{
		comps.erase(comp);
	}
}