#pragma once
#ifndef WORDLEGAME_H
#define WORDLEGAME_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class WordleGame {
	private:
		//2d array 6 down 5 across
		char grid[6][5];
		char feedbackGrid[6][5];
		string answer;

		void initGrid();
		void loadAnswer();
		void processFeedback(const string& guess, int tryIndex);
		void writeScore(int score);
		string toUpperCase(const string& s) const;
		void printColoredLetter(char letter, char color) const;

	public:
		static int currentTry;

		//constructor
		WordleGame();

		static int getCurrentTry() {
			return currentTry;
		}
		static void setCurrentValue(int newTry) {
			currentTry = newTry;
		}

		void displayRules() const;
		void playGame();
		void displayGrid() const;
		void viewPerformanceReport() const;
		bool validateWord(const string& word) const;


};

#endif