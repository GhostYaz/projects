#include <cassert>
#include <iostream>
#include "FireType.h"
#include "WaterType.h"
#include "EarthType.h"
#include "ElectricType.h"

// Test that Pokémon initializes correctly
void testPokemonInitialization() {
    FireType f("Charizard"); // Create a FireType Pokémon named Charizard
    assert(f.getName() == "Charizard");       // Check name is set correctly
    assert(f.getHP() == f.getMaxHP());         // Check HP initialized to max HP
    assert(f.getType() == "Fire");             // Check type is Fire
}

// Test that attack reduces target's HP
void testAttackDamage() {
    FireType f("Charmander");                   // Attacker: FireType
    WaterType w("Squirtle");                    // Defender: WaterType

    int oldHP = w.getHP();                      // Save old HP
    f.attack(w);                               // Attack WaterType
    assert(w.getHP() < oldHP);                  // Target HP should decrease
}

// Test that ultimate attack works and can only be used once
void testUltimate() {
    EarthType e("Golem");                       // Attacker: EarthType
    ElectricType el("Pikachu");                 // Defender: ElectricType

    int oldHP = el.getHP();                     // Save old HP
    e.useUltimate(el);                         // Use ultimate on defender
    assert(el.getHP() < oldHP);                 // Target HP should decrease
    assert(!e.canUseUltimate());                // Attacker should no longer be able to use ultimate
}

int main() {
    std::cout << "=== Running test_Pokemon.cpp ===" << std::endl;

    testPokemonInitialization();                // Run initialization test
    std::cout << "✅ testPokemonInitialization passed!" << std::endl;

    testAttackDamage();                          // Run attack damage test
    std::cout << "✅ testAttackDamage passed!" << std::endl;

    testUltimate();                             // Run ultimate attack test
    std::cout << "✅ testUltimate passed!" << std::endl;

    std::cout << "All Pokémon tests passed!" << std::endl;
    return 0;
}
