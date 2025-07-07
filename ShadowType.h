#include "Pokemon.h"
#include "TypeEffectiveness.h"

//ShadowType.h
// Defines the ShadowType Pokémon class, which inherits from the abstract base class "Pokemon"
class ShadowType : public Pokemon {
public:
    // Constructor: initializes name, HP (90), and attack power (27)
    ShadowType(string n) : Pokemon(n, 90, 27) {}

    // Return the Pokémon type
    string getType() const override { return "Shadow"; }

    // Return the passive ability description
    string getPassive() const override { return "Hides for 1 turn (invulnerable)"; }

    // Basic attack implementation
    void attack(Pokemon& target) override {
        TypeEffectiveness te; // Create TypeEffectiveness object to get multipliers
        float mod = te.getMultiplier("Shadow", target.getType()); // Get type advantage multiplier
        int dmg = static_cast<int>(attackPower * mod); // Calculate damage
        cout << name << " attacks with Dark Fang!\n";
        target.takeDamage(dmg); // Deal damage to target
        cout << "It dealt " << dmg << " damage.\n";
    }

    // Ultimate move: Shadow Realm
    void useUltimate(Pokemon& target) override {
        if (!canUseUltimate()) { // Check if ultimate has already been used
            cout << name << " has already used their ultimate!\n";
            return;
        }
        TypeEffectiveness te; // Get multiplier for ultimate attack
        float mod = te.getMultiplier("Shadow", target.getType());
        int dmg = static_cast<int>(attackPower * 2.0f * mod); // Double damage for ultimate
        cout << name << " uses Shadow Realm!\n";
        target.takeDamage(dmg); // Deal damage
        markUltimateUsed(); // Mark ultimate as used
    }
};
