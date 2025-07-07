#include "Pokemon.h"
#include "TypeEffectiveness.h"

// MagicType.h
// Defines the MagicType Pokémon class, which inherits from the abstract base class "Pokemon"

class MagicType : public Pokemon {
public:
    // Constructor to initialize MagicType Pokémon with specific name, HP (95), and attack power (28)
    MagicType(string n) : Pokemon(n, 95, 28) {}

    // Returns the Pokémon type as a string ("Magic")
    string getType() const override { return "Magic"; }

    // Returns the passive ability of the MagicType Pokémon
    string getPassive() const override { return "Reflect one attack per match"; }

    // Performs a regular attack on the target Pokémon
    void attack(Pokemon& target) override {
        TypeEffectiveness te;  // Create an instance of TypeEffectiveness to get damage multiplier
        float mod = te.getMultiplier("Magic", target.getType());  // Get effectiveness multiplier based on types
        int dmg = static_cast<int>(attackPower * mod);  // Calculate final damage
        cout << name << " attacks with Arcane Bolt!\n";  // Print attack message
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
        float mod = te.getMultiplier("Magic", target.getType());  // Get effectiveness multiplier
        int dmg = static_cast<int>(attackPower * 2.0f * mod);  // Calculate double damage for ultimate
        cout << name << " uses Arcane Surge!\n";  // Print ultimate attack message
        target.takeDamage(dmg);  // Apply damage to the target Pokémon
        markUltimateUsed();  // Mark that ultimate has been used
    }
};

