#ifndef WATERTYPE_H
#define WATERTYPE_H

#include "Pokemon.h"
#include "TypeEffectiveness.h"
#include <iostream>

// WaterType class, inherits from base Pokemon class
class WaterType : public Pokemon {
public:
    // Constructor: initializes name, HP (110), and attack power (22)
    WaterType(std::string n) : Pokemon(n, 110, 22) {}

    // Return the Pokémon type as a string
    std::string getType() const override { return "Water"; }

    // Return description of passive ability
    std::string getPassive() const override { return "Heals 10% HP each turn"; }

    // Basic attack implementation
    void attack(Pokemon& target) override {
        TypeEffectiveness te; // Instance to check type effectiveness
        float mod = te.getMultiplier("Water", target.getType()); // Get multiplier for Water attacking target's type
        int dmg = static_cast<int>(attackPower * mod); // Calculate damage
        std::cout << name << " attacks with Aqua Slash!\n";
        target.takeDamage(dmg); // Apply damage
        std::cout << "It dealt " << dmg << " damage.\n";
    }

    // Ultimate attack implementation
    void useUltimate(Pokemon& target) override {
        if (!canUseUltimate()) { // Check if ultimate has been used before
            std::cout << name << " has already used their ultimate!\n";
            return;
        }
        TypeEffectiveness te; // Check type effectiveness again
        float mod = te.getMultiplier("Water", target.getType());
        int dmg = static_cast<int>(attackPower * 2.0f * mod); // Ultimate deals double damage
        std::cout << name << " uses Tsunami Burst!\n";
        target.takeDamage(dmg); // Apply damage
        markUltimateUsed(); // Mark ultimate as used so it can't be used again
    }
};

#endif
