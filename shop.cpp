#include "Declerations.h"
#include<iostream>
#include<cmath>
#include<string>
#include<iomanip>
#include <conio.h>
#include<windows.h>
using namespace std;


// ==================== SHOP CLASS IMPLEMENTATIONS ====================

Shop::Shop() : itemCount(0) {
    // Initialize the shop with some items
    items[itemCount++] = new Knife();
    items[itemCount++] = new Sword();
    items[itemCount++] = new WaterBall();
    items[itemCount++] = new FireBall();
    items[itemCount++] = new Pistol();
    items[itemCount++] = new Riffle();
    items[itemCount++] = new HealthPotion(30);
}

void Shop::showItems() {
    system("CLS"); // Clear the screen for a fresh start
    cout << BLUE;
    cout << "========================= SHOP =======================" << endl;
    cout << WHITE;
    cout << "Available items in the shop:" << endl;
    cout << GREEN;
    for (int i = 0; i < itemCount; i++) {
        cout << i << ". " << items[i]->getItemName() << " (Cost: " << items[i]->getCost() << " points)" << endl;
    }
    cout << BLUE;
    cout << "======================================================" << endl;
    cout << WHITE;
}



void Shop::buyItem(Player& player, Item& item) {
    // Check if the item is available in the shop
    for (int i = 0; i < itemCount; i++) {
        if (items[i]->getItemName() == item.getItemName()) {
            // Check if the player has enough points to buy the item
            if (player.getPoints() >= item.getCost()) {
                // Add a new instance of the item to the player's inventory
                Item* newItem = nullptr;
                if (item.getItemName() == "Knife") newItem = new Knife();
                else if (item.getItemName() == "Sword") newItem = new Sword();
                else if (item.getItemName() == "Water Ball") newItem = new WaterBall();
                else if (item.getItemName() == "Fire Ball") newItem = new FireBall();
                else if (item.getItemName() == "Pistol") newItem = new Pistol();
                else if (item.getItemName() == "Riffle") newItem = new Riffle();
                else if (item.getItemName() == "Health Potion") newItem = new HealthPotion();

                if (newItem != nullptr) {
                    player.addInventory(*newItem);
                    player.setPoints(player.getPoints() - item.getCost());
                    cout << "Bought " << item.getItemName() << " from shop!" << endl;
                    cout << "Your current points: " << player.getPoints() << endl;
                } else {
                    cout << "Error: Unable to create item instance!" << endl;
                }
                return;
            } else {
                cout << "Not enough points to buy " << item.getItemName() << "!" << endl;
                return;
            }
        }
    }
    cout << "Item not available in shop!" << endl;
}

void Shop::sellItem(Player& player, Item& item) {
    // Check if the item is in the player's inventory
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (player.getInventory(i)[j] != nullptr && player.getInventory(i)[j]->getItemName() == item.getItemName()) {
                // Add the cost of the item back to the player's points
                player.addPoints(item.getCost());
                // Remove the item from the player's inventory
                delete player.getInventory(i)[j]; // Free the memory
                player.getInventory(i)[j] = nullptr;
                cout << "Sold " << item.getItemName() << " to shop!" << endl;
                return;
            }
        }
    }
    cout << "Item not found in player's inventory!" << endl;
}

void Shop::visitShop(Player* player) {
    int choice;
    do {
        showItems();
        cout << "-------------------------" << endl;
        player->showInventory();
        cin.ignore();
        cout << "Your current points: " << player->getPoints() << endl;
        cout << "Enter the item number to buy or -1 to exit: ";
        cin >> choice;

        if (choice >= 0 && choice < itemCount) {
            buyItem(*player, *items[choice]);
        }else if(choice == 1100){
            cout << "Enter the item number to sell: ";
            cin >> choice;
            if (choice >= 0 && choice < itemCount) {
                sellItem(*player, *items[choice]);
            } else {
                cout << "Invalid item number!" << endl;
            }
        }
         else if (choice == -1) {
            cout << "Exiting shop." << endl;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != -1);
}
Item* Shop::getItemByName(const string& itemName) const{
    for (int i = 0; i < itemCount; i++) {
        if (items[i]->getItemName() == itemName) {
            return items[i];
        }
    }
    return nullptr; // Item not found
}
