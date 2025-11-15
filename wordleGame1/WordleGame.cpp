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
	return upper;
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
	//Is file open?
	if (file.is_open()) {
		while (file >> word) {
			if (word.length() == 5) {
				words.push_back(toUpperCase(word));
			}
		}
		file.close();
	}


	if (!words.empty()) {
		int index = (currentTry * 17) % words.size();
		answer = words[index];
	}
	else {
		answer = "OCEAN";
		cout << "*** File not found.. using a default word.** \n";
	}
}

//Validate
bool WordleGame::validateWord(const string& word) const {
	if (word.length() != 5) {
		cout << "Error: Must be 5 letters.\n";
		return false;
	}
	for (int i = 0; i < 0; i++) {
		//Check if valid letter 
		if ((word[i] < 'A' || word[i] > 'Z') &&
			(word[i] < 'a' || word[i] >'z')) {
			cout << "Error: Only letters allowed.";
			return false;
		}
	}
	return true;
}

void WordleGame::processFeedback(const std::string& guess, int tryIndex) {
	std::string guessUpper = toUpperCase(guess);
	std::string answerCopy = answer;

	// Store the letters
	for (int i = 0; i < 5; i++) {
		grid[tryIndex][i] = guessUpper[i];
		feedbackGrid[tryIndex][i] = 'B';
	}

	// Mark GREEN (exact matches)
	for (int i = 0; i < 5; i++) {
		if (guessUpper[i] == answerCopy[i]) {
			feedbackGrid[tryIndex][i] = 'G';
			answerCopy[i] = '-';
		}
	}

	// Mark YELLOW (wrong position)
	for (int i = 0; i < 5; i++) {
		if (feedbackGrid[tryIndex][i] != 'G') {
			for (int j = 0; j < 5; j++) {
				if (guessUpper[i] == answerCopy[j]) {
					feedbackGrid[tryIndex][i] = 'Y';
					answerCopy[j] = '-';
					break;
				}
			}
		}
	}

	// Display with colors
	std::cout << "\n";
	for (int i = 0; i < 5; i++) {
		printColoredLetter(grid[tryIndex][i], feedbackGrid[tryIndex][i]);
		std::cout << " ";
	}
	std::cout << "\n";
}
// Display the game rules
void WordleGame::displayRules() const {
	std::cout << "\n========== WORDLE RULES ==========\n";
	std::cout << "1. Guess the 5-letter word\n";
	std::cout << "2. You have 6 tries\n";
	std::cout << "3. After each guess:\n";
	std::cout << "   ";
	printColoredLetter('G', 'G');
	std::cout << " = Correct letter, correct spot\n";
	std::cout << "   ";
	printColoredLetter('Y', 'Y');
	std::cout << " = Correct letter, wrong spot\n";
	std::cout << "   ";
	printColoredLetter('B', 'B');
	std::cout << " = Letter not in word\n";
	std::cout << "4. Win = Guess in 1-6 tries\n";
	std::cout << "5. Lose = Don't guess in 6 tries\n";
	std::cout << "===================================\n";
}
// Show the current grid
void WordleGame::displayGrid() const {
	std::cout << "\n======== WORDLE GRID (Try " << currentTry << "/6) ========\n\n";
	for (int i = 0; i < 6; i++) {
		std::cout << "Try " << (i + 1) << ": ";

		if (grid[i][0] == '-') {
			std::cout << "_ _ _ _ _";
		}
		else {
			for (int j = 0; j < 5; j++) {
				printColoredLetter(grid[i][j], feedbackGrid[i][j]);
				std::cout << " ";
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n========================================\n";
}
// Save score to file
void WordleGame::writeScore(int score) {
	std::ofstream outfile("wordleStats.txt", std::ios::app);
	if (outfile.is_open()) {
		outfile << score << "\n";
		outfile.close();
		std::cout << "Score saved: " << score << "\n";
	}
	else {
		std::cout << "Warning: Could not save score.\n";
	}
}

//Performance report
void WordleGame::viewPerformanceReport() const {
	std::ifstream infile("wordleStats.txt");

	if (!infile.is_open()) {
		std::cout << "\n*** No statistics found. Play some games first! ***\n";
		return;
	}

	int score;
	int gamesPlayed = 0;
	int gamesWon = 0;
	int totalTries = 0;

	while (infile >> score) {
		gamesPlayed++;
		if (score >= 1 && score <= 6) {
			gamesWon++;
			totalTries += score;
		}
	}
	infile.close();

	int gamesLost = gamesPlayed - gamesWon;
	double winPercent = (gamesPlayed > 0) ? (gamesWon * 100.0 / gamesPlayed) : 0.0;
	double avgTries = (gamesWon > 0) ? (totalTries * 1.0 / gamesWon) : 0.0;

	std::cout << "\n========== PERFORMANCE REPORT ==========\n";
	std::cout << "Games Played: " << gamesPlayed << "\n";
	std::cout << "Games Won:    " << gamesWon << "\n";
	std::cout << "Games Lost:   " << gamesLost << "\n";
	std::cout << "Win Rate:     " << winPercent << "%\n";
	std::cout << "Avg Tries:    " << avgTries << " (when won)\n";
	std::cout << "========================================\n";
}

// Main game loop
void WordleGame::playGame() {
	initGrid();
	currentTry = 1;
	loadAnswer();

	std::cout << "\n========== NEW GAME STARTED ==========\n";

	bool won = false;
	std::string guess;

	while (currentTry <= 6 && !won) {
		displayGrid();

		std::cout << "\nEnter guess #" << currentTry << " (5 letters): ";
		std::cin >> guess;

		while (!validateWord(guess)) {
			std::cout << "Try again. Enter 5 letters: ";
			std::cin >> guess;
		}

		std::string guessUpper = toUpperCase(guess);
		processFeedback(guessUpper, currentTry - 1);

		if (guessUpper == answer) {
			won = true;
			std::cout << "\n*** YOU WON! ***\n";
			std::cout << "You guessed '" << answer << "' in " << currentTry << " tries!\n";
		}

		currentTry++;
	}

	if (!won) {
		displayGrid();
		std::cout << "\n*** GAME OVER ***\n";
		std::cout << "The word was: " << answer << "\n";
	}

	int score = won ? (currentTry - 1) : 0;
	writeScore(score);

	std::cout << "======================================\n";
}