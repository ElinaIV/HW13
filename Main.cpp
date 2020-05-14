#include <iostream>
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

const auto width = 600U;
const auto height = 600U;
auto stepX = width / 10.0f;
auto stepY = height / 10.0f;

class Molecula {
public:
	float x, y, r;

	Molecula() : r{ 2.0f } {
		x = gen_from_to(10, width - 10);
		y = gen_from_to(10, height - 10);
	}

	void draw(sf::RenderWindow* window) {
		sf::CircleShape circle(2.0f * r);
		circle.setPosition(x, y);
		circle.setFillColor(sf::Color::Red);

		window->draw(circle);
	}

	float gen_from_to(float a, float b) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(a, b);

		return dis(gen);
	}

	void move() {
		if (x > width) x = 0; if (x < 0) x = width;
		if (y > height) y = 0; if (y < 0) y = height;
		x += gen_from_to(-10, 10);
		y += gen_from_to(-10, 10);
	}
};

bool isInside(Molecula* m, const unsigned int xPos, const unsigned int yPos) {
	return ((m->x < xPos) && (m->x > (xPos - stepX)) && (m->y < yPos) && (m->y > (yPos - stepY)));
}

int main() {
	std::vector<Molecula*> moleculs;
	double count = 20;
	for (int i = 0; i < count; i++) {
		moleculs.push_back(new Molecula());
	}

	sf::RenderWindow window{ sf::VideoMode(width, height), "BROWN!" };
	window.setFramerateLimit(40);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();
		for (auto i = stepX; i <= width; i += stepX) {
			for (auto j = stepY; j <= height; j += stepY) {
				double counter = 0;
				for (auto m : moleculs) {
					if (isInside(m, i, j)) {
						++counter;
					}
				}

				sf::RectangleShape rectangle;
				rectangle.setPosition(sf::Vector2f(i - stepX, j - stepY));
				rectangle.setSize(sf::Vector2f(stepX, stepY));
				rectangle.setFillColor(sf::Color(0, 255 * counter / count * 2.5f, 0));
				window.draw(rectangle);
			}
		}
		
		for (auto m : moleculs) {
			m->move();
			m->draw(&window);
		}
		window.display();
	}

	return 0;
}
