#pragma once

class Renderer {
	
private:
	unsigned int windowWidth;
	unsigned int windowHeight;
	unsigned int borderSize;

	
public:

	Renderer(unsigned int windowWidth, unsigned int windowHeight, unsigned int borderSize)
		: windowWidth(windowWidth), windowHeight(windowHeight), borderSize(borderSize) {}
	
	bool render(sf::RenderWindow& const window, const Solver& const solver) {
		//Draw a circle in the middle of the screen, with a radius of windowWidth / 2 - border
		sf::CircleShape circle;
		circle.setRadius(windowWidth / 2 - borderSize);
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineColor(sf::Color::White);
		circle.setOutlineThickness(2);
		circle.setPointCount(64);
		circle.setPosition(borderSize, borderSize);
		window.draw(circle);

		for (const Ball& const ball : solver.balls) {
			sf::CircleShape ballShape;
			ballShape.setRadius(ball.radius);
			ballShape.setFillColor(ball.color);
			ballShape.setOutlineColor(sf::Color::Transparent);
			ballShape.setPosition(ball.position - sf::Vector2f(ball.radius, ball.radius));
			window.draw(ballShape);
		}
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {

			sf::CircleShape ballShape;
			ballShape.setRadius(30);
			ballShape.setFillColor(sf::Color::Black);
			ballShape.setOutlineColor(sf::Color::Transparent);
			ballShape.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)) - sf::Vector2f(30, 30));
			window.draw(ballShape);

		}
		
		return true;
	}


};