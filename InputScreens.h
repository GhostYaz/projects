#ifndef INPUT_SCREENS_H
#define INPUT_SCREENS_H

#include <SFML/Graphics.hpp>
#include <iostream>

// Function to display the trainer name input screen and capture user's input
// Returns the entered trainer name as a string
std::string getTrainerName(sf::RenderWindow& window) {
    // Load font
    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return "";
    }

    // Load background image
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("assets/trainer_bg.png")) {
        std::cerr << "Failed to load trainer_bg.png!" << std::endl;
        return "";
    }
    sf::Sprite bgSprite(bgTexture);
    bgSprite.setScale(
        (float)window.getSize().x / bgTexture.getSize().x,
        (float)window.getSize().y / bgTexture.getSize().y
    );

    std::string trainerName;  // Store the entered trainer name

    // Prompt text
    sf::Text prompt("Enter Your Trainer Name:", font, 30);
    prompt.setPosition(100, 100);
    prompt.setFillColor(sf::Color::Black);
    prompt.setStyle(sf::Text::Bold);  // Bold prompt text

    // Text showing the entered trainer name
    sf::Text nameText("", font, 28);
    nameText.setPosition(110, 165);  // Slightly offset inside the box
    nameText.setFillColor(sf::Color::Black);

    // White box behind the input text
    sf::RectangleShape nameBox(sf::Vector2f(300, 40));
    nameBox.setPosition(100, 160);
    nameBox.setFillColor(sf::Color::White);

    // Continue button
    sf::RectangleShape continueButton(sf::Vector2f(200, 50));
    continueButton.setPosition(100, 250);
    continueButton.setFillColor(sf::Color(100, 250, 100));  // Green

    // Continue button text
    sf::Text continueText("Continue", font, 24);
    continueText.setPosition(130, 260);
    continueText.setFillColor(sf::Color::Black);

    // Main event loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Handle window close event
            if (event.type == sf::Event::Closed) {
                window.close();
                return "";
            }

            // Debug message for window focus
            if (event.type == sf::Event::GainedFocus) {
                std::cout << "Window focused." << std::endl;
            }

            // Handle text input for trainer name
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {  // Backspace
                    if (!trainerName.empty())
                        trainerName.pop_back();
                } else if (event.text.unicode < 128 && isprint(event.text.unicode)) {  // Valid printable ASCII
                    if (trainerName.length() < 20)
                        trainerName += static_cast<char>(event.text.unicode);
                }
            }

            // Handle mouse click on "Continue" button
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (continueButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        if (!trainerName.empty()) {
                            window.close();  // Close window
                            return trainerName;  // Return entered name
                        }
                    }
                }
            }
        }

        // Update name text with current input
        nameText.setString(trainerName);

        // Render the input screen
        window.clear();
        window.draw(bgSprite);       // Background image
        window.draw(prompt);         // Prompt
        window.draw(nameBox);        // White input box
        window.draw(nameText);       // Current input text
        window.draw(continueButton); // Continue button
        window.draw(continueText);   // Continue text
        window.display();
    }

    return "";  // In case window is closed unexpectedly
}

#endif
