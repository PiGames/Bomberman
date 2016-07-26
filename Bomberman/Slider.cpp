#include "Slider.h"


Slider::Slider(sliderOrientation orientation, sf::Vector2f beltBeginPosition, float beltLenght, int beltThickness, float sliderBeginXPosition, float sliderLenght, int sliderThickness, int grasperThickness, sf::Color beltColor, sf::Color sliderColor, sf::Color sliderAfterGrasperColor, sf::Color grasperColor, bool shadowEffect)
{
	value = 0;

	sliderOrient = orientation;

	oldMousePositionX = 0;
	oldMousePositionY = 0;
	mouseButtonPressed = false;

	belt = new sf::RectangleShape();
	slider = new sf::RectangleShape();
	sliderAfterGrasper = new sf::RectangleShape();
	grasper = new sf::RectangleShape();

	switch (orientation)
	{
		//poziomy
		case Slider::sliderOrientation::horizontal:
			belt->setPosition(beltBeginPosition);
			belt->setSize(sf::Vector2f(beltLenght, beltThickness));

			slider->setPosition(sliderBeginXPosition, beltBeginPosition.y + beltThickness / 2.f - sliderThickness / 2.f);
			slider->setSize(sf::Vector2f(sliderLenght, sliderThickness));

			grasper->setPosition(sliderBeginXPosition, slider->getPosition().y);
			grasper->setSize(sf::Vector2f(grasperThickness, sliderThickness));

			sliderAfterGrasper->setSize(sf::Vector2f(sliderLenght, sliderThickness));
			sliderAfterGrasper->setPosition(sliderBeginXPosition, beltBeginPosition.y + beltThickness / 2.f - sliderThickness / 2.f);

		break;

		case Slider::sliderOrientation::vertical:
			belt->setPosition(beltBeginPosition);
			belt->setSize(sf::Vector2f(beltThickness, beltLenght));

			slider->setPosition(beltBeginPosition.x + beltThickness / 2.f - sliderThickness / 2.f, sliderBeginXPosition);
			slider->setSize(sf::Vector2f(sliderThickness, sliderLenght));

			grasper->setPosition(slider->getPosition().x, slider->getPosition().y);
			grasper->setSize(sf::Vector2f(sliderThickness, grasperThickness));

			sliderAfterGrasper->setPosition(beltBeginPosition.x + beltThickness / 2.f - sliderThickness / 2.f, slider->getPosition().y);
			sliderAfterGrasper->setSize(sf::Vector2f(sliderThickness, sliderLenght));

		break;
	}
	
	belt->setFillColor(beltColor);
	slider->setFillColor(sliderColor);
	grasper->setFillColor(grasperColor);
	sliderAfterGrasper->setFillColor(sliderAfterGrasperColor);

}

Slider::~Slider()
{
	delete belt;
	delete slider;
	delete grasper;
	delete sliderAfterGrasper;
}

void Slider::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*belt,states);
	target.draw(*slider, states);
	target.draw(*sliderAfterGrasper, states);
	target.draw(*grasper, states);
}

void Slider::Update(sf::Vector2i mousePos, sf::Event* eventPoitner)
{
	if (grasper->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) || mouseButtonPressed)
	{
		if (eventPoitner->type == sf::Event::MouseButtonPressed)
		{
			if (eventPoitner->mouseButton.button == sf::Mouse::Left)
			{
				oldMousePositionX = mousePos.x;
				oldMousePositionY = mousePos.y;
				mouseButtonPressed = true;
			}

		}

		if (eventPoitner->type == sf::Event::MouseButtonReleased)
		{
			if (eventPoitner->mouseButton.button == sf::Mouse::Left)
			{
				mouseButtonPressed = false;
			}
		}

		if (eventPoitner->type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (sliderOrient == sliderOrientation::horizontal)
			{
				if (grasper->getPosition().x + eventPoitner->mouseMove.x - oldMousePositionX + grasper->getSize().x <= slider->getPosition().x + slider->getSize().x && grasper->getPosition().x + eventPoitner->mouseMove.x - oldMousePositionX >= slider->getPosition().x)
				{
					float grasperOldXPos = grasper->getPosition().x;
					grasper->setPosition(grasper->getPosition().x + eventPoitner->mouseMove.x - oldMousePositionX, grasper->getPosition().y);
					sliderAfterGrasper->setPosition(grasper->getPosition().x, sliderAfterGrasper->getPosition().y);
					sliderAfterGrasper->setSize(sf::Vector2f(sliderAfterGrasper->getSize().x - (grasper->getPosition().x - grasperOldXPos), sliderAfterGrasper->getSize().y));
					oldMousePositionX = eventPoitner->mouseMove.x;

					value = (grasper->getPosition().x + (grasper->getSize().x / 2.f) - slider->getPosition().x) / (slider->getSize().x);
					std::cout << "value: " << value << "\n";
				}
			}
			else if (sliderOrient == sliderOrientation::vertical)
			{
				if (grasper->getPosition().y + eventPoitner->mouseMove.y - oldMousePositionY + grasper->getSize().y <= slider->getPosition().y + slider->getSize().y && grasper->getPosition().y + eventPoitner->mouseMove.y - oldMousePositionY >= slider->getPosition().y)
				{
					float grasperOldYPos = grasper->getPosition().y;
					grasper->setPosition(grasper->getPosition().x, grasper->getPosition().y + eventPoitner->mouseMove.y - oldMousePositionY);
					sliderAfterGrasper->setPosition(sliderAfterGrasper->getPosition().x, grasper->getPosition().y);
					sliderAfterGrasper->setSize(sf::Vector2f(sliderAfterGrasper->getSize().x, sliderAfterGrasper->getSize().y - (grasper->getPosition().y - grasperOldYPos)));
					oldMousePositionY = eventPoitner->mouseMove.y;

					value = (grasper->getPosition().y + (grasper->getSize().y / 2.f) - slider->getPosition().y) / (slider->getSize().y);
					std::cout << "value: " << value << "\n";
				}
			}
			
			
		}

	}
}

void Slider::SetValue(float value)
{
	float grasperOldXPos = 0;
	float newX = 0;
	float grasperOldYPos = 0;
	float newY = 0;

	switch (sliderOrient)
	{
		case sliderOrientation::horizontal:
			grasperOldXPos = grasper->getPosition().x;
			newX = slider->getPosition().x - grasper->getSize().x/2.f + (slider->getSize().x * value);
			grasper->setPosition(newX, grasper->getPosition().y);
			sliderAfterGrasper->setPosition(grasper->getPosition().x, sliderAfterGrasper->getPosition().y);
			sliderAfterGrasper->setSize(sf::Vector2f(sliderAfterGrasper->getSize().x - (grasper->getPosition().x - grasperOldXPos), sliderAfterGrasper->getSize().y));
		break;
		case sliderOrientation::vertical:
			grasperOldYPos = grasper->getPosition().y;
			newY = slider->getPosition().y - grasper->getSize().y / 2.f + (slider->getSize().y * value);
			grasper->setPosition(grasper->getPosition().x,newY);
			sliderAfterGrasper->setPosition(sliderAfterGrasper->getPosition().x, grasper->getPosition().y);
			sliderAfterGrasper->setSize(sf::Vector2f(sliderAfterGrasper->getSize().x, sliderAfterGrasper->getSize().y - (grasper->getPosition().y - grasperOldYPos)));
		break;
	}
}

float Slider::GetValue() const
{
	return value;
}