#pragma once
#include <string>
#include <iostream>
int BOARD_SIZE = 5;
using namespace std;



// In this game... Warrior is a normal character, but with extra attack and defense power
// while Magician and Theif might have low attack and defense power... but....
// Magician can teleport (jump cells)
// Theif can steal its enemy inventory

/*
Warrior will initialy have only one knife ... and can have upto 3 Inventory Items
Magician can have upto 3 Inventory Items
Theif will initialy have only one Pistol ... but when he encounters a enemy ... he can steal his inventory.
Enemies will have only one type of Item

All the characters can buy items from shop in exchange of points that have earned...
points are earned on the basis of level completion, killing enemies
*/

/*Also thinking to add other Items (e.g bomb) and cheat codes in the game*/

//========================================ITEMS THAT PLAYER AND ENEMIES WILL USE===============================

class Enemy; // Forward declaration

class Item{
protected:
    string itemName;
    int attackPower;
    int cost;
public:
    Item(string name = "none", int attackP = 0, int c = 0);
    string getItemName() const;
    int getAttackPower() const;
    int getCost() const;
    void setCost(int c);
    //there is not setAttackPower()...since attack power is fixed for each item... and it is initialized in constructor
    //and it is not changed later
    //setItemName() is not needed since item name is fixed for each item and it is initialized in constructor

    //it is pure virtual function just needed for health potion, other items will not use it
    virtual int getHealthIncrement() const{ cout << "This item does not have health increment." << endl; return 0; }
};

//*********This two items are for Warrior*********** 
class Knife : public Item{
public:
    Knife();
};

class Sword : public Item{
public:
    Sword();
};

//*********This two items are for Magician*********** 
class WaterBall : public Item{
public:
    WaterBall();
};

class FireBall : public Item{
public:
    FireBall();
};

//*********This two items are for Theif*********** 
class Pistol : public Item{
public:
    Pistol();
};

class Riffle : public Item{
public:
    Riffle();
};

//***********Health Potion can be bought from Shop*********** */
class HealthPotion : public Item{
    int healthIncrement;
public:
    HealthPotion(int hIncrement = 20);
    int getHealthIncrement() const; // Override to provide health increment
    //setHealthIncrement() is not needed since health increment is fixed and we are not changing it later
};

//========================================PLAYER CLASS, CHARACTER CLASSES AND ENEMY CLASS===============================

struct Position{
    int x, y;
};

class Player{
protected:
    int health;
    int points;
    Position position;
    Item** inventory[3];
    int level; //player's level is made ... so that it can be used to unlock new items
    //int maxInventorySize; //this variable is not needed since we are using fixed size array
public:
    string name;
    Player(string n = "none", int h = 100, int p = 10, int x = 0, int y = 0, int l = 1, int e = 0);
    void setHealth(int h);
    void setPosition(int x, int y);
    void setLevel(int l);
    void addPoints(int p); // New method to add points

    Item* getInventoryItemByName(const string& itemName) const; // New method to get inventory item by name

    void showInventory();
    void showStats();
    Position getPosition();
    int getHealth() const;
    int getPoints() const;
    int getLevel() const;
    Item** getInventory(int i) const; // New method to get inventory item
    virtual bool addInventory(Item& item) = 0;
    virtual bool move() = 0;
    void setPoints(int p);   
    void removeInventoryItem(const string& itemName); // New method to remove inventory item
    //remove item function should alse be here
};

class Warrior : public Player{
    const int maxKnives;
    int currentKnives;
    const int maxSwords;
    int currentSwords;
public:
    Warrior();
    bool addInventory(Item& item) override;
    bool move() override;
    int getSwords() const;
    int getKnives() const;
};

class Magician : public Player{
    const int maxWaterBalls;
    int currentWaterBalls;
    const int maxFireBalls;
    int currentFireBalls;
public:
    Magician();
    bool addInventory(Item& item) override;
    bool teleport(int x, int y);
    bool move() override; // will ask for teleportation
    int getWaterBalls() const;
    int getFireBalls() const;
};

class Theif : public Player {
    const int maxPistols;
    int currentPistols;
    const int maxRiffles;
    int currentRiffles;
public:
    Theif();
    bool addInventory(Item& item) override;
    void stealInventory(Enemy& enemy);
    bool move() override;
    int getPistols() const;
    int getRiffles() const;
};

//========================================SHOP CLASS===============================================

class Shop{
    Item* items[7]; // Fixed-size array for items
public:
    int itemCount; // Track the number of items in the shop
    Shop();
    ~Shop();

    void buyItem(Player& player, Item& item);
    void sellItem(Player& player, Item& item);
    void showItems();
    void visitShop(Player* player);
    Item* getItemByName(const string& itemName) const; // New method to get item by name
};

//========================================CELL CLASS AND BOARD CLASS==================================

enum class CellType {
    EMPTY,
    PLAYER,
    ENEMY,
    // OBSTACLE
};

class Enemy;

class Cell {
private:
    CellType type;
    Player* player;
    Enemy* enemy;
public:
    Cell();
    void setType(CellType newType);
    CellType getType() const;
    void setPlayer(Player* p);
    void setEnemy(Enemy* e);
    Player* getPlayer() const;
    Enemy* getEnemy() const;
    bool isEmpty() const;
    void clear();
};


class Enemy {
private:
    string name;
    int health;
    Position position;
    Item* inventoryItem;
public:
    Enemy(string n = "Enemy", int h = 50, int x = 0, int y = 0);
    void setPosition(int x, int y);
    Position getPosition() const;
    void setInventoryItem(Item* item);
    Item* getInventoryItem() const;
    int getHealth() const;
    void setHealth(int h);
    string getName() const;
};

class Board {
private:
    int boardSize;
    Cell** cells;
public:
    Board(int size = 5);
    ~Board();
    int getBoardSize() const;
    Cell* getCell(int x, int y);
    bool isValidPosition(int x, int y) const;
    bool placePlayer(Player* player, int x, int y);
    bool placeEnemy(Enemy* enemy, int x, int y);
    bool movePlayer(Player* player);
    bool moveEnemy(Enemy* enemy, int toX, int toY);
    // void createObstacle(int x, int y);
    void displayBoard();
    bool enemyEncountered(Player* player, Enemy* enemy);
    void processCombat(Player* player, Enemy* enemy);
    void resizeBoard(int newSize);
};


class Game {
private:
    string userName;
    Board* board;
    Player* player;
    Enemy* enemies[10]; // Fixed-size array for enemies
    int enemyCount;     // Track the number of enemies
    int level;
    Shop* shop;

    int selectCharacter();
    void initializePlayer(int characterChoice);
    void createEnemies();
    // void createObstacles();
    void gameLoop();
    bool handlePlayerMove();
    void moveEnemies();
    void handleCombat(Enemy* enemy);
    void removeEnemy(Enemy* enemy); // Helper to remove an enemy
    void gameInitialize();
    void setUserName(string name);
    void showMenu();
    void gameRules();
    void cheatCodes();
    void byeBye();
    
public:
    Game();
    ~Game();
    void gameStart();
    string getUserName() const;
    void saveGame();
    void loadGame();
};
