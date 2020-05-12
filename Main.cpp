#include <iostream>
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>

auto width = 800U;
auto height = 600U;

class Molecula {
public:
	float x, y, dx, dy;
	float r;

	Molecula() {
		dx = 10;
		dy = 10;
		r = 3.0f;
		x = gen_from_to(10, width - 10);
		y = gen_from_to(10, height - 10);
		std::cout << "(" << x << " ; " << y << ")" << std::endl;
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
		x += dx;
		y += dy;
	}
};

int main() {

	std::vector<Molecula> moleculs;
	Molecula m;
	Molecula mm;
	moleculs.push_back(m);
	moleculs.push_back(mm);

	sf::RenderWindow window{ sf::VideoMode(width, height), "BROWN" };
	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();

		for (auto m : moleculs) {
			m.draw(&window);
			m.move();
		}

		window.display();
	}

	return 0;
}