
class Ball {
public:

	sf::Vector2f position;
	sf::Vector2f lastPosition;
	sf::Vector2f acceleration;
	float radius; //The radius represents the mass
	sf::Color color;
	
	void update(float deltaTime) {
		sf::Vector2f displacement = position - lastPosition;
		lastPosition = position;
		position += displacement + acceleration * deltaTime * deltaTime;
		acceleration = {};
	}

	Ball(sf::Vector2f position, float radius) : position(position), radius(radius) {}
	
};

class Solver {
private:
	float energyConservationFactor = 0.75f;

	float mouseRadius = 30;
	
public:
	std::vector<Ball> balls;

	Ball& addBall(sf::Vector2f position, float radius) {
		return balls.emplace_back(position, radius);
	}

	void update(sf::RenderWindow& window) {
		for (int i = 8; i--;) {
			applyGravity();
			checkCollsisions(window);
			checkConstraints();
			updateBalls((1 / 60.0f) / 8);
		}
	}

	void applyGravity() {
		for (Ball& ball : balls) {
			ball.acceleration.y += 981.0f;
		}
	}

	void checkCollsisions(sf::RenderWindow& window) {
		
		bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);
		
		for (int i = 0; i < balls.size(); i++) {
			auto& ballA = balls[i];
			if (mousePressed) {
				Ball ballB = Ball(sf::Vector2f(sf::Mouse::getPosition(window)), mouseRadius);
				const sf::Vector2f delta = ballA.position - ballB.position;
				const float distanceSQR = delta.x * delta.x + delta.y * delta.y;
				const float minDist = ballA.radius + ballB.radius;
				if (distanceSQR < minDist * minDist) {
					const float distance = sqrt(distanceSQR);
					const sf::Vector2f normal = delta / distance;

					const float overlap = 0.5f * energyConservationFactor * (distance - minDist);

					ballA.position -= normal * overlap;
				}
			}
			for (int j = i + 1; j < balls.size(); j++) {
				auto& ballB = balls[j];
				const sf::Vector2f delta = ballA.position - ballB.position;
				const float distanceSQR = delta.x * delta.x + delta.y * delta.y;
				const float minDist = ballA.radius + ballB.radius;
				if (distanceSQR < minDist * minDist) {
					const float distance = sqrt(distanceSQR);
					const sf::Vector2f normal = delta / distance;
					const float massRatioA = ballA.radius / (minDist);
					const float massRatioB = ballB.radius / (minDist);
					const float overlap = 0.5f * energyConservationFactor * (distance - minDist);
					
					ballA.position -= normal * overlap * massRatioB;
					ballB.position += normal * overlap * massRatioA;
				}
			}			
		}
	}

	void checkConstraints() {
		for (Ball& ball : balls) {
			//If the ball is outside the center circle with r = 470
			sf::Vector2f vectorToCenter = ball.position - sf::Vector2f(500, 500);
			float distanceToCenter = sqrt(vectorToCenter.x * vectorToCenter.x + vectorToCenter.y * vectorToCenter.y);
			if (distanceToCenter > 470 - ball.radius) {
				sf::Vector2f normal = vectorToCenter / distanceToCenter;
				ball.position = sf::Vector2f(500, 500) + normal * (470 - ball.radius);
			}
		}
	}

	void updateBalls(float deltaTime) {
		for (Ball& ball : balls) {
			ball.update(deltaTime);
		}
	}

};