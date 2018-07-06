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
	while (true)
	{
		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;

		sf::RenderWindow menu(sf::VideoMode(600, 600), "Menu", sf::Style::Titlebar | sf::Style::Close, settings);

		sf::Font arial;
		arial.loadFromFile("res/fonts/arial.ttf");

		sf::Text verticalDInput("Drop height:", arial, 24);
		sf::Text iVerticalAccInput("Vertical acceleration:", arial, 24);
		sf::Text verticalJerkInput("Vertical jerk:", arial, 24);
		sf::Text iHorizontalAccInput("Horizontal acceleration:", arial, 24);
		sf::Text horizontalJerkInput("Horizontal jerk:", arial, 24);

		verticalDInput.setFillColor(sf::Color::Color (255, 185, 10));
		iVerticalAccInput.setFillColor(sf::Color::Color(255, 185, 10));
		verticalJerkInput.setFillColor(sf::Color::Color(255, 185, 10));
		iHorizontalAccInput.setFillColor(sf::Color::Color(255, 185, 10));
		horizontalJerkInput.setFillColor(sf::Color::Color(255, 185, 10));

		int dataNumber{ 1 };

		verticalDInput.setPosition(0, 0);
		iVerticalAccInput.setPosition(0, 30);
		verticalJerkInput.setPosition(0, 60);
		iHorizontalAccInput.setPosition(0, 90);
		horizontalJerkInput.setPosition(0, 120);

		double verticalD;
		double iVerticalAcc;
		double verticalJerk;
		double iHorizontalAcc;
		double horizontalJerk;

		std::string input;
		sf::Text inputtext(input, arial, 24);
		inputtext.setPosition(verticalDInput.getLocalBounds().width + 10, 0);

		while (menu.isOpen())
		{
			sf::Event menuEvent;

			if (menu.pollEvent(menuEvent))
			{
				switch (menuEvent.type)
				{
				case sf::Event::Closed:
					menu.close();
					return 0;

				case sf::Event::TextEntered:
					if (menuEvent.text.unicode == 8)
					{
						if (input.size() == 0)
						{
							break;
						}
						else {
							input = input.substr(0, input.size() - 1);
						}
					}
					else if (menuEvent.text.unicode == 13)
					{
						if (dataNumber == 1)
						{
							verticalD = std::stod(input);
							inputtext.setPosition(iVerticalAccInput.getLocalBounds().width + 8, 30);
							verticalDInput.setString("Drop height: " + input);
						}
						else if (dataNumber == 2)
						{
							iVerticalAcc = std::stod(input);
							inputtext.setPosition(verticalJerkInput.getLocalBounds().width + 8, 60);
							iVerticalAccInput.setString("Vertical acceleration: " + input);
						}
						else if (dataNumber == 3)
						{
							verticalJerk = std::stod(input);
							inputtext.setPosition(iHorizontalAccInput.getLocalBounds().width + 10, 90);
							verticalJerkInput.setString("Vertical jerk: " + input);
						}
						else if (dataNumber == 4)
						{
							iHorizontalAcc = std::stod(input);
							inputtext.setPosition(horizontalJerkInput.getLocalBounds().width + 10, 120);
							iHorizontalAccInput.setString("Horizontal acceleration: " + input);
						}
						else if (dataNumber == 5)
						{
							horizontalJerk = std::stod(input);
							horizontalJerkInput.setString("Horizontal jerk: " + input);
							menu.close();
						}
						dataNumber++;
						inputtext.setString("");
						input = "";
					}
					else
					{
						input += menuEvent.text.unicode;
						inputtext.setString(input);
						std::cout << input << std::endl;
					}
				}
			}

			menu.clear(sf::Color::Blue);
			menu.draw(verticalDInput);
			menu.draw(iHorizontalAccInput);
			menu.draw(horizontalJerkInput);
			menu.draw(iVerticalAccInput);
			menu.draw(verticalJerkInput);
			menu.draw(inputtext);
			menu.display();
		}
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
			}

			time1 = timePassed;

			myWindow.clear(sf::Color::Blue);
			myWindow.draw(circle);
			myWindow.display();
		}
	}
	return 0;
}