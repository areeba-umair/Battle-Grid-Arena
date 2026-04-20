#include"Declerations.h"
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <fstream>
#include <vector>
#include "byeBye.cpp"

using namespace std;
using std::cout;
using std::endl;
using std::cin;

// Game class implementation
Game::Game() : board(new Board()), player(nullptr), enemyCount(0), level(1) {
    srand(static_cast<unsigned int>(time(nullptr))); // Initialize random seed
    
    shop = new Shop();
    // Initialize enemies array to nullptr
    for (int i = 0; i < 10; i++) {
        enemies[i] = nullptr;
    }
}

Game::~Game() {
    delete board;
    
    // Clean up any dynamic memory allocated during the game
    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i]) {
            delete enemies[i];
        }
    }
    
    if (player) {
        delete player;
    }
}

void Game::showMenu(){
    system("CLS"); // Clear the screen for a fresh start
    cout<< YELLOW << "============== WELCOME TO THE LEGENDS OF VALOUR ==========\n\n" << endl;

    cout << BLUE << "========================= MENU =======================" << WHITE <<endl;
    cout << "|                   1. Start New Game                |" << endl;
    cout << "|                   2. Load Game                     |" << endl;
    cout << "|                   3. Game Rules                    |" << endl;
    cout << "|                   4. Exit                          |" << endl;
    cout << BLUE << "======================================================\n" << endl;
    
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            gameInitialize();
            break;
        case 2:
            loadGame();
            break;
        case 3:
            gameRules();
        case 4:
            cout << "Exiting the game. Goodbye!" << endl;
            exit(0);
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            showMenu();
            break;
    }
}

void Game::gameStart(){
    showMenu();
}

void Game::setUserName(string name) {
    userName = name;
}

string Game::getUserName() const {
    return userName;
}

void Game::gameInitialize() {
    system("CLS"); // Clear the screen for a fresh start

    cout << "Enter your name: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, userName);
    setUserName(userName);
    system("CLS"); // Clear the screen for a fresh start
    cout << "Welcome, " << userName << "!" << endl;
    Sleep(1000); // Pause for a moment to build anticipation
    cout << "Prepare yourself !" << endl;
    Sleep(1000); // Pause for a moment to build anticipation
    cout << "Be carefull... The war is going to happen" << endl;
    Sleep(2000); // Pause for a moment to build anticipation
    system("CLS"); // Clear the screen for a fresh start

    cout << "Loading." << endl;
    Sleep(500); // Pause for a moment to build anticipation
    system("CLS"); // Clear the screen for a fresh start
    cout << "Loading.." << endl;
    Sleep(500); // Pause for a moment to build anticipation
    system("CLS"); // Clear the screen for a fresh start
    cout << "Loading..." << endl;
    Sleep(500); // Pause for a moment to build anticipation
    system("CLS"); // Clear the screen for a fresh start
    cout << "Loading...." << endl;
    Sleep(500); // Pause for a moment to build anticipation
    system("CLS"); // Clear the screen for a fresh start
    cout << "Loading....." << endl;


    // Character selection
    int characterChoice = selectCharacter();
    
    // Initialize player based on choice
    initializePlayer(characterChoice);
    
    // Place player on the board
    board->placePlayer(player, 0, 0);
    
    // Create and place enemies
    createEnemies();
    
    // Create obstacles
    // createObstacles();
    
    // Main game loop
    gameLoop();
}

int Game::selectCharacter() {
    int choice = 0;
    
    cout <<RED<< "Select your character:" << endl;
    cout << "1. Warrior (Strong attack and defense)" << endl;
    cout << "2. Magician (Can teleport across cells)" << endl;
    cout << "3. Thief (Can steal enemy inventory)" << endl;
    
    while (true) {
        cout << "Enter your choice (1-3): ";
        cin >> choice;
        
        if (cin.fail() || choice < 1 || choice > 3) {
            cin.clear();
            cin.ignore();
            cout << "Invalid choice. Please try again." << endl;
        } else {
            break;
        }
    }
    
    return choice;
}

void Game::initializePlayer(int characterChoice) {
    cout << RESET;
    switch (characterChoice) {
        case 1:
            player = new Warrior();
            cout << "You have chosen the Warrior!" << endl;
            break;
        case 2:
            player = new Magician();
            cout << "You have chosen the Magician!" << endl;
            break;
        case 3:
            // For now, use Warrior as placeholder since Thief is not implemented yet
            player = new Theif(); // Should be Thief in a complete implementation
            cout << "You have chosen the Thief!" << endl;
            break;
    }
    
    // Add initial items to inventory
    if (characterChoice == 1) { // Warrior
        Knife* knife = new Knife();
        player->addInventory(*knife);
    } else if (characterChoice == 2) { // Magician
        WaterBall* waterball = new WaterBall();
        player->addInventory(*waterball);
    }
    else if (characterChoice == 3) { // Thief
        Pistol* pistol = new Pistol();
        player->addInventory(*pistol);
    }
    else {
        cout << "Invalid character choice!" << endl;
        delete player; // Clean up in case of invalid choice
        player = nullptr;
    }
}

void Game::createEnemies() {
    // Create a few enemies and place them on the board
    string enemyNames[] = {"Goblin", "Orc", "Skeleton", "Troll", "Dragon"};
    int enemyHealth[] = {30, 50, 40, 70, 100};
    
    //
    if(level == 1)
        enemyCount = rand() % 3 + 3;
    else if(level == 2)
        enemyCount = rand() % 4 + 4;
    else if(level == 3)
        enemyCount = rand() % 5 + 5;
    else
    enemyCount = rand() % 3 + 3;
    
    for (int i = 0; i < enemyCount; i++) {
        int enemyType = rand() % 5; // 0
        int x, y;
        
        // Find a valid position for the enemy
        do {
            x = rand() % board->getBoardSize();
            y = rand() % board->getBoardSize();
        } while (!board->getCell(x, y)->isEmpty() || (x == 0 && y == 0));
        
        // Create and place the enemy
        enemies[i] = new Enemy(enemyNames[enemyType], enemyHealth[enemyType], x, y);
        
        // Give the enemy an item
        Item* enemyItem = nullptr;
        int itemType = rand() % 3;
        switch (itemType) {
            case 0: enemyItem = new Knife(); break;
            case 1: enemyItem = new Sword(); break;
            case 2: enemyItem = new Pistol(); break;
        }
        
        enemies[i]->setInventoryItem(enemyItem);
        board->placeEnemy(enemies[i], x, y);
    }
    
    cout << "Placed " << enemyCount << " enemies on the board." << endl;
}

// void Game::createObstacles() {
//     // Create some obstacles
//     int numObstacles = rand() % 5 + 5;
    
//     for (int i = 0; i < numObstacles; i++) {
//         int x, y;
        
//         // Find a valid position for the obstacle
//         do {
//             x = rand() % 7;
//             y = rand() % 7;
//         } while (!board->getCell(x, y)->isEmpty() || (x == 0 && y == 0));
        
//         board->createObstacle(x, y);
//     }
    
//     cout << "Created " << numObstacles << " obstacles on the board." << endl;
// }

void Game::gameLoop() {
    bool gameRunning = true;
    
    cout << CYAN << "\n============ GAME STARTED ==========\n" << endl;
    
    while (gameRunning) {
        system("CLS"); // Clear the screen to refresh after every move
        // Display the current state
        player->showStats();
        board->displayBoard();

        cout << RESET << "Press any key to move the character or 's' to visit the shop..." << endl;
        char input = '\0';
        while (true) {
            if (_kbhit()) {
                input = _getch();
                break;
            }
            Sleep(10); // slight delay 
        }

        if (input == 's' || input == 'S') {
            system("CLS"); // Clear the screen before entering the shop
            shop->visitShop(player); // Allow the player to visit the shop
            Sleep(5000); // Pause to let the player read the message
            // Skip the rest of the loop to refresh the game state after shopping
        }
        else if (input == 'h' || input == 'H') {
            // Check if the player has a health potion in their inventory
            Item* healthPotion = player->getInventoryItemByName("Health Potion");
            if (healthPotion) {
            // Use the health potion to increase player's health
            player->setHealth(player->getHealth() + healthPotion->getHealthIncrement());
            cout << "You used a Health Potion! Your health is now " << player->getHealth() << "." << endl;
            
            // Remove the health potion from the inventory
            player->removeInventoryItem("Health Potion");
            } else {
            cout << "You don't have a Health Potion in your inventory!" << endl;
            }
            // Pause to let the player read the message
            continue;
        }
        else if (input == 'q' || input == 'Q') {
            saveGame();
            cout << "Game saved! Exiting..." << endl;
            gameRunning = false;
            continue;
        }
        else if(input == 'x' || input == 'X'){
            cheatCodes();
            continue;
        }
      
        for (int i = 0; i < enemyCount; i++) {
            if (enemies[i] && board->enemyEncountered(player, enemies[i])) {
                cout << "You encountered " << enemies[i]->getName() << "!" << endl;
                handleCombat(enemies[i]);
            } 
        }
        
        // Get player move
        handlePlayerMove();
        // system("CLS"); // Clear the screen to refresh after every move
        // board->displayBoard();

        // Check win condition (player reaches the bottom-right corner of the board)
        if (player->getPosition().x >= board->getBoardSize() - 1 && player->getPosition().y >= board->getBoardSize() - 1) {

            cout << "\n===== LEVEL COMPLETED! ADVANCING TO NEXT LEVEL! =====\n" << endl;
            level++;
            player->setLevel(level);
           // delete board; // Delete the current board
            
            // Increase board size and create a new board
            int newBoardSize = board->getBoardSize() + 2; // Increment board size
            BOARD_SIZE = newBoardSize;
            board = new Board(newBoardSize);
            
            // Place player at the starting position
            player->setPosition(0, 0);
            board->placePlayer(player, 0, 0);
            
            // Create more enemies for the new level
            createEnemies();
            
            // // Create new obstacles
            // createObstacles();
            
            cout << "Welcome to Level " << level << "!" << endl;
            Sleep(2000); // Pause to let the player read the message
        }

        if(level==3){
            //Enemies will move randomly at each iteration on level 3... it is just to increase the difficulty
            moveEnemies();
        }
        if (level > 3) {
            byeBye();
            exit(0);
        }
        
        // Check lose condition
        if (player->getHealth() <= 0) {
            cout << "\n===== GAME OVER! YOU DIED! =====\n" << endl;
            gameRunning = false;
        }
    }
}

bool Game::handlePlayerMove() {
    // Move the player  
		board->getCell(player->getPosition().x, player->getPosition().y)->setType(CellType::EMPTY);
    if (player->move()) {
        // Update the board cell after the player moves  
        Position newPos = player->getPosition();
        board->placePlayer(player, newPos.x, newPos.y);
        return true;
    }
    return false;
}


void Game::moveEnemies() {
    // Simple AI for enemies: move randomly or towards player
    for (int i = 0; i < enemyCount; i++) {
        Enemy* enemy = enemies[i];
        if (!enemy) continue;
        
        // 50% chance to move towards player, 50% chance to move randomly
        bool moveTowardsPlayer = (rand() % 2 == 0);
        
        Position enemyPos = enemy->getPosition();
        Position playerPos = player->getPosition();
        
        int newX = enemyPos.x;
        int newY = enemyPos.y;
        
        if (moveTowardsPlayer) {
            // Move towards player
            if (enemyPos.x < playerPos.x) newX++;
            else if (enemyPos.x > playerPos.x) newX--;
            
            if (enemyPos.y < playerPos.y) newY++;
            else if (enemyPos.y > playerPos.y) newY--;
        } else {
            // Move randomly
            int direction = rand() % 4;
            switch (direction) {
                case 0: newY--; break; // Up
                case 1: newY++; break; // Down
                case 2: newX--; break; // Left
                case 3: newX++; break; // Right
            }
        }
        
        board->moveEnemy(enemy, newX, newY);
    }
}

void Game::handleCombat(Enemy* enemy) {
    cout << RED << "\n========== COMBAT STARTED ==========\n" << endl;
    cout << "You are fighting a " << enemy->getName() << " with " << enemy->getHealth() << " HP!" << endl;
    cout << "He has " << enemy->getInventoryItem()->getItemName() << " in his inventory." << endl;
    
    // Show combat options
    cout << WHITE << "Combat options:" << endl;
    cout << "1. Attack" << endl;
    cout << "2. Run away" << endl;
    
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    
    if (cin.fail() || (choice != 1 && choice != 2)) {
        cin.clear();
        cin.ignore();
        cout << "Invalid choice. Defaulting to attack." << endl;
        choice = 1;
    }
    
    if (choice == 1) {
        // Process combat
        if (player->name == "Thief") {
            cout << "Do you want to steal the inventory of the enemy? (1 for Yes, 0 for No): ";
            int stealChoice;
            cin >> stealChoice;
            if (stealChoice == 1) {
            // Cast player to Theif* and call addInventory if possible
            Theif* thiefPlayer = dynamic_cast<Theif*>(player);
            if (thiefPlayer) {
                Item* stolenItem = enemy->getInventoryItem();
                bool added = thiefPlayer->addInventory(*stolenItem); // Try to add to player inventory
                if (added) {
                player->addPoints(-20); // Deduct 20 points
                cout << "You stole the enemy's inventory but lost 20 points!" << endl;
                // Remove enemy from the board and enemy list
                Position enemyPos = enemy->getPosition();
                board->getCell(enemyPos.x, enemyPos.y)->setType(CellType::EMPTY);
                removeEnemy(enemy);
                delete enemy;
                return;
                } else {
                cout << "Failed to steal: Proceeding with normal combat." << endl;
                // Continue to normal combat below
                }
            } else {
                cout << "Steal ability not available!" << endl;
            }
            }
        }

        board->processCombat(player, enemy);
        
        // Check if enemy is defeated
        if (enemy->getHealth() <= 0) {
            // Remove enemy from the list
            removeEnemy(enemy);
            
            // Award points to player
            player->addPoints(25);
            player->setHealth(player->getHealth() + 30); // Heal player a bit
            cout << "You earned 25 points!" << endl;
            
            // Opportunity to pick up enemy item
            if (enemy->getInventoryItem()) {
                cout << "The enemy dropped a " << enemy->getInventoryItem()->getItemName() << "!" << endl;
                cout << "Do you want to pick it up? (1 for Yes, 0 for No): ";
                int pickUp;
                cin >> pickUp;
                
                if (pickUp == 1) {
                    // Add to player inventory
                    player->addInventory(*(enemy->getInventoryItem()));
                    Sleep(3000);
                    cout << "Added " << enemy->getInventoryItem()->getItemName() << " to your inventory!" << endl;
                }
            }
            
            delete enemy;
        }
    } else {
        // Run away
        cout << "You try to run away..." << endl;
        
        Position enemyPos = enemy->getPosition();
        Position playerPos = player->getPosition();

        // Calculate new position to jump over the enemy
        int newX = playerPos.x + 1;
        int newY = playerPos.y;

        // If the enemy is in the last cell of the row, adjust the y-coordinate
        if (enemyPos.x == board->getBoardSize() - 1) {
            newY = playerPos.y + 1;
        }

        // Ensure the new position is valid
        if (board->isValidPosition(newX, newY) && board->getCell(newX, newY)->isEmpty()) {
            // Remove enemy from the board
            board->getCell(enemyPos.x, enemyPos.y)->setType(CellType::EMPTY);
            removeEnemy(enemy);
            delete enemy;

            // Move player to the new position
            board->getCell(player->getPosition().x, player->getPosition().y)->setType(CellType::EMPTY);
            player->setPosition(newX, newY);
            board->placePlayer(player, newX, newY);
            cout << "You successfully ran away to (" << newX << ", " << newY << ")" << endl;
        } else {
            cout << "No valid position to jump over! Combat continues." << endl;
            board->processCombat(player, enemy);
        }
    }
}

void Game::removeEnemy(Enemy* enemy) {
    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i] == enemy) {
            enemies[i] = nullptr;
            break;
        }
    }
}
void Game::saveGame() {
    ofstream outFile("saved_game.txt");
    if (!outFile) {
        cout << "Failed to open file for saving!" << endl;
        return;
    }

    // Save basic game state
    outFile << userName << endl;
    outFile << level << endl;
    outFile << board->getBoardSize() << endl;
    outFile << player->getHealth() << " " << player->getPoints() << " " << player->getLevel() << endl;
    outFile << player->getPosition().x << " " << player->getPosition().y << endl;

    // Save player inventory (fixed 3x3 array)
    int savedCount = 0;
    // Count non-null items in the 3x3 array
    for (int i = 0; i < 3; ++i) {
        Item** inventoryRow = player->getInventory(i);
        for (int j = 0; j < 3; ++j) {
            if (inventoryRow[j] != nullptr) {
                savedCount++;
            }
        }
    }
    outFile << savedCount << endl;

    for (int i = 0; i < 3; ++i) {
        Item** inventoryRow = player->getInventory(i);
        for (int j = 0; j < 3; ++j) {
            Item* item = player->getInventory(i)[j];
            if (item) {
                outFile << i << " " << j << " " << item->getItemName() << endl;
            }
        }
    }

    // Save enemies
    outFile << enemyCount << endl;
    for (int i = 0; i < enemyCount; ++i) {
        if (enemies[i]) {
            outFile << enemies[i]->getName() << " "
                    << enemies[i]->getHealth() << " "
                    << enemies[i]->getPosition().x << " "
                    << enemies[i]->getPosition().y << " ";
            if (enemies[i]->getInventoryItem())
                outFile << enemies[i]->getInventoryItem()->getItemName();
            else
                outFile << "None";
            outFile << endl;
        } else {
            outFile << "NULL" << endl;
        }
    }

    outFile.close();
    cout << "Game saved!" << endl;
}

void Game::loadGame() {
    ifstream inFile("saved_game.txt");
    if (!inFile) {
        cout << "Failed to open file for loading!" << endl;
        return;
    }

    // Clean up previous state if any
    if (board) delete board;
    if (player) delete player;
    for (int i = 0; i < 10; ++i) {
        if (enemies[i]) {
            delete enemies[i];
            enemies[i] = nullptr;
        }
    }

    // Load basic game state
    getline(inFile, userName);
    inFile >> level;
    int boardSize;
    inFile >> boardSize;
    board = new Board(boardSize);

    int health, points, playerLevel;
    inFile >> health >> points >> playerLevel;

    int posX, posY;
    inFile >> posX >> posY;

    // For simplicity, always load as Warrior (you can extend this to save/load class type)
    player = new Warrior();
    player->setHealth(health);
    player->setPoints(points);
    player->setLevel(playerLevel);
    player->setPosition(posX, posY);
    board->placePlayer(player, posX, posY);

    // Load player inventory (fixed 3x3 array)
    int savedCount;
    inFile >> savedCount;
    for (int k = 0; k < savedCount; ++k) {
        int i, j;
        string itemName;
        inFile >> i >> j >> itemName;
        Item* item = shop->getItemByName(itemName);
        if (item) {
            player->addInventory(*item);
        }
    }

    // Load enemies
    inFile >> enemyCount;
    for (int i = 0; i < enemyCount; ++i) {
        string firstToken;
        inFile >> firstToken;
        if (firstToken == "NULL") {
            enemies[i] = nullptr;
            continue;
        }
        string enemyName = firstToken;
        int enemyHealth, enemyPosX, enemyPosY;
        inFile >> enemyHealth >> enemyPosX >> enemyPosY;
        string itemName;
        inFile >> itemName;

        enemies[i] = new Enemy(enemyName, enemyHealth, enemyPosX, enemyPosY);
        if (itemName != "None") {
            Item* item = shop->getItemByName(itemName);
            if (item) {
                enemies[i]->setInventoryItem(item);
            }
        }
        board->placeEnemy(enemies[i], enemyPosX, enemyPosY);
    }

    inFile.close();
    cout << "Game loaded!" << endl;
    // Resume game loop after loading
    gameLoop();
}

void Game::gameRules() {
    system("CLS"); // Clear the screen for a fresh start
    cout << YELLOW << "======================== GAME RULES ======================" << endl;
    cout << BLUE << "1. The game is played on a grid-based board." << endl;
    cout << "2. Players can move cell by cell. (Horizontally)" << endl;
    cout << "3. Players can encounter enemies and engage in combat." << endl;
    cout << "4.While playing the game, you can use the following commands:" << endl;
    cout << "        Press Space to move" << endl;
    cout << "        S - to enter shop" << endl;
    cout << "        T - to teleport (only for Magician)" << endl;
    cout << "        H - to use Health Potion" << endl;
    cout << "        Q - to quit the game and save the game" << endl;
    cout << "5. Players can buy items from the shop using points." << endl;
    cout << "6. Players have to go to the last cell to complete the level" << endl;
    cout << "7. With the increment of level player will unlock weapons and map difficulty will be increased" << endl;
    cout << "8. Players can save and load their game progress." << endl;
    
    cout << WHITE << "\nPress Enter to return to the menu..." << endl;
    cin.ignore();
    cin.get();
    showMenu();
}

void Game::cheatCodes(){
    system("CLS");
    cout << "Enter the cheat code: ";
    string cheatCode;
    cin >> cheatCode;
    if (cheatCode == "PAISAPAISA"){
        cout << "Cheat code activated! You have received 100 points!" << endl;
        player->addPoints(200);
    }
    else if (cheatCode == "GODMODE"){
        cout << "Cheat code activated! You are now invincible!" << endl;
        player->setHealth(9999); // Set health to a very high value
    }
    else if (cheatCode == "IDONOTWANTTOPLAY"){
        player->setPosition(board->getBoardSize() - 1, board->getBoardSize() - 1); // Move player to the last cell
        cout << "Cheat code activated! You have been teleported to the last cell!" << endl;
    }
    else{
        cout << "Kuch nahi!...Ab rehnay dein" << endl;
        Sleep(3000);
    }
}

void Game::byeBye(){
    displayGameCompleted();
}
