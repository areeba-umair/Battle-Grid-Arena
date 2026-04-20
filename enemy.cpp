#include "Declerations.h"
#include<iostream>
#include<cmath>
#include<string>
#include<iomanip>
#include <conio.h>
#include<windows.h>
using namespace std;



// ==================== ENEMY CLASS IMPLEMENTATIONS ====================
Enemy::Enemy(string n, int h, int x, int y) : 
    name(n), health(h), inventoryItem(nullptr) {
    position.x = x;
    position.y = y;
}

void Enemy::setPosition(int x, int y) { 
    position.x = x; 
    position.y = y; 
}

Position Enemy::getPosition() const { 
    return position; 
}

void Enemy::setInventoryItem(Item* item) { 
    inventoryItem = item; //Aggregation
}

Item* Enemy::getInventoryItem() const { 
    return inventoryItem; 
}

int Enemy::getHealth() const { 
    return health; 
}

void Enemy::setHealth(int h) { 
    health = h; 
}

string Enemy::getName() const { 
    return name; 
}
