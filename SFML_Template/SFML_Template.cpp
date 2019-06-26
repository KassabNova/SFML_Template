#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main()
{
	RenderWindow app(VideoMode(256, 256), "15-Puzzle!");
	app.setFramerateLimit(60);

	Texture t;
	t.loadFromFile("15.png");

	int w = 64;
	int grid[6][6] = { 0 };
	Sprite sprite[20];

	int n = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			n++;
			sprite[n].setTexture(t);
			sprite[n].setTextureRect(IntRect(i * w, j * w, w, w));
			grid[i + 1][j + 1] = n;
		}

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();

			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left)
				{
					Vector2i pos = Mouse::getPosition(app);
					int x = pos.x / w + 1;
					int y = pos.y / w + 1;

					int dx = 0;
					int dy = 0;

					if (grid[x + 1][y] == 16) { dx = 1; dy = 0; };
					if (grid[x][y + 1] == 16) { dx = 0; dy = 1; };
					if (grid[x][y - 1] == 16) { dx = 0; dy = -1; };
					if (grid[x - 1][y] == 16) { dx = -1; dy = 0; };

					int n = grid[x][y];
					grid[x][y] = 16;
					grid[x + dx][y + dy] = n;

					//animation
					sprite[16].move(-dx * w, -dy * w);
					float speed = 3;

					for (int i = 0; i < w; i += speed)
					{
						sprite[n].move(speed * dx, speed * dy);
						app.draw(sprite[16]);
						app.draw(sprite[n]);
						app.display();
					}
				}

		}

		app.clear(Color::White);
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				int n = grid[i + 1][j + 1];
				sprite[n].setPosition(i * w, j * w);
				app.draw(sprite[n]);
			}

		app.display();
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
