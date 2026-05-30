#include "Adopted_RectangleShape.h"
void Adopted_RectangleShape::update() {}
void Adopted_RectangleShape::update_resource(const std::variant<sf::Texture*, sf::Font*>&) {}

sf::FloatRect Adopted_RectangleShape::get_component_bounds()
{
	return getGlobalBounds();
}

sf::FloatRect Adopted_RectangleShape::get_component_render_bounds()
{
	return getGlobalBounds();
}

sf::Drawable* Adopted_RectangleShape::as_drawable()
{
	return this;
}

Adopted_RectangleShape::Adopted_RectangleShape()
{
	set_updatable(false);
	type_of_resource = Resource_Types::Undefined;
}