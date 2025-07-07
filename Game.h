#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Trainer.h"

using namespace std;

// Game.h
// Defines the Game class, which manages the main game loop and turns between trainers

class Game {
private:
    Trainer player;  // Player-controlled trainer
    Trainer enemy;   // CPU-controlled trainer

public:
    // Constructor to initialize player and enemy trainers by name
    Game(string playerName, string enemyName)
        : player(playerName), enemy(enemyName) {}

    // Handles a single turn for a trainer (attacker) against the defender
    void takeTurn(Trainer& attacker, Trainer& defender) {
        auto atkPoke = attacker.getActivePokemon();  // Get active Pokémon for attacker
        auto defPoke = defender.getActivePokemon();  // Get active Pokémon for defender

        // If attacker has no active Pokémon (fainted), skip turn
        if (!atkPoke || atkPoke->isFainted()) {
            cout << atkPoke->getName() << " has fainted and cannot move.\n";
            return;
        }

        // Prompt player for action
        cout << "\n" << attacker.getName() << "'s Turn: " << atkPoke->getName() << endl;
        cout << "1. Attack\n2. Use Ultimate\nChoose: ";
        int choice;
        cin >> choice;

        // If player chooses Ultimate and can use it, perform ultimate attack
        if (choice == 2 && atkPoke->canUseUltimate()) {
            atkPoke->useUltimate(*defPoke);
        } else {  // Otherwise, perform regular attack
            atkPoke->attack(*defPoke);
        }

        // If defender's Pokémon has fainted, announce and switch to next
        if (defPoke->isFainted()) {
            cout << defPoke->getName() << " has fainted!\n";
            defender.nextAvailablePokemon();  // Placeholder: can expand to auto-switch logic
        }
    }

    // Starts the main game loop, alternating turns until one trainer is out of Pokémon
    void start() {
        while (player.hasAlivePokemon() && enemy.hasAlivePokemon()) {
            player.displayTeam();  // Show player's team
            enemy.displayTeam();   // Show enemy's team
            takeTurn(player, enemy);  // Player's turn
            if (!enemy.hasAlivePokemon()) break;  // End loop if enemy is out
            takeTurn(enemy, player);  // Enemy's turn
        }

        // Print final game result
        cout << "\n==== GAME OVER ====\n";
        if (player.hasAlivePokemon())
            cout << player.getName() << " wins!\n";
        else
            cout << enemy.getName() << " wins!\n";

        // Save player's final team state to file
        player.saveToFile("player_team.txt");
    }

    // Accessor methods to get player and enemy trainers
    Trainer& getPlayer() { return player; }
    Trainer& getEnemy() { return enemy; }
};

#endif
