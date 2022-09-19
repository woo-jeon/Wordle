#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <fstream>
#include <random>
#include <ctime>
#include <algorithm>
#include <string>
#include "trie.h"
#pragma once

class GUI
{
	struct TextureManager
	{
		std::unordered_map<std::string, sf::Texture> _textures;

		void LoadTexture(std::string fileName)
		{
			sf::Texture temp;
			std::string path = "../assets/";
			path += fileName + ".png";

			if(!temp.loadFromFile(path))
			{
				std::cerr << "Failed to load " << fileName << std::endl;
			}
			else
			{
				_textures[fileName].loadFromFile(path);
			}
		} // end of LoadTexture function

		sf::Texture& GetTexture(std::string textureName)
		{
			if(_textures.find(textureName) == _textures.end())
				LoadTexture(textureName);

			return _textures[textureName];
		} // end of GetTexture function

		void Clear()
		{
			_textures.clear();
		} // end of Clear function
	}; // end of TextureManager struct
	

	// Dimensions //

	const int A_OFFSET_X = 84, A_OFFSET_Y = 73;
	const int A_WIDTH = 57, A_HEIGHT = 53;
	const int A_V_SPACE = 3, A_H_SPACE = 7;
	const int A_COL_NUM = 3;

	const int B_OFFSET_X = 287, B_OFFSET_Y = 63;
	const int B_WIDTH = 66, B_HEIGHT = 71;
	const int B_V_SPACE = 5, B_H_SPACE = 3;
	const int B_COL_NUM = 5;

	const int S_OFFSET_X = 290, S_OFFSET_Y = 511;
	const int S_WIDTH = 343, S_HEIGHT = 91;
	const int S_H_SPACE = 7;

	// Local Declaration(s)

	sf::Mouse mouse;

	TextureManager grabber;
	sf::Sprite _backdrop;
	std::vector<sf::Sprite> _alphabet;
	sf::Sprite _enter;
	std::vector<sf::Sprite> _attempts;
	sf::Sprite _status;
	sf::Sprite _restart;

	std::vector<int> _usedAlphabet;
	std::vector<std::vector<sf::Sprite>> _attemptRows;
	
	int rowPos = 0, colPos = 0;

	bool win = false, lose = false;

	Trie dictionary;
       	std::string target = "";
	std::string attempt = "";

	enum CHAR_COLOR { DEFAULT, HOVER, WRONG, MISPLACED, CORRECT };
	

	public:

	//// CONSTRUCTOR(S) AND DESTRUCTOR(S)
	
	GUI();

	~GUI();



	//// BEHAVIOUR(S) ////
	
	bool isRunning(sf::RenderWindow&);

	void Update(sf::RenderWindow&);

	void loadFile(Trie&);

	std::string getRandomWord(int);


	/// CLICK ROUTINE(S) ///
	
	void Click_Alphabet(sf::Event&, sf::Vector2i&);

	void Click_Enter(sf::Event&, sf::Vector2i&);

	void Click_Restart(sf::Event&, sf::Vector2i&);


	/// GAME LOGIC ///

	void RESTART();

	void Gameplay();

	void Attempt_Logic(int, sf::Event&, sf::Vector2i&);


	/// RENDER ROUTINE(S) ///

	void Render(sf::RenderWindow&);

	void Render_Backdrop(sf::RenderWindow&);

	void Render_Alphabet(sf::RenderWindow&);

	void Render_Attempts(sf::RenderWindow&);

	void Render_Enter(sf::RenderWindow&);

	void Render_Status(sf::RenderWindow&);

	void Render_Restart(sf::RenderWindow&);

	void Clear();

}; // end of GUI Class
