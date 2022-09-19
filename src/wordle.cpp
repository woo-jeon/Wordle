#include <iostream>
#include <fstream>
#include "gui.h"

int main()
{
	//// INITIALIZATION ////

	sf::RenderWindow window(sf::VideoMode(700, 750), "Snapping Gator's Wordle", sf::Style::Titlebar | sf::Style::Close); 
	window.setFramerateLimit(60);

	GUI game = GUI();

	//// MAIN GAMEPLAY LOOP ////

	while(game.isRunning(window))
	{
		/// GAME LOGIC ///
		game.Update(window);

		/// GAME DRAW ///
		game.Render(window);
	}

	//// SHUTDOWN ////

	game.Clear();

	return 0;
} // end of main
