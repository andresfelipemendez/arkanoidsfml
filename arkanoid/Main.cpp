#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

constexpr unsigned int windowWidth{ 800 }, windowHeight{ 600 };

int main(int argc, char** argv) 
{
	RenderWindow window{ { windowWidth, windowHeight }, "Arkanoid - 1" };
	window.setFramerateLimit(60);

	while (true)
	{
		window.clear(Color::Black);
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;
		window.display();
	}
}