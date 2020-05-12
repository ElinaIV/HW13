#include <iostream>
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

const auto width = 800U;
const auto height = 600U;

class Molecula {
public:
	float x, y, dx, dy;
	float r;

	Molecula() {
		dx = gen_from_to(0, 15);
		dy = gen_from_to(0, 15);
		r = 3.0f;
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

int main() {
	std::vector<Molecula*> moleculs;
	int count = 15;
	for (int i = 0; i < count; i++) {
		moleculs.push_back(new Molecula());
	}

	sf::RenderWindow window{ sf::VideoMode(width, height), "BROWN" };
	window.setFramerateLimit(90);
	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		for (auto m : moleculs) {
			m->move();
			m->draw(&window);
			window.display();
			window.clear();
		}

		window.display();
	}

	return 0;
}
