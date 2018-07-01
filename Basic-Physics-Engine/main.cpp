#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <iomanip>

int main()
{
	double heightM; 
	std::cout << "Input the height (Between 1 - 100)\n";
	std::cin >> heightM;

	double iacceleration;
	std::cout << "Input the initial acceleration\n";
	std::cin >> iacceleration;

	double jerk;
	std::cout << "Input the jerk\n";
	std::cin >> jerk;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::VideoMode fullscreen = sf::VideoMode::getDesktopMode();
	sf::RenderWindow myWindow(fullscreen, "My Window", sf::Style::None, settings);

	float height = myWindow.getSize().y;

	double circlesize;
	circlesize = height / heightM;

	sf::CircleShape circle(circlesize);
	circle.setFillColor(sf::Color::Magenta);
	circle.setPointCount(100);
	circle.setOrigin(circle.getRadius(), 2 * circle.getRadius());

	double time;
	double distanceFallen;
	double newposition;
	double newAcc;

	iacceleration = iacceleration * circlesize;

	sf::Clock clock;

	while (myWindow.isOpen())
	{
		sf::Event event;
		if (myWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				myWindow.close();

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Space)
				{
					myWindow.close();
				}
			}
		}

		time = clock.getElapsedTime().asSeconds();

		newAcc = iacceleration + (jerk * time);

		distanceFallen = (newAcc * (pow(time, 2))) / 2;

		if (distanceFallen <= height)
		{
			circle.setPosition(myWindow.getSize().x / 2, distanceFallen);
		}
		else if (distanceFallen > height)
		{
			circle.setPosition(myWindow.getSize().x / 2, height);
		}

		myWindow.clear(sf::Color::Blue);
		myWindow.draw(circle);
		myWindow.display();
	}
	return 0;
}