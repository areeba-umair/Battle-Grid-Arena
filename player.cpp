#include "Declerations.h"
#include<iostream>
#include<cmath>
#include<string>
#include<iomanip>
#include <conio.h>
#include<windows.h>
using namespace std;

// ==================== PLAYER CLASS IMPLEMENTATIONS ====================
Player::Player(string n , int h , int p , int x , int y , int l , int e ) : 
    name(n), health(h), points(p), level(l) {
    position.x = x;
    position.y = y;
    for (int i = 0; i < 3; i++){
        inventory[i] = new Item*[3];
        for (int j = 0; j < 3; j++){
            inventory[i][j] = nullptr;
        }   
    }
}

void Player::setHealth(int h) { 
    health = h; 
}

void Player::setPosition(int x, int y) { 
    position.x = x; 
    position.y = y; 
}

void Player::showInventory() {
    cout << "Inventory:   ";
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){ // Corrected increment variable to 'j'
            if(inventory[i][j]!=nullptr){
                cout << inventory[i][j]->getItemName() << "  |  ";
            }
        }
    }
    cout << endl;
}

void Player::showStats() {
    cout << BLUE;
    cout << "Name: " << name << endl;
    cout << "Health: " << health << endl;
    cout << YELLOW << "Points: " << points << endl;
    cout << BLUE << "Level: " << level << endl;
    cout << "Position: (" << position.x << ", " << position.y << ")" << endl;
    showInventory();
    cout << RESET;
}

Position Player::getPosition(){ 
    return position; 
}

int Player::getHealth() const { 
    return health; 
}

int Player::getPoints() const{
    return points;
}

void Player::addPoints(int p) {
    points += p;
}

void Player::setPoints(int p){
    points = p;
}


void Player::setLevel(int l){
    level = l;
}
int Player::getLevel() const {
    return level;
}
Item** Player::getInventory(int i) const {
    if (i >= 0 && i < 3) {
        return inventory[i];
    }
    return nullptr; // Return nullptr if the index is out of bounds
}


Item* Player::getInventoryItemByName(const string& itemName) const {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (inventory[i][j] != nullptr && inventory[i][j]->getItemName() == itemName) {
                return inventory[i][j];
            }
        }
    }
    return nullptr; // Item not found
}

void Player::removeInventoryItem(const string& itemName) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (inventory[i][j] != nullptr && inventory[i][j]->getItemName() == itemName) {
                delete inventory[i][j]; // Free the memory
                inventory[i][j] = nullptr; // Remove the item from inventory
                cout << "Removed " << itemName << " from inventory." << endl;
                return;
            }
        }
    }
    cout << itemName << " not found in inventory." << endl;
}

// ==================== WARRIOR CLASS IMPLEMENTATIONS ======================
Warrior::Warrior() : Player("Warrior", 100, 0, 0, 0, 1, 0), 
                    maxKnives(3), currentKnives(0),
                    maxSwords(3), currentSwords(0) {}

bool Warrior::addInventory(Item& item) {
    // Health Potions can be added at any level in row 2
    if (item.getItemName() == "Health Potion") {
        // Try to find an empty slot in row 2 for health potions
        for (int i = 0; i < 3; i++) {
            if (inventory[2][i] == nullptr) {
                inventory[2][i] = &item;
                cout << "Health Potion added to inventory.\n";
                return true;
            }
        }
        
        // If we get here, row 2 is full
        cout << "Health Potion row is full! Cannot add more potions.\n"; 
        return false;
    }
    
    // Level 1: Only knives allowed (in row 0)
    if (level == 1) {
        if (item.getItemName() == "Knife") {
            // Check if we've reached the max number of knives
            if (currentKnives >= maxKnives) {
                cout << "You cannot carry any more knives!\n";
                return false;
            }
            
            // Try to find an empty slot in row 0 for knives
            for (int i = 0; i < 3; i++) {
                if (inventory[0][i] == nullptr) {
                    inventory[0][i] = &item;
                    currentKnives++;
                    cout << "Knife added to inventory.\n";
                    return true;
                }
            }
            
            // If we get here, row 0 is full
            cout << "Knife row is full! Cannot add more knives.\n"; return false;
        } else {
            cout << "At level 1, you can only carry knives and health potions!\n"; return false;
        }
    }
    // Level 2: Both knives (row 0) and swords (row 1) allowed
    else if (level == 2) {
        if (item.getItemName() == "Knife") {
            // Check if we've reached the max number of knives
            if (currentKnives >= maxKnives) {
                cout << "You cannot carry any more knives!\n";
                return false;
            }
            
            // Try to find an empty slot in row 0 for knives
            for (int i = 0; i < 3; i++) {
                if (inventory[0][i] == nullptr) {
                    inventory[0][i] = &item;
                    currentKnives++;
                    cout << "Knife added to inventory.\n";
                    return true;
                }
            }
            
            // If we get here, row 0 is full
            cout << "Knife row is full! Cannot add more knives.\n"; return false;
        }
        else if (item.getItemName() == "Sword") {
            // Check if we've reached the max number of swords
            if (currentSwords >= maxSwords) {
                cout << "You cannot carry any more swords!\n";
                return false;
            }
            
            // Try to find an empty slot in row 1 for swords
            for (int i = 0; i < 3; i++) {
                if (inventory[1][i] == nullptr) {
                    inventory[1][i] = &item;
                    currentSwords++;
                    cout << "Sword added to inventory.\n";
                    return true;
                }
            }
            
            // If we get here, row 1 is full
            cout << "Sword row is full! Cannot add more swords.\n"; return false;
        }
        else {
            cout << "At level 2, you can only carry knives, swords, and health potions!\n"; return false;
        }
    }
    else {
        cout << "Invalid level or item type!\n"; return false;
    }
}

bool Warrior::move() {
    if(position.x < 0 || position.x >= BOARD_SIZE || position.y < 0 || position.y >= BOARD_SIZE){
        cout << "Invalid move\n";
        return false;
    }
    if (position.x + 1 < BOARD_SIZE) {
        position.x += 1; // Move to the next cell in the current row
        return true;
    } else if (position.y + 1 < BOARD_SIZE) {
        position.x = 0; // Reset to the first cell of the next row
        position.y += 1; // Move to the next row
        return true;
    } else {
        cout << "Warrior has reached the end of the board!" << endl;
        return true;
    }
}

int Warrior::getSwords() const { 
    return currentSwords; 
}

int Warrior::getKnives() const{
    return currentKnives;
}

// ==================== MAGICIAN CLASS IMPLEMENTATIONS ====================

Magician::Magician() : Player("Magician", 100, 0, 0, 0, 1, 0), 
                    maxFireBalls(3), currentFireBalls(0),
                    maxWaterBalls(3), currentWaterBalls(0){}


bool Magician::addInventory(Item& item) {
    // Health Potions can be added at any level in row 2
    if (item.getItemName() == "Health Potion") {
        // Try to find an empty slot in row 2 for health potions
        for (int i = 0; i < 3; i++) {
            if (inventory[2][i] == nullptr) {
                inventory[2][i] = &item;
                cout << "Health Potion added to inventory.\n";
                return true;
            }
        }
        
        // If we get here, row 2 is full
        cout << "Health Potion row is full! Cannot add more potions.\n";
        return false;
    }
    // Level 1: Only water balls allowed (in row 0)
    if (level == 1) {
        if (item.getItemName() == "Water Ball") {
            // Check if we've reached the max number of water balls
            if (currentWaterBalls >= maxWaterBalls) {
                cout << "You cannot carry any more water balls!\n";
                return false;
            }
            
            // Try to find an empty slot in row 0 for water balls
            for (int i = 0; i < 3; i++) {
                if (inventory[0][i] == nullptr) {
                    inventory[0][i] = &item;
                    currentWaterBalls++;
                    cout << "Water Ball added to inventory.\n";
                    return true;
                }
            }
            
            // If we get here, row 0 is full
            cout << "Water Ball row is full! Cannot add more water balls.\n"; return false;
        } else {
            cout << "At level 1, you can only carry water balls!\n"; return false;
        }
    }
    // Level 2: Both water balls (row 0) and fire balls (row 1) allowed
    else if (level == 2) {
        if (item.getItemName() == "Water Ball") {
            // Check if we've reached the max number of water balls
            if (currentWaterBalls >= maxWaterBalls) {
                cout << "You cannot carry any more water balls!\n";
                return false;
            }
            
            // Try to find an empty slot in row 0 for water balls
            for (int i = 0; i < 3; i++) {
                if (inventory[0][i] == nullptr) {
                    inventory[0][i] = &item;
                    currentWaterBalls++;
                    cout << "Water Ball added to inventory.\n";
                    return true;
                }
            }
            
            // If we get here, row 0 is full
            cout << "Water Ball row is full! Cannot add more water balls.\n"; return false;
        }
        else if (item.getItemName() == "Fire Ball") {
            // Check if we've reached the max number of fire balls
            if (currentFireBalls >= maxFireBalls) {
                cout << "You cannot carry any more fire balls!\n";
                return false;
            }
            
            // Try to find an empty slot in row 1 for fire balls
            for (int i = 0; i < 3; i++) {
                if (inventory[1][i] == nullptr) {
                    inventory[1][i] = &item;
                    currentFireBalls++;
                    cout << "Fire Ball added to inventory.\n";
                    return true;
                }
            }
            
            // If we get here, row 1 is full
            cout << "Fire Ball row is full! Cannot add more fire balls.\n"; return false;
        }
        else {
            cout << "At level 2, you can only carry water balls and fire balls!\n"; return false;
        }
    }
    else {
        cout << "Invalid level or item type!\n"; return false;
    }

}


bool Magician::teleport(int newX, int newY) {
    static int teleportCount = 0;
    static int lastLevel = -1;

    if (lastLevel != level) {
        teleportCount = 0;
        lastLevel = level;
    }

    if (teleportCount >= 3) {
        cout << "Teleport limit reached! You cannot teleport anymore.\n";
        return false;
    }

    while (true) {
        // Strict row-wise forward movement (same column or any column)
        int currentIndex = position.y * BOARD_SIZE + position.x;
        int newIndex = newY * BOARD_SIZE + newX;
        int stepsForward = newIndex - currentIndex;
        if (stepsForward > 0 && stepsForward <= 3) {
            // Valid forward teleport within 3 steps
            position.x = newX;
            position.y = newY;
            teleportCount++;
            return true;
        }else {
            cout << "Invalid teleport: You can only move forward a maximum of 3 cells (row-wise).\n";
            cout << "Enter new coordinates (x y): ";
            cin >> newX >> newY;
        }
    }
}



bool Magician::move() {
    if (position.x < 0 || position.x >= BOARD_SIZE || position.y < 0 || position.y >= BOARD_SIZE) {
        cout << "Invalid move\n";
        return false;
    }

    char input;
    bool wantTeleport = false;

    while (true) {
            if (_kbhit()) {
                input = _getch();
                break;
            }
            Sleep(10); // slight delay 
    }

    if (input == 't' || input == 'T') {
        wantTeleport = true;
        cout << "Teleporting...\n";
    } else {
        wantTeleport = false;
    }

    if (wantTeleport) {
        int newX, newY;
        cout << "Enter new coordinates (x y): ";
        cin >> newX >> newY;

        if (teleport(newX, newY)) {
            return true; // Teleportation successful, no further movement
        }
    }

    cout << "No teleportation...moving normally towards next cell\n";

    if (position.x + 1 < BOARD_SIZE) {
        position.x += 1; // Move to the next cell in the current row
        return true;
    } else if (position.y + 1 < BOARD_SIZE) {
        position.x = 0; // Reset to the first cell of the next row
        position.y += 1; // Move to the next row
        return true;
    } else {
        cout << "Magician has reached the end of the board!" << endl;
        return true;
    }
}

int Magician::getWaterBalls() const { 
    return currentWaterBalls; 
}

int Magician::getFireBalls() const{
    return currentFireBalls;
}
// ==================== THIEF CLASS IMPLEMENTATIONS ====================
Theif::Theif() : Player("Thief", 100, 0, 0, 0, 1, 0), 
                    maxPistols(3), currentPistols(0),
                    maxRiffles(3), currentRiffles(0) {}



bool Theif::addInventory(Item& item) {

    // Health Potions can be added at any level in row 2
    if (item.getItemName() == "Health Potion") {
        // Try to find an empty slot in row 2 for health potions
        for (int i = 0; i < 3; i++) {
            if (inventory[2][i] == nullptr) {
                inventory[2][i] = &item;
                cout << "Health Potion added to inventory.\n";
                return true;
            }
        }
        
        // If we get here, row 2 is full
        cout << "Health Potion row is full! Cannot add more potions.\n";
        return false;
    }
    // Level 1: Only pistols allowed in first row (row 0)
    if (level == 1) {
        // Check if item is a pistol
        if (item.getItemName() == "Pistol") {
            // Check if we've reached the max number of pistols
            if (currentPistols >= maxPistols) {
                cout << "You cannot carry any more pistols!\n";
                return false;
            }
            
            // Try to find an empty slot in row 0
            for (int i = 0; i < 3; i++) {
                if (inventory[0][i] == nullptr) {
                    inventory[0][i] = &item;
                    currentPistols++;
                    cout << "Pistol added to inventory.\n";
                    return true;
                }
            }
            
            // If we get here, row 0 is full
            cout << "Pistol row is full! Cannot add more pistols.\n"; return false;
        } else {
            cout << "At level 1, you can only carry pistols!\n"; return false;
        }
    }
    // Level 2: Both pistols (row 0) and rifles (row 1) allowed
    else if (level == 2) {
        if (item.getItemName() == "Pistol") {
            // Check if we've reached the max number of pistols
            if (currentPistols >= maxPistols) {
                cout << "You cannot carry any more pistols!\n";
                return false;
            }
            
            // Try to find an empty slot in row 0 for pistols
            for (int i = 0; i < 3; i++) {
                if (inventory[0][i] == nullptr) {
                    inventory[0][i] = &item;
                    currentPistols++;
                    cout << "Pistol added to inventory.\n";
                    return true;
                }
            }
            
            // If we get here, row 0 is full
            cout << "Pistol row is full! Cannot add more pistols.\n"; return false;
        }
        else if (item.getItemName() == "Riffle") {  // Note: You might want to fix the spelling to "Rifle"
            // Check if we've reached the max number of rifles
            if (currentRiffles >= maxRiffles) {
                cout << "You cannot carry any more riffles!\n";
                return  false;
            }
            
            // Try to find an empty slot in row 1 for rifles
            for (int i = 0; i < 3; i++) {
                if (inventory[1][i] == nullptr) {
                    inventory[1][i] = &item;
                    currentRiffles++;
                    cout << "Riffle added to inventory.\n";
                    return true;
                }
            }
            
            // If we get here, row 1 is full
            cout << "Riffle row is full! Cannot add more riffles.\n"; return false;
        }
        else {
            cout << "At level 2, you can only carry pistols and riffles!\n"; return false;
        }
    }
    else {
        cout << "Invalid level or item type!\n"; return false;
    }
  
}

void Theif::stealInventory(Enemy& enemy) {
    Item* stolenItem = enemy.getInventoryItem();
    if (stolenItem != nullptr) {
        // Add the stolen item to the thief's inventory
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if(inventory[i][j] == nullptr){
                    inventory[i][j] = stolenItem;
                    break;
                }
            }
        }
        cout << "Stole " << stolenItem->getItemName() << " from enemy!" << endl;
    } else {
        cout << "No item to steal from enemy!" << endl;
    }
}

bool Theif::move() {
    if (position.x < 0 || position.x >= BOARD_SIZE || position.y < 0 || position.y >= BOARD_SIZE) {
        cout << "Invalid move\n";
        return false;
    }

    if (position.x + 1 < BOARD_SIZE) {
        position.x += 1; // Move to the next cell in the current row
        return true;
    } else if (position.y + 1 < BOARD_SIZE) {
        position.x = 0; // Reset to the first cell of the next row
        position.y += 1; // Move to the next row
        return true;
    } else {
        cout << "Thief has reached the end of the board!" << endl;
        return true;
    }
}
int Theif::getPistols() const { 
    return currentPistols; 
}
int Theif::getRiffles() const{
    return currentRiffles;
}
