#ifndef TRAINER_H
#define TRAINER_H

#include <iostream>
#include <vector>
#include <memory>
#include "Pokemon.h"
#include <fstream>

using namespace std;

// Trainer class represents a Pokémon Trainer with a team of Pokémon
class Trainer {
private:
    string name;                             // Trainer's name
    vector<shared_ptr<Pokemon>> team;       // Team of up to 3 Pokémon (shared pointers)

public:
    // Constructor to initialize trainer name
    Trainer(const string& name) : name(name) {}

    // Getter for trainer's name
    string getName() const {
        return name;
    }

    // Add a Pokémon to the team if team has less than 3 Pokémon
    void addPokemon(shared_ptr<Pokemon> pokemon) {
        if (team.size() < 3) {
            team.push_back(pokemon);
        } else {
            cout << "Team is full!" << endl; // Notify if team already full
        }
    }

    // Get the first alive Pokémon from the team as the active Pokémon
    shared_ptr<Pokemon> getActivePokemon() const {
        for (const auto& poke : team) {
            if (poke->isAlive()) {
                return poke;
            }
        }
        return nullptr; // No alive Pokémon found
    }

    // Check if the trainer has at least one alive Pokémon
    bool hasAlivePokemon() const {
        for (const auto& poke : team) {
            if (poke->isAlive()) {
                return true;
            }
        }
        return false;
    }

    // Placeholder for logic to switch to next available Pokémon (not implemented yet)
    void nextAvailablePokemon() {
        // Could implement forced switch or rotation here
    }

    // Display each Pokémon's name, type, and current HP; show if fainted
    void displayTeam() const {
        for (const auto& poke : team) {
            cout << poke->getName() << " [" << poke->getType() << "] - HP: "
                 << poke->getHP() << "/" << poke->getMaxHP();
            if (!poke->isAlive()) {
                cout << " (Fainted)";
            }
            cout << endl;
        }
    }

    // Save team info to file: name, type, current/max HP for each Pokémon
    void saveToFile(const string& filename) const {
        ofstream out(filename);
        for (const auto& poke : team) {
            out << poke->getName() << "," << poke->getType()
                << "," << poke->getHP() << "/" << poke->getMaxHP() << endl;
        }
        out.close();
    }
};

#endif
