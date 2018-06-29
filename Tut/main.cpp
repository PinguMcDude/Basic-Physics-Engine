#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <iomanip>

int main()
{
	float acceleration;
	std::cout << "Input the initial acceleration\n";
	std::cin >> acceleration;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::VideoMode fullscreen = sf::VideoMode::getDesktopMode();
	sf::RenderWindow myWindow(fullscreen, "My Window", sf::Style::None, settings);

	float height = myWindow.getSize().y;

	sf::CircleShape circle(100);
	circle.setFillColor(sf::Color::Magenta);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(myWindow.getSize().x / 2, 0 - circle.getRadius());
	
	double time;
	double distanceFallen;
	double newposition;

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
		distanceFallen = (acceleration * (pow(time, 2)))/ 2;

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