#include "WordleGame.h"

//Initialize our first attempt
int WordleGame::currentTry = 1;

//Constructor
WordleGame::WordleGame() {
	answer = "";
	initGrid(); //Build our grid

}

// Convert the word to uppercase for comparison 
string WordleGame::toUpperCase(const std::string& s) const {
	string upper = s;

	for (int i = 0; i < upper.length(); i++) {
		//check if lowercase and if so make uppercase by doing ascii - 32
		if (upper[i] >= 'a' && upper[i] <= 'z') {
			upper[i] = upper[i] - 32;
		}
	}
}

// print colored letters 
void WordleGame::printColoredLetter(char letter, char color) const {
	//ansi color codes
	if (color == 'G') {
		cout << "\033[42m\033[30m " << letter << " \033[0m";
	}
	else if (color == 'Y') {
		cout << "\033[43m\033[30m " << letter << " \033[0m";
	}
	else {
		cout << "\033[100m\033[37m " << letter << " \033[0m";
	}
}

// fill blank grids for display
void WordleGame::initGrid() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 5; j++) {
			grid[i][j] = '-';
			feedbackGrid[i][j] = '-';
		}
	}
}

void WordleGame::loadAnswer() {
	ifstream file("fiveLetterWords.txt");
	vector<string> words;
	string word;

	if (file.is_open()) {

	}
}