#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>

int main(int argc, char** argv) 
{
	sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "window");
	sf::Event event;
	sf::Clock clock;
	std::unordered_map<int, bool> keys;
	std::list<int> changedKeys;

	while (renderWindow.isOpen())
	{
		changedKeys.clear();
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed)
				renderWindow.close();

			if(event.type == sf::Event::EventType::KeyPressed)
			{
				if(keys.count(event.key.code) == 0)
				{
					keys[event.key.code] = true;
					changedKeys.push_back(event.key.code);
				}
			}

			if (event.type == sf::Event::EventType::KeyReleased)
			{
				if (keys.count(event.key.code) == 1)
				{
					keys.erase(event.key.code);
					changedKeys.push_back(event.key.code);
				}
			}
		}
		
		//std::cout << "Elapsed time in microseconds: " << clock.getElapsedTime().asMicroseconds() << std::endl;
		std::cout << "Currently pressed keys: ";

		for (auto& keyValue : keys)
			std::cout << keyValue.first << " ";
		std::cout << std::endl;

		if(!changedKeys.empty())
			std::cout << "Changed keys !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << std::endl;

		clock.restart();

		renderWindow.clear();
		renderWindow.display();
	}
	
}