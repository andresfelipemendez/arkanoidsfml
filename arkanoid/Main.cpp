#include <SFML/Graphics.hpp>

int main(int argc, char** argv) 
{
	sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "window");
	while (true)
	{
		renderWindow.clear();
		renderWindow.display();
	}
}