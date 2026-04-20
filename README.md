# 🎮 GridQuest: Battle Arena

## 📌 Overview
GridQuest: Battle Arena is a C++ console-based turn-based strategy game built using Object-Oriented Programming (OOP) concepts. The game features multiple player classes, inventory systems, and grid-based movement with combat mechanics.

Players choose between different character types (Warrior, Magician, Thief), each with unique abilities, movement styles, and inventory restrictions.

---

## 🧠 Features

### 👤 Player Classes
- **Warrior**
  - Uses knives (Level 1) and swords (Level 2)
  - Balanced combat strength
- **Magician**
  - Uses water balls and fire balls
  - Special ability: Teleport (limited usage)
- **Thief**
  - Uses pistols and rifles
  - Can steal items from enemies

---

## 🎒 Inventory System
- 3x3 grid-based inventory
- Each player has different item restrictions based on level
- Health potions can be stored separately
- Inventory management includes:
  - Add items
  - Remove items
  - Display items
  - Capacity limits per weapon type

---

## 🗺️ Movement System
- Grid-based movement system
- Each player moves cell-by-cell on a board
- Special movement ability:
  - Magician can teleport within limits
- Boundary checks implemented

---

## ⚔️ Combat Features
- Turn-based combat system
- Damage calculated using inventory items
- Enemy encounters trigger automatic combat
- Health-based win/lose system

---

## 🏗️ OOP Concepts Used
- Classes & Objects
- Inheritance (Player → Warrior/Magician/Thief)
- Polymorphism
- Encapsulation
- Dynamic Memory Allocation
- Composition (Inventory system)
