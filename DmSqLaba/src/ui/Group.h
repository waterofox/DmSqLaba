#pragma once

#include <foxAndDot-SDK/Components/Scene_Component.h>
#include <SFML/Graphics/Transformable.hpp>

class Group : public Scene_Component, public sf::Transformable
{

	//class for making simple groups of transformable components

	std::unordered_map<sf::Transformable*, sf::Vector2f> comps;



	void update() override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>&) override;

	sf::FloatRect get_component_bounds() override;
	sf::FloatRect get_component_render_bounds() override;

	sf::Drawable* as_drawable() override;

public:
	Group();
	~Group() = default;

	void add(sf::Transformable* comp, const sf::Vector2f& margin);
	void remove(sf::Transformable* comp);
};