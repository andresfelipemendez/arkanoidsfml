#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

int main(int argc, char** argv) 
{
	sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "window");
	sf::Event event;

	sf::Clock clock;
	auto color(sf::Color::Red);

	srand(time(nullptr));

	std::uniform_int_distribution<int> randomColorRange(0, 255);
	std::random_device rd;
	std::mt19937 randomNumbers(rd());
	while (renderWindow.isOpen())
	{
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed)
				renderWindow.close();

			if(event.type == sf::Event::EventType::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
					color.r = rand() % 255;
			}
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
				color.r = 0;
			else
				color.r = randomColorRange(randomNumbers);

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
				color.g = 0;
			else
				color.g = randomColorRange(randomNumbers);

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
				color.b = 0;
			else
				color.b = randomColorRange(randomNumbers);

		}

		std::cout << "Elapsed time in microseconds:" << clock.getElapsedTime().asMicroseconds() << std::endl;
		clock.restart();

		renderWindow.clear(color);
		renderWindow.display();
	}
	
}