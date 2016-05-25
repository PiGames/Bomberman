#pragma once
#include <SFML\Graphics.hpp>


class Ray :public sf::Drawable
{
private:
	void draw(sf::RenderWindow&, sf::RenderStates) const;

public:
	Ray();
	~Ray();

	/// Check is anything coliding with ray
	/// <param name="floatRect"> collider of an object</param>
	/// <returns>true when is collision</returns>
	/// <returns>false when isn't collision</returns>
	bool Contains(sf::FloatRect & floatRect);

private:
	/// True - horizontal, false - vertical
	bool m_orientation;
	sf::Sprite m_sprite;
	std::vector<int> m_sections;

};

