#ifndef FIRETYPE_H
#define FIRETYPE_H

#include "Pokemon.h"
#include "TypeEffectiveness.h"
#include <iostream>

// FireType.h
// Defines the FireType Pokémon class, which inherits from the abstract base class "Pokemon".

class FireType : public Pokemon {
public:
    // Constructor to initialize FireType Pokémon with specific name, HP (100), and attack power (25)
    FireType(std::string n) : Pokemon(n, 100, 25) {}

    // Returns the Pokémon type as a string ("Fire")
    std::string getType() const override { return "Fire"; }

    // Returns the passive ability of the FireType Pokémon
    std::string getPassive() const override { return "10% chance to burn (5% HP over 2 turns)"; }

    // Performs a regular attack on the target Pokémon
    void attack(Pokemon& target) override {
        TypeEffectiveness te;  // Create an instance of TypeEffectiveness to get damage multiplier
        float mod = te.getMultiplier("Fire", target.getType());  // Get effectiveness multiplier based on types
        int dmg = static_cast<int>(attackPower * mod);  // Calculate final damage
        std::cout << name << " uses Flame Burst!\n";  // Print attack message
        target.takeDamage(dmg);  // Apply damage to the target Pokémon
        std::cout << "It dealt " << dmg << " damage.\n";  // Print damage dealt
    }

    // Uses the ultimate attack, which deals double damage
    void useUltimate(Pokemon& target) override {
        if (!canUseUltimate()) {  // Check if ultimate has already been used
            std::cout << name << " has already used their ultimate!\n";  // Notify user
            return;
        }
        TypeEffectiveness te;  // Create an instance of TypeEffectiveness
        float mod = te.getMultiplier("Fire", target.getType());  // Get effectiveness multiplier
        int dmg = static_cast<int>(attackPower * 2.0f * mod);  // Calculate double damage for ultimate
        std::cout << name << " uses Flame Overdrive!\n";  // Print ultimate attack message
        target.takeDamage(dmg);  // Apply damage to the target Pokémon
        markUltimateUsed();  // Mark that ultimate has been used
    }
};

#endif
