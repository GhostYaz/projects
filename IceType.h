#include "Pokemon.h"
#include "TypeEffectiveness.h"

// IceType.h
// Defines the IceType Pokémon class, which inherits from the abstract base class "Pokemon".

class IceType : public Pokemon {
public:
    // Constructor to initialize IceType Pokémon with specific name, HP (100), and attack power (25)
    IceType(string n) : Pokemon(n, 100, 25) {}

    // Returns the Pokémon type as a string ("Ice")
    string getType() const override { return "Ice"; }

    // Returns the passive ability of the IceType Pokémon
    string getPassive() const override { return "Slows enemy (10% less ATK)"; }

    // Performs a regular attack on the target Pokémon
    void attack(Pokemon& target) override {
        TypeEffectiveness te;  // Create an instance of TypeEffectiveness to get damage multiplier
        float mod = te.getMultiplier("Ice", target.getType());  // Get effectiveness multiplier based on types
        int dmg = static_cast<int>(attackPower * mod);  // Calculate final damage
        cout << name << " attacks with Frost Shard!\n";  // Print attack message
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
        float mod = te.getMultiplier("Ice", target.getType());  // Get effectiveness multiplier
        int dmg = static_cast<int>(attackPower * 2.0f * mod);  // Calculate double damage for ultimate
        cout << name << " uses Frost Nova!\n";  // Print ultimate attack message
        target.takeDamage(dmg);  // Apply damage to the target Pokémon
        markUltimateUsed();  // Mark that ultimate has been used
    }
};
