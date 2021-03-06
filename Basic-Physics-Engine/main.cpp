#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <chrono>
#include <thread>

int main()
{
	double verticalD;
	std::cout << "Input the drop height (Between 1 - 100)\n";
	std::cin >> verticalD;

	double iVerticalAcc;
	std::cout << "Input the initial vertical acceleration\n";
	std::cin >> iVerticalAcc;

	double verticalJerk;
	std::cout << "Input the vertical acceleration jerk\n";
	std::cin >> verticalJerk;

	double iHorizontalAcc;
	std::cout << "Input the initial horizontal acceleration\n";
	std::cin >> iHorizontalAcc;

	double horizontalJerk;
	std::cout << "Input the horizontal jerk\n";
	std::cin >> horizontalJerk;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::VideoMode fullscreen = sf::VideoMode::getDesktopMode();
	sf::RenderWindow myWindow(fullscreen, "My Window", sf::Style::None, settings);

	int windowHeight = myWindow.getSize().y;

	double circlesize = windowHeight / verticalD;

	sf::CircleShape circle(circlesize);
	circle.setFillColor(sf::Color::Magenta);
	circle.setPointCount(100);
	circle.setOrigin(circle.getRadius(), 2 * circle.getRadius());
	circle.setPosition(0 - circle.getRadius(), 0);

	double timePassed, timeDiff, time1{ 0 };
	double verticalAcc, horizontalAcc;
	double verticalV, horizontalV;
	sf::Vector2i cursorPos;
	iVerticalAcc = iVerticalAcc * circlesize;
	iHorizontalAcc = iHorizontalAcc * circlesize;

	sf::Clock clock;

	while (myWindow.isOpen())
	{
		sf::Event event;

		if (myWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Space)
				{
					myWindow.close();
					return 0;
				}
			}

		}

		cursorPos = sf::Mouse::getPosition(myWindow);

		timePassed = clock.getElapsedTime().asSeconds();
		timeDiff = timePassed - time1;

		verticalAcc = iVerticalAcc + (verticalJerk * timePassed);
		verticalV = verticalAcc * timePassed;

		horizontalAcc = iHorizontalAcc + (horizontalJerk * timePassed);
		horizontalV = horizontalAcc * timePassed;

		if (circle.getPosition().y <= windowHeight)
		{
			circle.move(horizontalV * timeDiff, verticalV * timeDiff);
		}
		else if (circle.getPosition().y > windowHeight)
		{
			circle.move(0, 0);
			std::this_thread::sleep_for(std::chrono::seconds(3));
			myWindow.close();
			return 0;
		}

		time1 = timePassed;

		myWindow.clear(sf::Color::Blue);
		myWindow.draw(circle);
		myWindow.display();
	}
	return 0;
}