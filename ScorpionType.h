#include "Pokemon.h"
#include "TypeEffectiveness.h"

// ScorpionType class - represents the Scorpion-type Pokémon
class ScorpionType : public Pokemon {
public:
    // Constructor: initializes name, HP (100), and attack power (26)
    ScorpionType(string n) : Pokemon(n, 100, 26) {}

    // Return the Pokémon type
    string getType() const override { return "Scorpion"; }

    // Return the passive ability description
    string getPassive() const override { return "15% chance to double strike"; }

    // Basic attack implementation
    void attack(Pokemon& target) override {
        TypeEffectiveness te; // Create TypeEffectiveness object to check multipliers
        float mod = te.getMultiplier("Scorpion", target.getType()); // Get type advantage multiplier
        int dmg = static_cast<int>(attackPower * mod); // Calculate damage
        cout << name << " attacks with Venom Jab!\n";
        target.takeDamage(dmg); // Deal damage to target
        cout << "It dealt " << dmg << " damage.\n";
    }

    // Ultimate move: Poison Rage
    void useUltimate(Pokemon& target) override {
        if (!canUseUltimate()) { // Check if ultimate has already been used
            cout << name << " has already used their ultimate!\n";
            return;
        }
        TypeEffectiveness te; // Get multiplier for ultimate attack
        float mod = te.getMultiplier("Scorpion", target.getType());
        int dmg = static_cast<int>(attackPower * 2.0f * mod); // Double damage for ultimate
        cout << name << " uses Poison Rage!\n";
        target.takeDamage(dmg); // Deal damage
        markUltimateUsed(); // Mark ultimate as used
    }
};
