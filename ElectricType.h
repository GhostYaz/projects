#include "Pokemon.h"
#include "TypeEffectiveness.h"

// ElectricType.h
// Defines the ElectricType Pokémon class, which inherits from the abstract base class "Pokemon".

class ElectricType : public Pokemon {
public:
    // Constructor to initialize ElectricType Pokémon with specific name, HP, and attack power
    ElectricType(string n) : Pokemon(n, 100, 25) {}

    // Returns the Pokémon type as a string ("Electric")
    string getType() const override { return "Electric"; }

    // Returns the passive ability of the ElectricType Pokémon
    string getPassive() const override { return "20% chance to stun enemy"; }

    // Performs a regular attack on the target Pokémon
    void attack(Pokemon& target) override {
        TypeEffectiveness te;  // Create an instance of TypeEffectiveness to get damage multiplier
        float mod = te.getMultiplier("Electric", target.getType());  // Get effectiveness multiplier based on types
        int dmg = static_cast<int>(attackPower * mod);  // Calculate final damage
        cout << name << " attacks with Volt Strike!\n";  // Print attack message
        target.takeDamage(dmg);  // Apply damage to the target Pokémon
        cout << "It dealt " << dmg << " damage.\n";  // Print damage dealt
    }

    // Uses the ultimate attack, which deals double damage
    void useUltimate(Pokemon& target) override {
        if (!canUseUltimate()) {  // Check if ultimate has already been used
            cout << name << " has already used their ultimate!\n";  // Notify user
            return;
        }
        TypeEffectiveness te;  // Create an instance of TypeEffectiveness
        float mod = te.getMultiplier("Electric", target.getType());  // Get effectiveness multiplier
        int dmg = static_cast<int>(attackPower * 2.0f * mod);  // Calculate double damage for ultimate
        cout << name << " uses Thunder Wrath!\n";  // Print ultimate attack message
        target.takeDamage(dmg);  // Apply damage to the target Pokémon
        markUltimateUsed();  // Mark that ultimate has been used
    }
};
