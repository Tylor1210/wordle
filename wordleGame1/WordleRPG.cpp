#include "WordleGame.h"
#include <limits>


/**
 * Display the main menu
 */
void displayMenu() {
    std::cout << "\n==================================\n";
    std::cout << "     WORDLE GAME MAIN MENU\n";
    std::cout << "==================================\n";
    std::cout << "1. See the Rules\n";
    std::cout << "2. Play the Game\n";
    std::cout << "3. See Performance Report\n";
    std::cout << "4. Quit\n";
    std::cout << "Enter your choice (1-4): ";
}

/**
 * Run the menu loop
 */
void runMenu() {
    WordleGame game;  // Create the game object
    int choice = 0;

    // Loop until user quits
    while (choice != 4) {
        displayMenu();

        // Try to read user's choice
        try {
            if (!(std::cin >> choice)) {
                // Input failed (user typed letters instead of numbers)
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Invalid input. Please enter a number.");
            }

            // Handle the menu choice
            switch (choice) {
            case 1:
                game.displayRules();
                break;
            case 2:
                game.playGame();
                break;
            case 3:
                game.viewPerformanceReport();
                break;
            case 4:
                std::cout << "\nThank you for playing Wordle! Goodbye.\n";
                break;
            default:
                std::cout << "\nInvalid choice. Please select 1, 2, 3, or 4.\n";
                break;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "\nError: " << e.what() << "\n";
        }
    }
}

/**
 * Main function - program starts here!
 */
int main() {
    runMenu();
    return 0;
}