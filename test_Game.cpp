#include <cassert>
#include <iostream>
#include "Trainer.h"
#include "FireType.h"
#include "WaterType.h"
#include "EarthType.h"

// Test adding Pokémon to a Trainer and getting the active Pokémon
void testTrainerAddAndGet() {
    Trainer t("Ash"); // Create a Trainer named Ash
    t.addPokemon(std::make_shared<FireType>("Charmander")); // Add Fire-type Pokémon
    t.addPokemon(std::make_shared<WaterType>("Squirtle"));  // Add Water-type Pokémon
    t.addPokemon(std::make_shared<EarthType>("Bulbasaur")); // Add Earth-type Pokémon

    assert(t.hasAlivePokemon()); // Assert trainer has at least one alive Pokémon
    assert(t.getActivePokemon()->isAlive()); // Assert active Pokémon is alive
}

// Test Pokémon fainting mechanics
void testPokemonFainting() {
    FireType f("FireMon");   // Create Fire-type Pokémon
    EarthType e("EarthMon"); // Create Earth-type Pokémon

    // Fire attacks Earth until Earth faints
    while (e.isAlive()) {
        f.attack(e); // Perform attack
    }

    assert(!e.isAlive()); // Assert Earth-type Pokémon has fainted
}

int main() {
    std::cout << "=== Running test_Game.cpp ===" << std::endl;

    testTrainerAddAndGet(); // Run add/get test
    std::cout << "✅ testTrainerAddAndGet passed!" << std::endl;

    testPokemonFainting();  // Run fainting test
    std::cout << "✅ testPokemonFainting passed!" << std::endl;

    std::cout << "All Game tests passed!" << std::endl;
    return 0;
}
