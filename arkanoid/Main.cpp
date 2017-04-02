#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

constexpr unsigned int windowWidth{ 800 }, windowHeight{ 600 };
constexpr float ballRadius{ 10.f }, ballVelocity{8.f};
constexpr float paddelWidth{ 60.f }, paddelHeight{ 20.f }, paddleVelocity{ 6.f };

struct Ball
{
	CircleShape shape;

	Vector2f velocity{ -ballVelocity, -ballVelocity };

	Ball(float mX, float mY)
	{
		shape.setPosition(mX, mY);
		shape.setRadius(ballRadius);
		shape.setFillColor(Color::Red);
		shape.setOrigin(ballRadius, ballRadius);
	}

	void update()
	{
		shape.move(velocity);
		if (left() < 0) velocity.x = ballVelocity;
		else if (right() > windowWidth) velocity.x = -ballVelocity;

		if (top() < 0) velocity.y = ballVelocity;
		else if (bottom() > windowHeight) velocity.y = -ballVelocity;
	}

	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getRadius(); }
	float right() { return x() + shape.getRadius(); }
	float top() { return y() - shape.getRadius(); }
	float bottom() { return y() + shape.getRadius(); }
};

struct Paddle
{
	RectangleShape shape;
	Vector2f velocity;

	Paddle(float mX, float mY)
	{
		shape.setPosition(mX, mY);
		shape.setSize({paddelWidth, paddelHeight });
		shape.setFillColor(Color::Red);
		shape.setOrigin(paddelWidth/2, paddelHeight/2);
	}

	void update()
	{
		shape.move(velocity);
		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0) velocity.x = -paddleVelocity;
		else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < windowWidth) velocity.x = paddleVelocity;
		else velocity.x = 0;
	}

	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getSize().x / 2.f; }
	float right() { return x() + shape.getSize().x / 2.f; }
	float top() { return y() - shape.getSize().y / 2.f; }
	float bottom() { return y() + shape.getSize().y / 2.f; }
};

template<class T1, class T2> bool isIntersecting(T1& mA, T2& mB)
{
	return	mA.right() >= mB.left() && mA.left() <= mB.right()
			&& mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

void testCollision(Paddle& mPaddle, Ball& mBall)
{
	if (!isIntersecting(mPaddle, mBall)) return;

	mBall.velocity.y = -ballVelocity;

	if (mBall.x() < mPaddle.x()) mBall.velocity.x = -ballVelocity;
	else  mBall.velocity.x = ballVelocity;
}

int main(int argc, char** argv) 
{
	Ball ball{ windowWidth / 2,windowHeight / 2 };
	Paddle paddle{ windowWidth / 2,windowHeight -50 };
	RenderWindow window{ { windowWidth, windowHeight }, "Arkanoid - 1" };
	window.setFramerateLimit(60);

	while (true)
	{
		window.clear(Color::Black);
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;
		testCollision(paddle, ball);
		ball.update();
		paddle.update();
		
		window.draw(ball.shape);
		window.draw(paddle.shape);
		window.display();
	}
}