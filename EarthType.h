#include "Pokemon.h"
#include "TypeEffectiveness.h"

// EarthType.h
// Defines the EarthType Pokémon class, which inherits from the abstract base class "Pokemon".

class EarthType : public Pokemon {
public:
    // Constructor to initialize EarthType Pokémon with specific name, HP, and attack power
    EarthType(string n) : Pokemon(n, 120, 20) {}

    // Returns the Pokémon type as a string ("Earth")
    string getType() const override { return "Earth"; }

    // Returns the passive ability of the EarthType Pokémon
    string getPassive() const override { return "25% chance to block attack"; }

    // Performs a regular attack on the target Pokémon
    void attack(Pokemon& target) override {
        TypeEffectiveness te;  // Create an instance of TypeEffectiveness to get damage multiplier
        float mod = te.getMultiplier("Earth", target.getType());  // Get effectiveness multiplier based on types
        int dmg = static_cast<int>(attackPower * mod);  // Calculate final damage
        cout << name << " attacks with Rock Slam!\n";  // Print attack message
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
        float mod = te.getMultiplier("Earth", target.getType());  // Get effectiveness multiplier
        int dmg = static_cast<int>(attackPower * 2.0f * mod);  // Calculate double damage for ultimate
        cout << name << " uses Earthquake Smash!\n";  // Print ultimate attack message
        target.takeDamage(dmg);  // Apply damage to the target Pokémon
        markUltimateUsed();  // Mark that ultimate has been used
    }
};
