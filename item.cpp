#include "Declerations.h"
#include<iostream>
#include<cmath>
#include<string>
#include<iomanip>
#include <conio.h>
#include<windows.h>
using namespace std;

// ==================== ITEM CLASS IMPLEMENTATIONS ====================
Item::Item(string name, int attackP, int c) : itemName(name), attackPower(attackP), cost(c) {}

string Item::getItemName() const{
    return itemName;
}

int Item::getAttackPower() const{
    return attackPower;
}

int Item::getCost() const{
    return cost;
}

void Item::setCost(int c){
    cost = c;
}

Knife::Knife() : Item("Knife", 15, 10) {}
Sword::Sword() : Item("Sword", 30, 20) {}
WaterBall::WaterBall() : Item("Water Ball", 10, 10) {}
FireBall::FireBall() : Item("Fire Ball", 25, 20) {}
Pistol::Pistol() : Item("Pistol", 20, 10) {}
Riffle::Riffle() : Item("Riffle", 35, 20) {}

HealthPotion::HealthPotion(int hIncrement) : Item("Health Potion", 0, 30), healthIncrement(hIncrement) {}
int HealthPotion::getHealthIncrement() const {
    return healthIncrement;
}
