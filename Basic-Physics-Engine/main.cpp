#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <chrono>
#include <thread>

enum class EXITS
{
	MANUALLY_EXITED
};

int MANUALLY_EXITED = static_cast<int>(EXITS::MANUALLY_EXITED);

int main()
{
	while (true)
	{
		sf::ContextSettings settings;
		settings.antialiasingLevel = 16;

		sf::RenderWindow menu(sf::VideoMode::getDesktopMode(), "Menu", sf::Style::None, settings);

		sf::Font arial;

		arial.loadFromFile("res/fonts/arial.ttf");

		sf::Text verticalDInput("Drop height:", arial, 24);
		sf::Text iVerticalAccInput("Vertical acceleration:", arial, 24);
		sf::Text verticalJerkInput("Vertical jerk:", arial, 24);
		sf::Text iHorizontalAccInput("Horizontal acceleration:", arial, 24);
		sf::Text horizontalJerkInput("Horizontal jerk:", arial, 24);

		verticalDInput.setFillColor(sf::Color::Color (255, 255, 255));
		iVerticalAccInput.setFillColor(sf::Color::Color(255, 255, 255));
		verticalJerkInput.setFillColor(sf::Color::Color(255, 255, 255));
		iHorizontalAccInput.setFillColor(sf::Color::Color(255, 255, 255));
		horizontalJerkInput.setFillColor(sf::Color::Color(255, 255, 255));

		int dataNumber{ 1 };
		float menuHorizontalSpacing = 25;
		float menuVerticalSpacing = 25;

		verticalDInput.setPosition(menuHorizontalSpacing, menuVerticalSpacing);
		iVerticalAccInput.setPosition(menuHorizontalSpacing, menuVerticalSpacing + 30);
		verticalJerkInput.setPosition(menuHorizontalSpacing, menuVerticalSpacing + 60);
		iHorizontalAccInput.setPosition(menuHorizontalSpacing, menuVerticalSpacing + 90);
		horizontalJerkInput.setPosition(menuHorizontalSpacing, menuVerticalSpacing + 120);

		double verticalD;
		double iVerticalAcc;
		double verticalJerk;
		double iHorizontalAcc;
		double horizontalJerk;

		std::string input;
		sf::Text inputtext(input, arial, 24);
		inputtext.setFillColor(sf::Color::Color(233, 249, 0));
		inputtext.setPosition(verticalDInput.getLocalBounds().width + 35, menuVerticalSpacing);
		//Opens menu
		while (menu.isOpen())
		{
			sf::Event menuEvent;

			if (menu.pollEvent(menuEvent))
			{
				switch (menuEvent.type)
				{
				case sf::Event::Closed:
					menu.close();
					return MANUALLY_EXITED;

				case sf::Event::TextEntered:
					if (menuEvent.text.unicode == 8)
					{
						if (input.size() == 0)
						{
							break;
						}
						else {
							input = input.substr(0, input.size() - 1);
							inputtext.setString(input);
						}
					}
					else if (menuEvent.text.unicode == 13)
					{
						if (dataNumber == 1)
						{
							verticalD = std::stod(input);
							inputtext.setPosition(iVerticalAccInput.getLocalBounds().width + 33, menuVerticalSpacing + 30);
							verticalDInput.setString("Drop height: " + input);
						}
						else if (dataNumber == 2)
						{
							iVerticalAcc = std::stod(input);
							inputtext.setPosition(verticalJerkInput.getLocalBounds().width + 33, menuVerticalSpacing + 60);
							iVerticalAccInput.setString("Vertical acceleration: " + input);
						}
						else if (dataNumber == 3)
						{
							verticalJerk = std::stod(input);
							inputtext.setPosition(iHorizontalAccInput.getLocalBounds().width + 35, menuVerticalSpacing + 90);
							verticalJerkInput.setString("Vertical jerk: " + input);
						}
						else if (dataNumber == 4)
						{
							iHorizontalAcc = std::stod(input);
							inputtext.setPosition(horizontalJerkInput.getLocalBounds().width + 35, menuVerticalSpacing + 120);
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
					else if (menuEvent.text.unicode <= 57 && menuEvent.text.unicode >= 48)
					{
						input += menuEvent.text.unicode;
						inputtext.setString(input);
						std::cout << input << std::endl;
					}
					else if (menuEvent.text.unicode == 32)
					{
						menu.close();
						return MANUALLY_EXITED;
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
		myWindow.clear(sf::Color::Blue);
		int windowHeight = myWindow.getSize().y;

		double circlesize = windowHeight / verticalD;

		sf::CircleShape circle(circlesize);
		circle.setFillColor(sf::Color::White);
		circle.setPointCount(1000);
		circle.setOrigin(circle.getRadius(), 2 * circle.getRadius());
		circle.setPosition(0 - circle.getRadius(), 0);

		double timePassed, timeDiff, time1{ 0 };
		double verticalAcc, horizontalAcc;
		double verticalV, horizontalV;
		sf::Vector2i cursorPos;
		iVerticalAcc = iVerticalAcc * circlesize;
		iHorizontalAcc = iHorizontalAcc * circlesize;

		sf::Text verticalVDisplay("Vertical Velocity: ", arial, 24);
		verticalVDisplay.setFillColor(sf::Color::Color(255, 255, 255));
		verticalVDisplay.setPosition(menuHorizontalSpacing, menuVerticalSpacing);
		sf::Text horizontalVDisplay("Horizontal Velocity: ", arial, 24);
		horizontalVDisplay.setFillColor(sf::Color::Color(255, 255, 255));
		horizontalVDisplay.setPosition(menuHorizontalSpacing, menuVerticalSpacing + 30);
		sf::Text verticalAccDisplay("Vertical Acceleration: ", arial, 24);
		verticalAccDisplay.setFillColor(sf::Color::Color(255, 255, 255));
		verticalAccDisplay.setPosition(menuHorizontalSpacing, menuVerticalSpacing + 60);
		sf::Text horizontalAccDisplay("Horizontal Acceleration: ", arial, 24);
		horizontalAccDisplay.setFillColor(sf::Color::Color(255, 255, 255));
		horizontalAccDisplay.setPosition(menuHorizontalSpacing, menuVerticalSpacing + 90);

		sf::Clock clock;
		//Simulation starts
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
						return MANUALLY_EXITED;
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
				verticalVDisplay.setString("Vertical Velocity: " + std::to_string(verticalV / 10) + "m/s");
				horizontalVDisplay.setString("Horizontal Velocity: " + std::to_string(horizontalV / 10) +  "0m/s");
				//horizontalVDisplay.setString("Vertical Acceleration: " + std::to_string(verticalAcc / 10) + "0m/s^2");
				//verticalAccDisplay.setString("Horizontal Acceleration: " + std::to_string(horizontalAcc / 10) + "0m/s^2");
				circle.move(horizontalV * timeDiff, verticalV * timeDiff);
			}
			else if (circle.getPosition().y > windowHeight)
			{
				verticalVDisplay.setString("Vertical Velocity: 0m/s");
				horizontalVDisplay.setString("Horizontal Velocity: 0m/s");
				verticalAccDisplay.setString("Vertical Acceleration: 0m/s^2");
				horizontalAccDisplay.setString("Horizontal Acceleration: 0m/s^2");
				myWindow.clear(sf::Color::Blue);
				myWindow.draw(circle);
				myWindow.draw(verticalVDisplay);
				myWindow.draw(horizontalVDisplay);
				myWindow.draw(verticalAccDisplay);
				myWindow.draw(horizontalAccDisplay);
				myWindow.display();
				circle.move(0, 0);
				std::this_thread::sleep_for(std::chrono::seconds(3));
				myWindow.close();
			}

			time1 = timePassed;

			sf::Color circleColor(255, 255, 255);
			circleColor.r += 1;
			circle.setFillColor(circleColor);

			myWindow.clear(sf::Color::Blue);
			myWindow.draw(circle);
			myWindow.draw(verticalVDisplay);
			myWindow.draw(horizontalVDisplay);
			myWindow.draw(verticalAccDisplay);
			myWindow.draw(horizontalAccDisplay);
			myWindow.display();
		}
	}
	return MANUALLY_EXITED;
}