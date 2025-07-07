#include "Pokemon.h"
#include "TypeEffectiveness.h"

// CyberpunkType.h
// Defines the CyberpunkType Pokémon class, which inherits from the abstract base class "Pokemon".

class CyberpunkType : public Pokemon {
public:
    // Constructor to initialize CyberpunkType Pokémon with specific name, HP, and attack power
    CyberpunkType(string n) : Pokemon(n, 105, 23) {}

    // Returns the Pokémon type as a string ("Cyberpunk")
    string getType() const override { return "Cyberpunk"; }

    // Returns the passive ability of the CyberpunkType Pokémon
    string getPassive() const override { return "Random stat boost each turn"; }

    // Performs a regular attack on the target Pokémon
    void attack(Pokemon& target) override {
        TypeEffectiveness te;  // Create an instance of TypeEffectiveness to get damage multiplier
        float mod = te.getMultiplier("Cyberpunk", target.getType());  // Get effectiveness multiplier based on types
        int dmg = static_cast<int>(attackPower * mod);  // Calculate final damage
        cout << name << " attacks with Data Surge!\n";  // Print attack message
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
        float mod = te.getMultiplier("Cyberpunk", target.getType());  // Get effectiveness multiplier
        int dmg = static_cast<int>(attackPower * 2.0f * mod);  // Calculate double damage for ultimate
        cout << name << " uses Hack Storm!\n";  // Print ultimate attack message
        target.takeDamage(dmg);  // Apply damage to the target Pokémon
        markUltimateUsed();  // Mark that ultimate has been used
    }
};
