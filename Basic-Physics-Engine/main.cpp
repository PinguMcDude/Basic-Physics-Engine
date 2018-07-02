#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <iomanip>

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
	circle.setPosition(myWindow.getSize().x / 2, 0);

	double time;
	double verticalDrop;
	double verticalAcc;
	double horizontalAcc;
	double horizontalMove;
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
				}
			}
		}

		time = clock.getElapsedTime().asSeconds();

		verticalAcc = iVerticalAcc + (verticalJerk * time);
		verticalDrop = (verticalAcc * (pow(time, 2))) / 2;

		horizontalAcc = iHorizontalAcc + (horizontalJerk * time);
		horizontalMove = (horizontalAcc * (pow(time, 2))) / 2;

		if (verticalDrop <= windowHeight)
		{
			circle.setPosition(horizontalMove, verticalDrop);
		}
		else if (verticalDrop > windowHeight)
		{
			circle.setPosition(horizontalMove, windowHeight);
		}

		myWindow.clear(sf::Color::Blue);
		myWindow.draw(circle);
		myWindow.display();
	}
	return 0;
}