#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>
#include <iostream>
using namespace sf;

const int width = 26;
const int length = 26;
int cnt = 0;
const int tile_size = 35;
int max_turns = 61;


enum colors { Yellow, Red, Green, Cyan, Blue, Magenta, White, Black };


//fills each square shape on board with a random color
void fillSquare(RectangleShape a[][width], int i, int j, int c) {
	
	switch (colors(c)) {
	case Yellow:
		a[i][j].setFillColor(Color::Yellow);
		break;
	case Red:
		a[i][j].setFillColor(Color::Red);
		break;
	case Green:
		a[i][j].setFillColor(Color::Green);
		break;
	case Cyan:
		a[i][j].setFillColor(Color::Cyan);
		break;
	case Blue:
		a[i][j].setFillColor(Color::Blue);
		break;
	case Magenta:
		a[i][j].setFillColor(Color::Magenta);
		break;
	case White:
		a[i][j].setFillColor(Color::White);
		break;
	case Black:
		a[i][j].setFillColor(Color::Black);
		break;

	}
}

//floods the board using recursion
void flood(RectangleShape board[][width], int width, int length, int i, int j, Color newColor, Color oldColor) {

	if (i > length || i < 0 || j > width || j < 0 || oldColor == newColor)
		return;
	else if (board[i][j].getFillColor() == oldColor)
	{
		board[i][j].setFillColor(newColor);
		flood(board, width,length, i, j + 1, newColor, oldColor);
		flood(board, width,length, i, j - 1, newColor, oldColor);
		flood(board, width,length, i + 1, j, newColor, oldColor);
		flood(board, width,length, i - 1, j, newColor, oldColor);
	}
}

// refills the array with random color values to restart the game and sets cnt to 0
void restartGame(RenderWindow & window, RectangleShape floodboard[][width], int length, int & cnt) {

	for (int i = 0;i < length;i++) 
		for (int j = 0;j < width;j++) {
			floodboard[i][j] = RectangleShape(Vector2f(tile_size, tile_size));
			fillSquare(floodboard, i, j, rand() % 8);
		}

	cnt = 0;
}

//play game using keyboard and increments count after every valid move
void handleKey(RenderWindow & window,RectangleShape floodboard[][width]) {
	
	if (Keyboard::isKeyPressed(Keyboard::R) && Color::Red != floodboard[0][0].getFillColor()) {
		flood(floodboard, width, length, 0, 0, Color::Red, floodboard[0][0].getFillColor());
		cnt++;
	}

	else if (Keyboard::isKeyPressed(Keyboard::Y) && Color::Yellow != floodboard[0][0].getFillColor()) {
		flood(floodboard, width, length, 0, 0, Color::Yellow, floodboard[0][0].getFillColor());
		cnt++;
	}

	else if (Keyboard::isKeyPressed(Keyboard::C) && Color::Cyan != floodboard[0][0].getFillColor()) {
		flood(floodboard, width, length, 0, 0, Color::Cyan, floodboard[0][0].getFillColor());
		cnt++;
	}

	else if (Keyboard::isKeyPressed(Keyboard::B) && Color::Blue != floodboard[0][0].getFillColor()) {
		flood(floodboard, width, length, 0, 0, Color::Blue, floodboard[0][0].getFillColor());
		cnt++;
	}

	else if (Keyboard::isKeyPressed(Keyboard::G) && Color::Green != floodboard[0][0].getFillColor()) {
		flood(floodboard, width, length, 0, 0, Color::Green, floodboard[0][0].getFillColor());
		cnt++;
	}

	else if (Keyboard::isKeyPressed(Keyboard::W) && Color::White != floodboard[0][0].getFillColor()) {
		flood(floodboard, width, length, 0, 0, Color::White, floodboard[0][0].getFillColor());
		cnt++;
	}

	else if (Keyboard::isKeyPressed(Keyboard::L) && Color::Black != floodboard[0][0].getFillColor()) {
		flood(floodboard, width, length, 0, 0, Color::Black, floodboard[0][0].getFillColor());
		cnt++;
	}

	else if (Keyboard::isKeyPressed(Keyboard::M) && Color::Magenta != floodboard[0][0].getFillColor()) {
		flood(floodboard, width, length, 0, 0, Color::Magenta, floodboard[0][0].getFillColor());
		cnt++;
	}

	else if (Keyboard::isKeyPressed(Keyboard::Space))
		restartGame(window, floodboard,length,cnt);
	
		else return;
}

//play game using mouse
void handleMouse(RenderWindow & window, Event event, RectangleShape floodboard[][width]) {

	if (event.mouseButton.button == Mouse::Left) {

		float x = Mouse::getPosition(window).x;
		float y = Mouse::getPosition(window).y;

		for (int i = 0;i < length;i++)
			for (int j = 0;j < width;j++)
				if (floodboard[i][j].getGlobalBounds().contains(x, y) && floodboard[i][j].getFillColor() != floodboard[0][0].getFillColor()) {
					flood(floodboard, width,length, 0, 0, floodboard[i][j].getFillColor(), floodboard[0][0].getFillColor());
					cnt++;
				}
	}
	else return;
	
}

//handles events in window
void handleEvent(RenderWindow & window, Event event, RectangleShape floodboard[][width]) {

	while (window.pollEvent(event))
	{
		switch (event.type){

			case Event::Closed:
				window.close();
				break;

			case Event::KeyPressed:
				handleKey(window, floodboard);
					break;

			case Event::MouseButtonPressed:
				handleMouse(window, event, floodboard);
				break;

			default:
				break;

		}
	}
}

void displayText(RenderWindow & window,Font font,Text text,int posx, int posy, std::string s, int charsize) {

	text;
	text.setFont(font); 
	text.setCharacterSize(charsize);
	text.setString(s);
	text.setFillColor(Color::White);
	text.setPosition(posx,posy);
	window.draw(text);

}


bool isFlooded(RectangleShape floodboard[][width], int length) {
	for (int i = 0;i < length;i++)
		for (int j = 0;j < width;j++)
			if (floodboard[i][j].getFillColor() != floodboard[0][0].getFillColor())
				return false;
	return true;
}

//simulates main game window
void GameWindow(RenderWindow & window, RectangleShape floodboard[][width], Font font) {


	for (int i = 0;i < length;i++) {
		for (int j = 0;j < width;j++) {
			floodboard[i][j].setPosition(tile_size * j + 40, tile_size * i + 40);
			window.draw(floodboard[i][j]);
		}
	}

	Text counter, lose, win;

	std::string s = std::to_string(cnt) + "/" + std::to_string(max_turns);
	displayText(window, font, counter, 1250, 60, s, 100);

	std::string loses = "Oh, Oh, You Lost :( \n Continue playing or \n Press on the spacebar \n to play again!";

	std::string wins = "Yay! You won! :D \n Press on the spacebar \n to play again!";


	if (cnt > max_turns)
		displayText(window, font, lose, 1050, 170, loses, 40);

	else if (cnt <= max_turns && isFlooded(floodboard, length))
		displayText(window, font, win, 1050, 170, wins, 40);
}

//displays text on help_window
void helpWindow(RenderWindow& help_window, Font font) {

			Text help;

			std::string instructions = "Play using your keyboard or your mouse \n Keyboard Instructions: \n Y: Yellow \n R: Red \n B: Blue \n C: Cyan \n G: Green \n M: Magenta \n W: White \n L: Black \n Spacebar: Restart";
			displayText(help_window, font, help, 5, 5, instructions, 42);
}

		








int main()

{
	RectangleShape floodboard[length][width];

	RenderWindow window(sf::VideoMode(1500, 1000), "Flood It!!");
	RenderWindow help_window(sf::VideoMode(700, 500), "Help and Instructions");
	srand(unsigned(time(NULL)));

	restartGame(window, floodboard, length, cnt);

		Font font;
		if (!font.loadFromFile("C:\\Users\\Faraah\\Documents\\Visual Studio 2015\\Projects\\A6_Farah\\A6_Farah\\example_font.ttf"))
			std::cout << "error loading font";

		
		

		while (window.isOpen()|| help_window.isOpen())

		{		Event event;
		if (window.isOpen()) {
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();

			}

			window.clear();
			GameWindow(window, floodboard, font);
			window.display();
			handleEvent(window, event, floodboard);
		}
			
		if (help_window.isOpen()) {

			while (help_window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					help_window.close();
			}

			help_window.clear();
			helpWindow(help_window, font);
			help_window.display();
		}
			
			
		}
	

	system("pause");
	return 0;

}