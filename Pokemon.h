#ifndef POKEMON_H
#define POKEMON_H

#include <iostream>
#include <string>

using namespace std;

// Base class for all Pokémon types
class Pokemon {
protected:
    string name;       // Pokémon's name
    int maxHP;         // Maximum HP
    int currentHP;     // Current HP
    int attackPower;   // Base attack power
    bool hasUsedUltimate = false; // Track if ultimate has been used

public:
    // Constructor to initialize name, maxHP, attackPower
    Pokemon(string n, int hp, int atk) : name(n), maxHP(hp), currentHP(hp), attackPower(atk) {}

    virtual ~Pokemon() {} // Virtual destructor for proper cleanup in derived classes

    // Pure virtual functions to be implemented by derived classes
    virtual void attack(Pokemon& target) = 0;         // Basic attack
    virtual void useUltimate(Pokemon& target) = 0;    // Ultimate move
    virtual string getType() const = 0;               // Get Pokémon type
    virtual string getPassive() const = 0;            // Get passive ability (if any)

    // Take damage, reducing current HP but not below zero
    void takeDamage(int dmg) {
        currentHP -= dmg;
        if (currentHP < 0) currentHP = 0;
    }

    // Heal Pokémon by a certain amount, not exceeding maxHP
    void heal(int amount) {
        currentHP += amount;
        if (currentHP > maxHP) currentHP = maxHP;
    }

    // Check if Pokémon has fainted (HP 0 or below)
    bool isFainted() const {
        return currentHP <= 0;
    }

    // Check if Pokémon is alive (not fainted)
    bool isAlive() const {
        return !isFainted();
    }

    // Check if Pokémon can use ultimate attack (only once)
    bool canUseUltimate() const {
        return !hasUsedUltimate;
    }

    // Mark that ultimate has been used
    void markUltimateUsed() {
        hasUsedUltimate = true;
    }

    // Getter methods
    string getName() const { return name; }
    int getHP() const { return currentHP; }
    int getMaxHP() const { return maxHP; }
    int getAttackPower() const { return attackPower; }

    // Friend function to output Pokémon details
    friend ostream& operator<<(ostream& os, const Pokemon& p) {
        os << p.name << " [" << p.getType() << "] - HP: " << p.currentHP << "/" << p.maxHP;
        return os;
    }
};

#endif
