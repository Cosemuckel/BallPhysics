#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>
#include <Math.h>

#include "Helper.h"
#include "Solver.h"
#include "Renderer.h"


int main() {

	sf::RenderWindow window;
	window.create(sf::VideoMode(1000, 1000), "Ball Physics");
	window.setFramerateLimit(60);

	Renderer renderer(1000, 1000, 30);
	Solver solver;

	std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
	float deltaTime = 0;
	float time = 0;
	float timeSinceSpawn = 0;
	float spawnAngle = 3.1415f / 2;
	bool spawnAngleAdding = true;
	float spawnInterval = 0.1;

	bool wasMouseClicked = false;

	bool spawned = false;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTime).count() / 1000000.0f;
		time += deltaTime;

		solver.update(window);
		lastTime = currentTime;	
		timeSinceSpawn += deltaTime;
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || time < 20 && timeSinceSpawn > spawnInterval) {
			if (!wasMouseClicked) {
				timeSinceSpawn = 0;
				Ball& ball = solver.addBall(sf::Vector2f(500, 200), rand() % 20 + 3);
				ball.color = Rainbow::nextColor(time);
				ball.lastPosition = ball.position;
			}
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) wasMouseClicked = true;
		}
		else {
			wasMouseClicked = false;
		}

		if (time > 30 && !spawned) {
			spawned = true;
			Ball& ball = solver.addBall(sf::Vector2f(500, 200), 60);
			ball.color = sf::Color::Black;
			ball.lastPosition = ball.position - sf::Vector2f(0, 60);
		}

		window.clear(sf::Color(0x2d, 0x2d, 0x2d));
		
		renderer.render(window, solver);

		window.display();
	}

	return 0;

	
	
}

