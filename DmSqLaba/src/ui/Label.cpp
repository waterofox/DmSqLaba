#include "Label.h"

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*text, states);
}

void Label::update(){}

void Label::update_resource(const std::variant<sf::Texture*, sf::Font*>& resource)
{
	text->setFont(*std::get<sf::Font*>(resource));
}

sf::FloatRect Label::get_component_render_bounds()
{
	return text->getGlobalBounds();
}

sf::FloatRect Label::get_component_bounds()
{
	return text->getGlobalBounds();
}

sf::Drawable* Label::as_drawable()
{
	return this;
}

Label::Label()
{
	text = new sf::Text(def_font,"");
	this->type_of_resource = Resource_Types::Font;
}

Label::Label(const Label& other) : Scene_Component(other), sf::Drawable(other)
{
	this->text = new sf::Text(*other.text);
}

Label& Label::operator=(const Label& other)
{
	if (this == &other) { return *this; }

	Scene_Component::operator=(other);
	sf::Drawable::operator=(other);

	if (this->text != nullptr)
	{
		delete text;
		text = nullptr;
	}

	this->text = new sf::Text(*other.text);

	return *this;
}

Label::~Label()
{
	delete text;
}
