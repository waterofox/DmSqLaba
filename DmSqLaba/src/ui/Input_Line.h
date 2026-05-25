#pragma once
#include <foxAndDot-SDK/Components/Scene_Component.h>
#include "Label.h"
class Input_Line : public::Scene_Component, public sf::Drawable
{
	
	Label label;
	bool is_active = false;

	void update() override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;
private:
	sf::FloatRect get_component_bounds() override;
	sf::FloatRect get_component_render_bounds() override;
	sf::Drawable* as_drawable() override;

	void draw(sf::RenderTarget& target, sf::RenderStates staet) const override;
public:
	sf::RectangleShape body;

	void clear_text();
	std::string get_text();
	void set_text(const std::string& t);

	Input_Line();
	~Input_Line() = default;
};

