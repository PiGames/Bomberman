#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>
#include <iostream>
class Slider :
	public sf::Drawable
{
public:
	enum sliderOrientation{vertical,horizontal};
	Slider(sliderOrientation orientation,sf::Vector2f beltBeginPosition, float beltLenght, int beltThickness, float sliderBeginXPosition, float sliderLenght, int sliderThickness, int grasperThickness, sf::Color beltColor, sf::Color sliderColor, sf::Color sliderAfterGrasperColor, sf::Color grasperColor, bool shadowEffect);
	~Slider();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void Update(sf::Vector2i mousePos, sf::Event* eventPoitner);

	void SetValue(float value);
	float GetValue() const;

private:
	sf::RectangleShape* belt;
	decltype(belt) slider;
	decltype(belt) sliderAfterGrasper;
	decltype(belt) grasper;

	float oldMousePositionX;
	float oldMousePositionY;
	bool mouseButtonPressed;

	float value;
	sliderOrientation sliderOrient;
};

