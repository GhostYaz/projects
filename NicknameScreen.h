#ifndef NICKNAME_SCREEN_H
#define NICKNAME_SCREEN_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <map>

// Function to get nicknames for selected Pokémon
std::vector<std::string> getNicknames(sf::RenderWindow& window, sf::Font& font, const std::vector<std::string>& chosenTypes) {
    std::vector<std::string> nicknames(3, ""); // Initialize 3 empty nicknames

    // Load background image
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("assets/nickname_bg.png")) {
        std::cerr << "Failed to load nickname_bg.png" << std::endl;
    }
    sf::Sprite bgSprite(bgTexture);
    bgSprite.setScale(
        (float)window.getSize().x / bgTexture.getSize().x,
        (float)window.getSize().y / bgTexture.getSize().y
    );

    // Map Pokémon type names to their image files
    std::map<std::string, std::string> typeToFile = {
        {"Fire", "assets/fire.png"}, {"Water", "assets/water.png"}, {"Earth", "assets/earth.png"},
        {"Electric", "assets/electric.png"}, {"Air", "assets/air.png"}, {"Cyberpunk", "assets/cyberpunk.png"},
        {"Shadow", "assets/shadow.png"}, {"Magic", "assets/magic.png"}, {"Ice", "assets/ice.png"},
        {"Scorpion", "assets/scorpion.png"}, {"Tsunami", "assets/tsunami.png"}, {"Lava", "assets/lava.png"}
    };

    // Load and prepare Pokémon images (3 slots)
    std::vector<sf::Texture> textures(3);
    std::vector<sf::Sprite> sprites(3);

    for (int i = 0; i < 3; ++i) {
        if (!textures[i].loadFromFile(typeToFile[chosenTypes[i]])) {
            std::cerr << "Failed to load image for: " << chosenTypes[i] << std::endl;
        }
        sprites[i].setTexture(textures[i]);

        // Scale to 150x150 maximum size
        float maxDim = std::max(textures[i].getSize().x, textures[i].getSize().y);
        float scale = 150.0f / maxDim;
        sprites[i].setScale(scale, scale);
        sprites[i].setPosition(window.getSize().x / 2 + 100, 150); // Position on screen
    }

    // Iterate over the 3 selected Pokémon for nickname input
    for (int idx = 0; idx < 3; ++idx) {
        std::string nickname = "";

        // Prompt text
        sf::Text prompt("Give nickname to " + chosenTypes[idx] + ":", font, 26);
        prompt.setFillColor(sf::Color::White);
        prompt.setStyle(sf::Text::Bold);
        prompt.setPosition(100, 100);

        // Text box to show typed nickname
        sf::Text nameText("", font, 24);
        nameText.setFillColor(sf::Color::White);
        nameText.setStyle(sf::Text::Bold);
        nameText.setPosition(100, 150);

        // Continue button
        sf::RectangleShape continueButton(sf::Vector2f(200, 50));
        continueButton.setFillColor(sf::Color(100, 250, 100));
        continueButton.setPosition(100, 250);

        // Continue button text
        sf::Text continueText("Continue", font, 22);
        continueText.setFillColor(sf::Color::Black);
        sf::FloatRect textRect = continueText.getLocalBounds();
        continueText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        continueText.setPosition(100 + 100, 250 + 25); // Centered on button

        // Input loop for current Pokémon
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return {}; // User closed window → return empty
                }
                // Handle text input
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') { // Handle backspace
                        if (!nickname.empty())
                            nickname.pop_back();
                    } else if (event.text.unicode < 128 && isprint(event.text.unicode)) {
                        if (nickname.length() < 15) // Limit nickname length
                            nickname += static_cast<char>(event.text.unicode);
                    }
                }
                // Handle continue button click
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (continueButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        if (!nickname.empty()) { // Only accept if not empty
                            nicknames[idx] = nickname;
                            goto next; // Move to next Pokémon
                        }
                    }
                }
            }

            // Update nickname text
            nameText.setString(nickname);

            // Clear window and draw background
            window.clear(sf::Color::White);
            window.draw(bgSprite);

            // Draw prompt
            window.draw(prompt);

            // Draw a semi-transparent box behind the nickname
            sf::FloatRect nameBounds = nameText.getGlobalBounds();
            sf::RectangleShape nameBox(sf::Vector2f(nameBounds.width + 20, nameBounds.height + 20));
            nameBox.setPosition(nameText.getPosition().x - 10, nameText.getPosition().y - 10);
            nameBox.setFillColor(sf::Color(0, 0, 0, 150));
            window.draw(nameBox);
            window.draw(nameText);

            // Draw continue button and its text
            window.draw(continueButton);
            window.draw(continueText);

            // Draw Pokémon image with border
            sf::FloatRect spriteBounds = sprites[idx].getGlobalBounds();
            sf::RectangleShape border(sf::Vector2f(spriteBounds.width + 10, spriteBounds.height + 10));
            border.setPosition(sprites[idx].getPosition().x - 5, sprites[idx].getPosition().y - 5);
            border.setFillColor(sf::Color(255, 255, 255, 180));
            border.setOutlineThickness(3);
            border.setOutlineColor(sf::Color::Black);
            window.draw(border);
            window.draw(sprites[idx]);

            // Update display
            window.display();
        }
        return {}; // Window closed while inputting → return empty
    next:; // Label to skip to next Pokémon
    }

    return nicknames; // Return final nicknames after all 3 inputs
}

#endif
