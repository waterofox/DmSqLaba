#pragma once

#include <foxAndDot-SDK/Components/Scene_Component.h>
#include <SFML/Graphics/Text.hpp>

class Label : public Scene_Component, public sf::Drawable
{

	static inline sf::Font def_font;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::FloatRect get_component_render_bounds() override;
	sf::FloatRect get_component_bounds() override;

	sf::Drawable* as_drawable() override;


public:
	sf::Text* text = nullptr;

	void update() override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;

	Label();
	Label(const Label& other);
	Label& operator=(const Label& other);
	~Label();
	
};