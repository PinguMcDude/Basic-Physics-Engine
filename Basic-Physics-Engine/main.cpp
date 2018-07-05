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

		std::string x;

		while (menu.isOpen())
		{
			sf::Event menuEvent;

			if (menu.pollEvent(menuEvent))
			{
				switch (menuEvent.type)
				{
				case sf::Event::Closed:
					menu.close();
					//Delete return 0; after testing
					return 0;
				case sf::Event::TextEntered:
					if (menuEvent.text.unicode == 8)
					{
						if (x.size() == 0)
						{
							break;
						}
						else {
							x = x.substr(0, x.size() - 1);
						}
					}
					else
					{
						x += menuEvent.text.unicode;
					}
					std::cout << x << std::endl;
				}
			}
			sf::Font arial;
			arial.loadFromFile("res/fonts/arial.ttf");

			sf::Text VerticalDInput("Drop height: ", arial, 24);
			sf::Text iVerticalAccInput("Vertical acceleration: ", arial, 24);
			sf::Text verticalJerkInput("Vertical Jerk: ", arial, 24);
			sf::Text iHorizontalAccInput("Horizontal acceleration: ", arial, 24);
			sf::Text horizontalJerkInput("Horizontal jerk: ", arial, 24);

			VerticalDInput.setPosition(0, 0);
			iVerticalAccInput.setPosition(0, 24);
			verticalJerkInput.setPosition(0, 48);
			iHorizontalAccInput.setPosition(0, 72);
			horizontalJerkInput.setPosition(0, 96);

			menu.clear(sf::Color::Black);
			menu.draw(VerticalDInput);
			menu.draw(iHorizontalAccInput);
			menu.draw(horizontalJerkInput);
			menu.draw(iVerticalAccInput);
			menu.draw(verticalJerkInput);
			menu.display();
		}
		/*		while (true)
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
				}
				*/
	}
	return 0;
}