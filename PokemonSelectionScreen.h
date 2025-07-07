#ifndef POKEMON_SELECTION_SCREEN_H
#define POKEMON_SELECTION_SCREEN_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Function to select 3 Pokémon types by clicking text buttons
std::vector<std::string> selectPokemons(sf::RenderWindow& window, sf::Font& font) {
    // Load background image for selection screen
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("assets/selection_bg.png")) {
        std::cerr << "Failed to load selection_bg.png" << std::endl;
    }
    sf::Sprite bgSprite(bgTexture);
    bgSprite.setScale(
        (float)window.getSize().x / bgTexture.getSize().x,
        (float)window.getSize().y / bgTexture.getSize().y
    );

    // Pokémon types (including Tsunami and Lava)
    std::vector<std::string> types = {
        "Fire", "Water", "Earth", "Electric", "Air",
        "Cyberpunk", "Shadow", "Magic", "Ice", "Scorpion",
        "Tsunami", "Lava"
    };

    // Create text objects for each type
    std::vector<sf::Text> typeTexts;
    for (size_t i = 0; i < types.size(); ++i) {
        sf::Text text(types[i], font, 28);  // Increased font size for clarity
        text.setFillColor(sf::Color(20, 20, 20));  // Dark gray text
        text.setStyle(sf::Text::Bold);  // Bold for visibility
        text.setPosition(100 + (i % 3) * 200, 100 + (i / 3) * 60);  // 3 columns layout
        typeTexts.push_back(text);
    }

    std::vector<std::string> chosen;  // Stores selected Pokémon types

    // Continue button setup
    sf::RectangleShape continueButton(sf::Vector2f(200, 50));
    continueButton.setFillColor(sf::Color(100, 250, 100)); // Green color
    continueButton.setPosition(window.getSize().x / 2 - 100, window.getSize().y - 80);

    sf::Text continueText("Continue", font, 24);
    continueText.setFillColor(sf::Color::Black);
    sf::FloatRect textRect = continueText.getLocalBounds();
    continueText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    continueText.setPosition(window.getSize().x / 2, window.getSize().y - 55);

    // Main input loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return {}; // Exit if window closed
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // Check if player clicked on a Pokémon type
                for (size_t i = 0; i < typeTexts.size(); ++i) {
                    if (typeTexts[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        // If already chosen, deselect it
                        auto it = std::find(chosen.begin(), chosen.end(), types[i]);
                        if (it != chosen.end()) {
                            chosen.erase(it);
                            typeTexts[i].setFillColor(sf::Color(20, 20, 20));  // Reset color
                        } else if (chosen.size() < 3) {
                            // If less than 3, add to chosen
                            chosen.push_back(types[i]);
                            typeTexts[i].setFillColor(sf::Color::Blue);  // Highlight selection
                        }
                    }
                }

                // Check if player clicked Continue button (only if 3 chosen)
                if (chosen.size() == 3 && continueButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.close();
                    return chosen; // Return chosen Pokémon types
                }
            }
        }

        // Rendering phase
        window.clear(sf::Color::White);

        // Draw background first
        window.draw(bgSprite);

        // Draw Pokémon type options with semi-transparent box behind text
        for (const auto& text : typeTexts) {
            sf::FloatRect textBounds = text.getGlobalBounds();
            sf::RectangleShape box(sf::Vector2f(textBounds.width + 12, textBounds.height + 12));
            box.setPosition(text.getPosition().x - 6, text.getPosition().y - 6);
            box.setFillColor(sf::Color(255, 255, 255, 200));  // White box with some transparency
            window.draw(box);
            window.draw(text);
        }

        // Draw Continue button if player has chosen 3 Pokémon
        if (chosen.size() == 3) {
            window.draw(continueButton);
            window.draw(continueText);
        }

        window.display(); // Update display
    }

    return {}; // Window closed unexpectedly → return empty
}

#endif
