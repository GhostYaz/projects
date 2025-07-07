#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "Pokemon.h"
#include "TypeEffectiveness.h"

// GameManager.h
// Manages the 3v3 Pokémon battle logic for the graphical SFML interface

class GameManager {
private:
    std::vector<Pokemon*> playerTeam;  // Player's team of Pokémon
    std::vector<Pokemon*> cpuTeam;     // CPU's team of Pokémon
    int playerIndex = 0;               // Index of current active player Pokémon
    int cpuIndex = 0;                  // Index of current active CPU Pokémon
    bool playerUltimateUsed = false;   // Tracks if player used their ultimate move
    TypeEffectiveness typeChart;       // Type effectiveness chart for damage calculation

public:
    // Constructor: initializes the player and CPU teams
    GameManager(const std::vector<Pokemon*>& player, const std::vector<Pokemon*>& cpu) {
        playerTeam = player;
        cpuTeam = cpu;
    }

    // Checks if player still has Pokémon remaining
    bool hasPlayerRemaining() const {
        return playerIndex < 3;
    }

    // Checks if CPU still has Pokémon remaining
    bool hasCpuRemaining() const {
        return cpuIndex < 3;
    }

    // Returns the active player Pokémon
    Pokemon* getPlayerPokemon() {
        return playerTeam[playerIndex];
    }

    // Returns the active CPU Pokémon
    Pokemon* getCpuPokemon() {
        return cpuTeam[cpuIndex];
    }

    // Player attacks CPU Pokémon (regular or ultimate attack)
    void playerAttack(bool useUltimate) {
        int base = getRandom(25, 40);  // Random base damage
        int dmg = useUltimate ? static_cast<int>(base * 2.0f) : base;  // Double damage if ultimate
        float mult = typeChart.getMultiplier(getPlayerPokemon()->getType(), getCpuPokemon()->getType());  // Type multiplier
        getCpuPokemon()->takeDamage(dmg * mult);  // Apply damage to CPU Pokémon
        if (useUltimate) playerUltimateUsed = true;  // Mark ultimate as used
    }

    // CPU attacks player Pokémon (always regular attack)
    void cpuAttack() {
        int base = getRandom(25, 40);  // Random base damage
        float mult = typeChart.getMultiplier(getCpuPokemon()->getType(), getPlayerPokemon()->getType());  // Type multiplier
        getPlayerPokemon()->takeDamage(base * mult);  // Apply damage to player Pokémon
    }

    // Returns whether the player has used their ultimate this round
    bool isPlayerUltimateUsed() const {
        return playerUltimateUsed;
    }

    // Move to the next player Pokémon and reset ultimate usage flag
    void nextPlayer() {
        playerIndex++;
        playerUltimateUsed = false;
    }

    // Move to the next CPU Pokémon
    void nextCpu() {
        cpuIndex++;
    }

    // Checks if the current player Pokémon has fainted
    bool isPlayerFainted() {
        return !getPlayerPokemon()->isAlive();
    }

    // Checks if the current CPU Pokémon has fainted
    bool isCpuFainted() {
        return !getCpuPokemon()->isAlive();
    }

    // Checks if battle is over (when either team has lost all 3 Pokémon)
    bool isBattleOver() const {
        return playerIndex >= 3 || cpuIndex >= 3;
    }

    // Returns the result of the battle as a string ("You Win!" or "You Lose!")
    std::string getResult() const {
        if (playerIndex >= 3) return "You Lose!";
        if (cpuIndex >= 3) return "You Win!";
        return "";
    }

private:
    // Generates a random integer between min and max (inclusive)
    int getRandom(int min, int max) {
        static bool seeded = false;  // Ensure random number generator is seeded only once
        if (!seeded) {
            std::srand(static_cast<unsigned>(std::time(nullptr)));  // Seed RNG with current time
            seeded = true;
        }
        return min + std::rand() % (max - min + 1);
    }
};

#endif
