#ifndef BATTLE_SCREEN_H
#define BATTLE_SCREEN_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Pokemon.h"
#include "TypeEffectiveness.h"

// Generates a random damage value between min and max (inclusive)
int getRandomDamage(int min, int max) {
    static std::random_device rd;  // Seed for random number generator
    static std::mt19937 rng(rd()); // Mersenne Twister RNG
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

// Draws a health bar at specified (x, y) with given hp value
void drawHealthBar(sf::RenderWindow& window, int x, int y, int hp) {
    sf::RectangleShape outline(sf::Vector2f(125, 20)); // Outline of the health bar
    outline.setPosition(x, y);
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(sf::Color::Black);
    outline.setOutlineThickness(2);

    sf::RectangleShape health(sf::Vector2f(hp, 20)); // Actual health bar (green)
    health.setPosition(x, y);
    health.setFillColor(sf::Color::Green);

    window.draw(outline);
    window.draw(health);
}

// Main battle loop for a single Pokémon-vs-Pokémon battle screen
void battleScreen(sf::RenderWindow& window, sf::Font& font, Pokemon* playerPokemon, Pokemon* cpuPokemon) {
    TypeEffectiveness typeChart;  // Damage multiplier chart
    bool playerTurn = true;       // Flag to track whose turn it is
    bool ultimateUsed = false;    // Track if player used ultimate
    bool battleOver = false;      // Track if battle is over
    std::string result = "";      // Result message (win/lose)

    // Text for player Pokémon's name
    sf::Text playerText(playerPokemon->getName(), font, 24);
    playerText.setPosition(50, 50);
    playerText.setFillColor(sf::Color::Black);

    // Text for CPU Pokémon's name
    sf::Text cpuText(cpuPokemon->getName(), font, 24);
    cpuText.setPosition(550, 50);
    cpuText.setFillColor(sf::Color::Black);

    // Attack button and label
    sf::RectangleShape attackButton(sf::Vector2f(150, 50));
    attackButton.setPosition(50, 400);
    attackButton.setFillColor(sf::Color(200, 200, 255));

    sf::Text attackText("Attack", font, 20);
    attackText.setPosition(80, 410);
    attackText.setFillColor(sf::Color::Black);

    // Ultimate button and label
    sf::RectangleShape ultimateButton(sf::Vector2f(150, 50));
    ultimateButton.setPosition(250, 400);
    ultimateButton.setFillColor(sf::Color(255, 200, 200));

    sf::Text ultimateText("Ultimate", font, 20);
    ultimateText.setPosition(270, 410);
    ultimateText.setFillColor(sf::Color::Black);

    // Text for end-of-battle result
    sf::Text endText("", font, 28);
    endText.setPosition(200, 250);
    endText.setFillColor(sf::Color::Red);

    // Main battle loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close the window
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            // Handle mouse clicks for player actions
            if (!battleOver && playerTurn && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // Player clicks attack button
                if (attackButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    int base = getRandomDamage(25, 40);
                    float multiplier = typeChart.getMultiplier(playerPokemon->getType(), cpuPokemon->getType());
                    cpuPokemon->takeDamage(base * multiplier); // Apply damage to CPU Pokémon
                    playerTurn = false; // End player's turn
                }

                // Player clicks ultimate button (if not used yet)
                if (!ultimateUsed && ultimateButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    int base = getRandomDamage(25, 40);
                    int ultimate = static_cast<int>(base * 2.0f); // Double damage for ultimate
                    float multiplier = typeChart.getMultiplier(playerPokemon->getType(), cpuPokemon->getType());
                    cpuPokemon->takeDamage(ultimate * multiplier); // Apply ultimate damage
                    ultimateUsed = true; // Mark ultimate as used
                    playerTurn = false; // End player's turn
                }
            }
        }

        // CPU's turn if player's turn is over and battle is not over
        if (!playerTurn && !battleOver) {
            int base = getRandomDamage(25, 40);
            float multiplier = typeChart.getMultiplier(cpuPokemon->getType(), playerPokemon->getType());
            playerPokemon->takeDamage(base * multiplier); // CPU attacks player
            playerTurn = true; // Return control to player
        }

        // Check if battle is over
        if (!cpuPokemon->isAlive() && !battleOver) {
            result = "You Win!";
            battleOver = true;
        } else if (!playerPokemon->isAlive() && !battleOver) {
            result = "You Lose!";
            battleOver = true;
        }

        // Update result text if battle is over
        endText.setString(result);

        // Render everything
        window.clear(sf::Color::White);
        window.draw(playerText);
        window.draw(cpuText);

        drawHealthBar(window, 50, 100, playerPokemon->getHP());
        drawHealthBar(window, 550, 100, cpuPokemon->getHP());

        // Draw buttons if battle ongoing
        if (!battleOver) {
            window.draw(attackButton);
            window.draw(attackText);
            if (!ultimateUsed) {
                window.draw(ultimateButton);
                window.draw(ultimateText);
            }
        } else { // Draw end text if battle over
            window.draw(endText);
        }

        window.display();
    }
}

#endif
