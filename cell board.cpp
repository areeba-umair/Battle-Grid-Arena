#include "Declerations.h"
#include<iostream>
#include<cmath>
#include<string>
#include<iomanip>
#include <conio.h>
#include<windows.h>
#include "byeBye.cpp"
using namespace std;


// ==================== CELL CLASS IMPLEMENTATIONS ====================
Cell::Cell() : type(CellType::EMPTY), player(nullptr), enemy(nullptr) {}

void Cell::setType(CellType newType) { 
    type = newType; 
}

CellType Cell::getType() const { 
    return type; 
}

void Cell::setPlayer(Player* p) { 
    player = p; 
    if (p != nullptr) {
        type = CellType::PLAYER;
    } else if (type == CellType::PLAYER) {
        type = CellType::EMPTY;
    }
}

void Cell::setEnemy(Enemy* e) { 
    enemy = e; 
    if (e != nullptr) {
        type = CellType::ENEMY;
    } else if (type == CellType::ENEMY) {
        type = CellType::EMPTY;
    }
}

Player* Cell::getPlayer() const { 
    return player; 
}

Enemy* Cell::getEnemy() const { 
    return enemy; 
}

bool Cell::isEmpty() const { 
    return type == CellType::EMPTY; 
}

void Cell::clear() { 
    type = CellType::EMPTY; 
    player = nullptr; 
    enemy = nullptr; 
}


// ==================== BOARD CLASS IMPLEMENTATIONS ====================
Board::Board(int size) : boardSize(size) {
    cells = new Cell*[boardSize];
    for (int i = 0; i < boardSize; ++i) {
        cells[i] = new Cell[boardSize];
    }
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; i < boardSize; i++){
            cells[i][j].setType(CellType::EMPTY);
        }
        
    }
    
}

Board::~Board() {
    for (int i = 0; i < boardSize; ++i) {
        delete[] cells[i];
    }
    delete[] cells;
}

int Board::getBoardSize() const {
    return boardSize;
}

void Board::resizeBoard(int newSize) {
    // Delete old board
    for (int i = 0; i < boardSize; ++i) {
        delete[] cells[i];
    }
    delete[] cells;

    // Create new board with updated size
    boardSize = newSize;
    cells = new Cell*[boardSize];
    for (int i = 0; i < boardSize; ++i) {
        cells[i] = new Cell[boardSize];
    }
}

Cell* Board::getCell(int x, int y) {
    if (isValidPosition(x, y)) {
        return &cells[y][x];
    }
    return nullptr;
}

bool Board::isValidPosition(int x, int y) const {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

bool Board::placePlayer(Player* player, int x, int y) {
    if (!isValidPosition(x, y) || !cells[y][x].isEmpty()) {
        return false;
    }
    cells[y][x].setPlayer(player);
    player->setPosition(x, y);
    return true;
}

bool Board::placeEnemy(Enemy* enemy, int x, int y) {
    if (!isValidPosition(x, y) || !cells[y][x].isEmpty()) {
        return false;
    }
    cells[y][x].setEnemy(enemy);
    enemy->setPosition(x, y);
    return true;
}

bool Board::movePlayer(Player* player) {
    bool isMoved = player->move();
    return isMoved;
}

bool Board::moveEnemy(Enemy* enemy, int toX, int toY) {
    Position currentPos = enemy->getPosition();
    if (!isValidPosition(toX, toY) || !cells[toY][toX].isEmpty()) {
        return false;
    }
    cells[currentPos.y][currentPos.x].setEnemy(nullptr);
    cells[toY][toX].setEnemy(enemy);
    enemy->setPosition(toX, toY);
    return true;
}

// void Board::createObstacle(int x, int y) {
//     if (isValidPosition(x, y) && cells[y][x].isEmpty()) {
//         cells[y][x].setType(CellType::OBSTACLE);
//     }
// }

void Board::displayBoard() {
    const int padding = 3; // Padding for centering the board
    const int cellWidth = 7; // Increased width of each cell for more spacing

    // Print top padding
    for (int i = 0; i < padding; i++) {
        cout << endl;
    }

    // Print column headers with extra spacing
    cout << string(padding * cellWidth, ' '); // Left padding
    cout << "       ";
    for (int x = 0; x < BOARD_SIZE; x++) {
        cout << WHITE;
        cout << setw(cellWidth) << x;
    }
    cout << endl;

    // Print the board rows
    for (int y = 0; y < boardSize; y++) {
        cout << string(padding * cellWidth, ' '); // Left padding
        cout << WHITE << setw(7) << y; // Row header
        for (int x = 0; x < boardSize; x++) {
            string cellContent;
            switch (cells[y][x].getType()) {
                case CellType::PLAYER: cellContent = "[ P ]"; break;
                case CellType::ENEMY: cellContent = "[ E ]"; break;
                // case CellType::OBSTACLE: cellContent = "[ # ]"; break;
                case CellType::EMPTY:
                default: cellContent = "[   ]"; break;
            }
            if(cellContent == "[ E ]") {
                cout << RED;
            }
            else if(cellContent == "[ P ]") {
                cout << GREEN;
            }
            else {
                cout << YELLOW;
            }
            cout << setw(cellWidth) << cellContent;
        }
        cout << endl << endl;
    }
    cout << RESET; // Reset color
    // Print bottom padding
    for (int i = 0; i < padding; i++) {
        cout << endl;
    }
}

bool Board::enemyEncountered(Player* player, Enemy* enemy) {
    Position playerPos = player->getPosition();
    Position enemyPos = enemy->getPosition();
    int dx = abs(playerPos.x - enemyPos.x);
    int dy = abs(playerPos.y - enemyPos.y);
    return (dx <= 1 && dy <= 0);
}

void Board::processCombat(Player* player, Enemy* enemy) {
    cout << "Combat initiated between Player and " << enemy->getName() << "!" << endl;

    // Combat loop
    bool isPlayerTurn = false; // Enemy attacks first
    while (player->getHealth() > 0 && enemy->getHealth() > 0) {
        if (isPlayerTurn) {
            // Player attacks enemy
            int playerDamage = 0;
            int playerLevel = player->getLevel();
            bool usedLevel2Weapon = false;

            // If player is level 2 or above, use level 2 (row 2) weapon first
            if (playerLevel >= 2) {
            Item** level2Row = player->getInventory(2);
            if (level2Row != nullptr) {
                for (int j = 0; j < 3; j++) {
                if (level2Row[j] != nullptr) {
                    playerDamage += level2Row[j]->getAttackPower();
                    usedLevel2Weapon = true;
                }
                }
            }
            }

            // If no level 2 weapon used, sum all inventory as fallback (original logic)
            if (!usedLevel2Weapon) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                Item** inventoryRow = player->getInventory(i);
                if (inventoryRow != nullptr && inventoryRow[j] != nullptr) {
                    playerDamage += inventoryRow[j]->getAttackPower();
                }
                }
            }
            }

            cout << "Player attacks " << enemy->getName() << " for " << playerDamage << " damage!" << endl;
            enemy->setHealth(enemy->getHealth() - playerDamage);

            if (enemy->getHealth() <= 0) {
            Position pos = enemy->getPosition();
            cells[pos.y][pos.x].setEnemy(nullptr);
            cout << enemy->getName() << " defeated!" << endl;
            return;
            }
        } 
        else {  // Enemy attacks player
            int enemyDamage = 10; // Base damage for enemy
            cout << enemy->getName() << " attacks Player for " << enemyDamage << " damage!" << endl;
            player->setHealth(player->getHealth() - enemyDamage);

            if (player->getHealth() <= 0) {
                cout << "Player defeated! Game Over!" << endl;
                return;
            }
        }

        // Switch turn
        isPlayerTurn = !isPlayerTurn;
    }
}
