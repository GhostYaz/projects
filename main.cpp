#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <SFML/Graphics.hpp> // Include SFML for Trainer name input
#include "Trainer.h"
#include "InputScreens.h"    // For getTrainerName()
#include "FireType.h"
#include "WaterType.h"
#include "EarthType.h"
#include "ElectricType.h"
#include "AirType.h"
#include "CyberpunkType.h"
#include "LavaType.h"
#include "TsunamiWaterType.h"

using namespace std;

// Helper function to create a Pokemon by type and name
shared_ptr<Pokemon> createPokemonByName(const string& type, const string& name) {
    string t = type;
    transform(t.begin(), t.end(), t.begin(), ::tolower); // Convert to lowercase for easier matching

    if (t == "fire") return make_shared<FireType>(name);
    if (t == "water") return make_shared<WaterType>(name);
    if (t == "earth") return make_shared<EarthType>(name);
    if (t == "electric") return make_shared<ElectricType>(name);
    if (t == "air") return make_shared<AirType>(name);
    if (t == "cyberpunk") return make_shared<CyberpunkType>(name);

    return nullptr; // Invalid type
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed random for CPU turn

    // ========== SFML Trainer Name Input ==========
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pokemon Battle - Trainer Setup");
    string trainerName = getTrainerName(window); // GUI input
    if (trainerName.empty()) {
        cout << "Trainer name not entered. Exiting game.\n";
        return 0;
    }

    // Create player and CPU trainers
    Trainer player(trainerName);
    Trainer cpu("CPU");

    // ========== Console Pokemon Selection ==========
    cout << "\nChoose 3 Pokemon for your team:\n";
    for (int i = 0; i < 3; ++i) {
        string typeChoice;
        string name;

        cout << "\nChoose your Pokemon (Fire, Water, Earth, Electric, Air, Cyberpunk): ";
        cin >> typeChoice;
        cin.ignore(); // Clear leftover newline

        cout << "Give your Pokemon a name: ";
        getline(cin, name); // Allow multi-word names

        // Create chosen Pokemon
        auto poke = createPokemonByName(typeChoice, name);
        if (poke) {
            player.addPokemon(poke);
        } else {
            cout << "Invalid Pokemon type. Try again.\n";
            --i; // Retry current slot
        }
    }

    // ========== CPU Team Setup ==========
    // Predefined CPU team
    cpu.addPokemon(make_shared<WaterType>("EnemyWater"));
    cpu.addPokemon(make_shared<AirType>("EnemyAir"));
    cpu.addPokemon(make_shared<CyberpunkType>("EnemyCyber"));

    // ========== Game Loop ==========
    while (player.hasAlivePokemon() && cpu.hasAlivePokemon()) {
        // Display current teams
        player.displayTeam();
        cpu.displayTeam();

        // Player's turn
        auto atkPoke = player.getActivePokemon();
        auto defPoke = cpu.getActivePokemon();

        cout << "\n" << player.getName() << "'s Turn: " << atkPoke->getName() << endl;
        cout << "1. Attack\n2. Use Ultimate\nChoose: ";
        int move;
        cin >> move;

        if (move == 2 && atkPoke->canUseUltimate()) {
            atkPoke->useUltimate(*defPoke); // Use ultimate attack
        } else {
            atkPoke->attack(*defPoke); // Use basic attack
        }

        // Check if CPU still has alive Pokemon
        if (!cpu.hasAlivePokemon()) break;

        // CPU's turn
        atkPoke = cpu.getActivePokemon();
        defPoke = player.getActivePokemon();
        cout << "\nCPU's Turn: " << atkPoke->getName() << endl;
        int cpuChoice = rand() % 2 + 1; // Randomly choose attack or ultimate
        if (cpuChoice == 2 && atkPoke->canUseUltimate()) {
            atkPoke->useUltimate(*defPoke);
        } else {
            atkPoke->attack(*defPoke);
        }
    }

    // ========== Result ==========
    cout << "\n==== GAME OVER ====\n";
    if (player.hasAlivePokemon())
        cout << player.getName() << " wins!\n";
    else
        cout << cpu.getName() << " wins!\n";

    // Save player team to file
    player.saveToFile("player_team.txt");

    return 0;
}
