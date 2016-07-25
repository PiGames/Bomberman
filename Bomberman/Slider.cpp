#include "Slider.h"


Slider::Slider(sliderOrientation orientation, sf::Vector2f beltBeginPosition, float beltLenght, int beltThickness, float sliderBeginXPosition, float sliderLenght, int sliderThickness, int grasperThickness, sf::Color beltColor, sf::Color sliderColor, sf::Color sliderAfterGrasperColor, sf::Color grasperColor, bool shadowEffect)
{
	value = 0;

	sliderOrient = orientation;

	oldMousePositionX = 0;
	oldMousePositionY = 0;
	mouseButtonPressed = false;

	belt = std::make_unique<sf::RectangleShape>();
	slider = std::make_unique<sf::RectangleShape>();
	sliderAfterGrasper = std::make_unique<sf::RectangleShape>();
	grasper = std::make_unique<sf::RectangleShape>();

	switch (orientation)
	{
		//poziomy
		case Slider::sliderOrientation::horizontal:
			belt.get()->setPosition(beltBeginPosition);
			belt.get()->setSize(sf::Vector2f(beltLenght, beltThickness));

			slider.get()->setPosition(sliderBeginXPosition, beltBeginPosition.y + beltThickness / 2.f - sliderThickness / 2.f);
			slider.get()->setSize(sf::Vector2f(sliderLenght, sliderThickness));

			grasper.get()->setPosition(sliderBeginXPosition, slider.get()->getPosition().y);
			grasper.get()->setSize(sf::Vector2f(grasperThickness, sliderThickness));

			sliderAfterGrasper.get()->setSize(sf::Vector2f(sliderLenght, sliderThickness));
			sliderAfterGrasper.get()->setPosition(sliderBeginXPosition, beltBeginPosition.y + beltThickness / 2.f - sliderThickness / 2.f);

		break;

		case Slider::sliderOrientation::vertical:
			belt.get()->setPosition(beltBeginPosition);
			belt.get()->setSize(sf::Vector2f(beltThickness, beltLenght));

			slider.get()->setPosition(beltBeginPosition.x + beltThickness / 2.f - sliderThickness / 2.f, sliderBeginXPosition);
			slider.get()->setSize(sf::Vector2f(sliderThickness, sliderLenght));

			grasper.get()->setPosition(slider.get()->getPosition().x, slider.get()->getPosition().y);
			grasper.get()->setSize(sf::Vector2f(sliderThickness, grasperThickness));

			sliderAfterGrasper.get()->setPosition(beltBeginPosition.x + beltThickness / 2.f - sliderThickness / 2.f, slider.get()->getPosition().y);
			sliderAfterGrasper.get()->setSize(sf::Vector2f(sliderThickness, sliderLenght));

		break;
	}
	
	belt.get()->setFillColor(beltColor);
	slider.get()->setFillColor(sliderColor);
	grasper.get()->setFillColor(grasperColor);
	sliderAfterGrasper.get()->setFillColor(sliderAfterGrasperColor);

}

Slider::~Slider()
{
}

void Slider::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*belt.get(),states);
	target.draw(*slider.get(), states);
	target.draw(*sliderAfterGrasper, states);
	target.draw(*grasper.get(), states);
}

void Slider::Update(sf::Vector2i mousePos, sf::Event* eventPoitner)
{
	if (grasper.get()->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) || mouseButtonPressed)
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
				if (grasper.get()->getPosition().x + eventPoitner->mouseMove.x - oldMousePositionX + grasper.get()->getSize().x <= slider.get()->getPosition().x + slider.get()->getSize().x && grasper.get()->getPosition().x + eventPoitner->mouseMove.x - oldMousePositionX >= slider.get()->getPosition().x)
				{
					float grasperOldXPos = grasper.get()->getPosition().x;
					grasper.get()->setPosition(grasper.get()->getPosition().x + eventPoitner->mouseMove.x - oldMousePositionX, grasper.get()->getPosition().y);
					sliderAfterGrasper.get()->setPosition(grasper.get()->getPosition().x, sliderAfterGrasper.get()->getPosition().y);
					sliderAfterGrasper.get()->setSize(sf::Vector2f(sliderAfterGrasper.get()->getSize().x - (grasper.get()->getPosition().x - grasperOldXPos), sliderAfterGrasper.get()->getSize().y));
					oldMousePositionX = eventPoitner->mouseMove.x;

					value = (grasper.get()->getPosition().x + (grasper.get()->getSize().x / 2.f) - slider.get()->getPosition().x) / (slider.get()->getSize().x);
					std::cout << "value: " << value << "\n";
				}
			}
			else if (sliderOrient == sliderOrientation::vertical)
			{
				if (grasper.get()->getPosition().y + eventPoitner->mouseMove.y - oldMousePositionY + grasper.get()->getSize().y <= slider.get()->getPosition().y + slider.get()->getSize().y && grasper.get()->getPosition().y + eventPoitner->mouseMove.y - oldMousePositionY >= slider.get()->getPosition().y)
				{
					float grasperOldYPos = grasper.get()->getPosition().y;
					grasper.get()->setPosition(grasper.get()->getPosition().x, grasper.get()->getPosition().y + eventPoitner->mouseMove.y - oldMousePositionY);
					sliderAfterGrasper.get()->setPosition(sliderAfterGrasper.get()->getPosition().x, grasper.get()->getPosition().y);
					sliderAfterGrasper.get()->setSize(sf::Vector2f(sliderAfterGrasper.get()->getSize().x, sliderAfterGrasper.get()->getSize().y - (grasper.get()->getPosition().y - grasperOldYPos)));
					oldMousePositionY = eventPoitner->mouseMove.y;

					value = (grasper.get()->getPosition().y + (grasper.get()->getSize().y / 2.f) - slider.get()->getPosition().y) / (slider.get()->getSize().y);
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
			grasperOldXPos = grasper.get()->getPosition().x;
			newX = slider.get()->getPosition().x - grasper.get()->getSize().x/2.f + (slider.get()->getSize().x * value);
			grasper.get()->setPosition(newX, grasper.get()->getPosition().y);
			sliderAfterGrasper.get()->setPosition(grasper.get()->getPosition().x, sliderAfterGrasper.get()->getPosition().y);
			sliderAfterGrasper.get()->setSize(sf::Vector2f(sliderAfterGrasper.get()->getSize().x - (grasper.get()->getPosition().x - grasperOldXPos), sliderAfterGrasper.get()->getSize().y));
		break;
		case sliderOrientation::vertical:
			grasperOldYPos = grasper.get()->getPosition().y;
			newY = slider.get()->getPosition().y - grasper.get()->getSize().y / 2.f + (slider.get()->getSize().y * value);
			grasper.get()->setPosition(grasper.get()->getPosition().x,newY);
			sliderAfterGrasper.get()->setPosition(sliderAfterGrasper.get()->getPosition().x, grasper.get()->getPosition().y);
			sliderAfterGrasper.get()->setSize(sf::Vector2f(sliderAfterGrasper.get()->getSize().x, sliderAfterGrasper.get()->getSize().y - (grasper.get()->getPosition().y - grasperOldYPos)));
		break;
	}
}

float Slider::GetValue() const
{
	return value;
}