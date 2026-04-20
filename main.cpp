 #include "Declerations.h"
#include "Game.cpp"
#include "firstscreen.cpp"
#include "Cell_Board.cpp"
#include "Player.cpp"
#include "Enemy.cpp"
#include "Item.cpp"


#include "Shop.cpp"
#include <iostream>

using namespace std;

int main() {

    displayFancyTitle();
    
    Sleep(5000); // Pause for a moment to build anticipation
    system("CLS"); // Clear the screen for a fresh start
    // Wait for user to press Enter before closing
    std::cout << WHITE << "\nPress Enter to continue..." << RESET;
    std::cin.get();
    // Create a new game instance
    Game game;
    // Initialize and start the game
    game.gameStart();
    
    return 0;
}
