#pragma once

#include <foxAndDot-SDK/Components/Scene_Component.h>

class Adopted_RectangleShape : public Scene_Component, public sf::RectangleShape
{
	void update() override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>&);

	sf::FloatRect get_component_bounds() override;
	sf::FloatRect get_component_render_bounds()override;

	sf::Drawable* as_drawable() override;

public:
	Adopted_RectangleShape();
	~Adopted_RectangleShape() = default;
};
