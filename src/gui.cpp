#include "gui.h"

GUI::GUI()
{
	// std::cout << "RIGHT CROSS" << std::endl;
	
	loadFile(dictionary);

	RESTART();

} // end of default constructor

GUI::~GUI()
{
	
} // end of destructor



//// BEHAVIOUR(S) ////

bool GUI::isRunning(sf::RenderWindow& window)
{
	return window.isOpen();
} // end of isRunning function


void GUI::Update(sf::RenderWindow& window)
{
	sf::Event event;
	while(window.pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
			window.close();
		else if(event.type == sf::Event::MouseButtonPressed)
		{
			// Record the click position
			sf::Vector2i position = mouse.getPosition(window);
			
			if(!(win || lose))
			{
				Click_Alphabet(event, position);
				Click_Enter(event, position);
			}

			Click_Restart(event, position);
		}
	}
} // end of Update function

void GUI::loadFile(Trie& root)
{
	std::string result = "";
	
	std::ifstream file("../dataset/words.txt");
	
	while(file>>result)
	{
		root.insert(result);
	}

	file.close();

} // end of loadFile function

std::string GUI::getRandomWord(int length)
{
	std::string result = "";

	std::ifstream file("../dataset/words.txt");

	mt19937 mt(time(0));
	uniform_int_distribution<int> dist(1, 370105);
	int wordNum = dist(mt);

	for(int i = 0; i < wordNum; i++)
	{
		file >> result;
	}

	while((int)result.size() != length)
	{
		if(!(file>>result))
		{
			file.clear();
			file.seekg(0);
		}
	}

	file.close();
	
	return result;
} // end of getRandomWord function

/// CLICK ROUTINE(S) ///

void GUI::Click_Alphabet(sf::Event& ev, sf::Vector2i& pos)
{
	if(ev.mouseButton.button == sf::Mouse::Left)
	{
		// Detect Letter being clicked
		for(int i = 0; i < 26; i++)
		{
			if(_alphabet[i].getGlobalBounds().contains(sf::Vector2f(pos.x, pos.y)))
			{
				// std::cout << static_cast<char>(i+97) << " was clicked!" << std::endl;

				if(attempt.size() < 5)
					attempt += static_cast<char>(i+97);

				// std::cout << "Attempt: " << attempt << std::endl;

				// Find the current clicked character
				_alphabet[i].setTextureRect(sf::IntRect(_usedAlphabet[i]*A_WIDTH, i*A_HEIGHT, A_WIDTH, A_HEIGHT));
				// Game Logic
				Attempt_Logic(i, ev, pos);

			}
		}

		// Detect BACKSPACE being clicked
		if(_alphabet[26].getGlobalBounds().contains(sf::Vector2f(pos.x, pos.y)))
		{
			// std::cout << "BACKSPACE was clicked!" << std::endl;
			// std::cout << "The row and col are: " << rowPos << " " << colPos << std::endl;

			if(colPos != 0)
				colPos--;

			if(colPos != 5)
				_attemptRows[rowPos][colPos].setTextureRect(sf::IntRect(0, 0, B_WIDTH, B_HEIGHT));

			if(attempt.size() != 0)
				attempt.pop_back();

			// std::cout << "Attempt: " << attempt << std::endl;
		}
	}
} // end of Click_Alphabet function

void GUI::Click_Enter(sf::Event& ev, sf::Vector2i& pos)
{
	if(ev.mouseButton.button == sf::Mouse::Left && _enter.getGlobalBounds().contains(sf::Vector2f(pos.x, pos.y)))
	{
		// std::cout << "ENTER was clicked!" << std::endl;

		if(colPos == 5)
		{
			// Game Logic
			
			Gameplay();

		}

		// Display too short
		else
		{
			// std::cout << "Word is too short" << std::endl;
			_status.setTextureRect(sf::IntRect(0, S_HEIGHT, S_WIDTH, S_HEIGHT));
		}

		// Display Lose State
		if(!win && rowPos == 6)
		{
			// std::cout << "Game Over: You Lose!" << std::endl;
			_status.setTextureRect(sf::IntRect(0, 3*S_HEIGHT,S_WIDTH, S_HEIGHT));
			lose = true;
		}
	}
} // end of Click_Enter function

void GUI::Click_Restart(sf::Event& ev, sf::Vector2i& pos)
{
	if(ev.mouseButton.button == sf::Mouse::Left && _restart.getGlobalBounds().contains(sf::Vector2f(pos.x, pos.y)))
	{
		// std::cout << "RESTART was clicked!" << std::endl;
		RESTART();
	}
} // end of Click_Restart function


/// GAME LOGIC ///

void GUI::RESTART()
{
	Clear();

	win = false;
	lose = false;
	
	// Init Target Word

	// target = getRandomWord(5);
	target = "gator";
	attempt = "";

	std::cout << "Random Word: " << target << std::endl;
	
	// Init Backdrop
	_backdrop = sf::Sprite();
	_backdrop.setTexture(grabber.GetTexture("Backdrop"));

	// Init Alphabet
	for(int i = 0, j = 0; i < 27; i++)
	{
		_alphabet.push_back(sf::Sprite());
		_alphabet[i].setTexture(grabber.GetTexture("Input_Tiles"));
		_usedAlphabet.push_back(0);

		// Columns per Row
		if(i!= 0 && i%A_COL_NUM == 0) j++;

		if((j%2) == 0)
			_alphabet[i].setPosition(A_OFFSET_X+(i%A_COL_NUM)*(A_WIDTH+A_V_SPACE), A_OFFSET_Y+j*(A_HEIGHT+A_H_SPACE));
		else
			_alphabet[i].setPosition(A_OFFSET_X+(i%A_COL_NUM)*(A_WIDTH+A_V_SPACE)-17, A_OFFSET_Y+j*(A_HEIGHT+A_H_SPACE));

		_alphabet[i].setTextureRect(sf::IntRect(_usedAlphabet[i]*A_WIDTH, i*A_HEIGHT, A_WIDTH, A_HEIGHT));
	}

	// Init ENTER Button
	_enter = sf::Sprite();
	_enter.setTexture(grabber.GetTexture("Enter_Button"));

	// Init Attempt
	for(int row = 0; row < 6; row++)
	{
		for(int col = 0; col < 5; col++)
		{
			_attempts.push_back(sf::Sprite());
			_attempts[col].setTexture(grabber.GetTexture("Attempt_Tiles"));
			_attempts[col].setPosition(B_OFFSET_X+col*(B_WIDTH+B_V_SPACE), B_OFFSET_Y+row*(B_HEIGHT+B_H_SPACE));
			_attempts[col].setTextureRect(sf::IntRect(0, 0, B_WIDTH, B_HEIGHT));
		}

		_attemptRows.push_back(_attempts);
	}


	// Init Game Status
	_status = sf::Sprite();
	_status.setTexture(grabber.GetTexture("Game_States"));
	_status.setPosition(290, 511);
	_status.setTextureRect(sf::IntRect(0, 0, 343, 91));

	// Init RESTART Button
	_restart = sf::Sprite();
	_restart.setTexture(grabber.GetTexture("Game_States"));

	rowPos = 0;
	colPos = 0;

} // end of RESTART function

void GUI::Gameplay()
{
	if(!dictionary.search(attempt))
	{
		// std::cout << "Not a Word!" << std::endl;
		_status.setTextureRect(sf::IntRect(0, 2*S_HEIGHT, S_WIDTH, S_HEIGHT));
	}
	else
	{
		if(target.compare(attempt) != 0)
		{
			// std::cout << "Wrong Word" << std::endl;

			for(int i = 0; i < (int)attempt.size(); i++)
			{
				std::size_t found = target.find(attempt[i]);

				// Valid Letter
				if(found != std::string::npos)
				{
					// Misplaced Letter
					if((int)found != i)
					{
						_usedAlphabet[attempt.at(i)-97] = MISPLACED;
					}
					// Correct Letter
					else
					{
						_usedAlphabet[attempt.at(i)-97] = CORRECT;
					}
				}
				// Invalid Letter
				else
				{
					_usedAlphabet[attempt.at(i)-97] = WRONG;
				}

				// Reset Status
				_status.setTextureRect(sf::IntRect(0, 0, S_WIDTH, S_HEIGHT));
				// Change Alphabet Color
				_alphabet[attempt.at(i)-97].setTextureRect(sf::IntRect(_usedAlphabet[attempt.at(i)-97]*A_WIDTH, (attempt.at(i)-97)*A_HEIGHT, A_WIDTH, A_HEIGHT));
				// Change Attempt Color
				_attemptRows[rowPos][i].setTextureRect(sf::IntRect((_usedAlphabet[attempt.at(i)-97])*B_WIDTH, (attempt.at(i)-96)*B_HEIGHT, B_WIDTH, B_HEIGHT));
			}
		}
		else
		{
			// std::cout << "Correct Word" << std::endl;
			win = true;
			
			
			_status.setTextureRect(sf::IntRect(0, 4*S_HEIGHT, S_WIDTH, S_HEIGHT));

			// Color for each tile
			for(int i = 0; i < (int)attempt.size(); i++)
			{
				_usedAlphabet[attempt.at(i)-97] = CORRECT;
				// Change Alphabet Color
				_alphabet[attempt.at(i)-97].setTextureRect(sf::IntRect(_usedAlphabet[attempt.at(i)-97]*A_WIDTH, (attempt.at(i)-97)*A_HEIGHT, A_WIDTH, A_HEIGHT));
				// Change Attempt Color
				_attemptRows[rowPos][i].setTextureRect(sf::IntRect((_usedAlphabet[attempt.at(i)-97])*B_WIDTH, (attempt.at(i)-96)*B_HEIGHT, B_WIDTH, B_HEIGHT));
			}
		}

		attempt = "";
		colPos = 0;
		rowPos++;
	}

} // end of Gameplay function

void GUI::Attempt_Logic(int i, sf::Event& ev, sf::Vector2i& pos)
{
	// std::cout << "The row and col are: " << rowPos << " " << colPos << std::endl;
		
	if(rowPos*colPos != 25)
	{
		if(colPos != 5)
		{
			// Alter Current Attempt

			_attemptRows[rowPos][colPos].setTextureRect(sf::IntRect(0, (i+1)*B_HEIGHT, B_WIDTH, B_HEIGHT));

		}
	}

	// Toggle Character

	if(colPos < 5)
	{
		colPos++;
	}
	else
	{
		if(rowPos < 5)
		{
			Click_Enter(ev, pos);
		}
		else
		{
			// std::cout << "The Game Should be over!" << std::endl;
		}
	}

} // end of Attempt_Logic function

/// RENDER ROUTINE(S) ///


void GUI::Render(sf::RenderWindow& window)
{
	/// CLEAR DISPLAY ///
	window.clear(sf::Color(255,255,255));

	/// RENDER BACKDROP ///
	Render_Backdrop(window);

	/// RENDER CHARACTER SECTION ///
	Render_Alphabet(window);
	Render_Enter(window);
	
	/// RENDER CHARACTER SECTION ///
	Render_Attempts(window);

	/// RENDER GAME STATUS SECTION ///
	Render_Status(window);
	Render_Restart(window);
	
	/// DISPLAY OBJECTS ///
	window.display();

} // end of Render function

void GUI::Render_Backdrop(sf::RenderWindow& window)
{
	window.draw(_backdrop);
} // end of Render_Backdrop function

void GUI::Render_Alphabet(sf::RenderWindow& window)
{
	sf::Vector2i position = mouse.getPosition(window);

	for(int i = 0; i < 27; i++)
	{
		if(_usedAlphabet[i] == DEFAULT && (_alphabet[i].getGlobalBounds().contains(sf::Vector2f(position.x, position.y))))
			_alphabet[i].setTextureRect(sf::IntRect(A_WIDTH, i*A_HEIGHT, A_WIDTH, A_HEIGHT));
		else if(_usedAlphabet[i] == DEFAULT)
			_alphabet[i].setTextureRect(sf::IntRect(0, i*A_HEIGHT, A_WIDTH, A_HEIGHT));
			
		window.draw(_alphabet[i]);
	}

} // end of Render_Alphabet function

void GUI::Render_Enter(sf::RenderWindow& window)
{
	const int OFFSET_X = 84-17, OFFSET_Y = 613;
	const int HEIGHT = 74;

	sf::Vector2i position = mouse.getPosition(window);

	
	_enter.setPosition(OFFSET_X, OFFSET_Y);

	// Mouse Hover over ENTER
	
	if(!_enter.getGlobalBounds().contains(sf::Vector2f(position.x, position.y)))
		_enter.setTextureRect(sf::IntRect(0, 0, 178, 74));
	else
		_enter.setTextureRect(sf::IntRect(0, HEIGHT, 178, 74));
	window.draw(_enter);
} // end of Render_Enter function

void GUI::Render_Attempts(sf::RenderWindow& window)
{

	// Attempt Section

	for(int row = 0; row < 6; row++)
	{
		for(int col = 0; col < 5; col++)
		{
			window.draw(_attemptRows[row][col]);
		}
	}
} // end of Render_Attempts function

void GUI::Render_Status(sf::RenderWindow& window)
{
	window.draw(_status);
} // end of Render_Status function

void GUI::Render_Restart(sf::RenderWindow& window)
{
	const int OFFSET_X = 290, OFFSET_Y = 608;
	const int WIDTH = 343, HEIGHT = 87;
	sf::Vector2i position = mouse.getPosition(window);

	_restart.setPosition(OFFSET_X, OFFSET_Y);

	// Mouse Hover over RESTART
	if(!_restart.getGlobalBounds().contains(sf::Vector2f(position.x, position.y)))
		_restart.setTextureRect(sf::IntRect(0, 5*(HEIGHT+4), WIDTH, HEIGHT));
	else
		_restart.setTextureRect(sf::IntRect(0, 5*(HEIGHT+4)+HEIGHT, WIDTH, HEIGHT));

	window.draw(_restart);

} // end of Render_Restart function



void GUI::Clear()
{
	grabber.Clear();
	_alphabet.clear();
	_attempts.clear();
	_usedAlphabet.clear();
	_attemptRows.clear();
} // end of Clear function
