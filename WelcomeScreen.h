#ifndef WELCOME_SCREEN_H
#define WELCOME_SCREEN_H

#include <SFML/Graphics.hpp>
#include <iostream>

// Function to show the welcome screen with a background and a Continue button
void showWelcomeScreen(sf::RenderWindow& window) {
    // Load background image texture
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("assets/welcome_bg.png")) {
        std::cout << "Failed to load welcome_bg.png" << std::endl;
        return; // Exit if background fails to load
    }
    sf::Sprite bgSprite(bgTexture);
    // Scale background to fit the window size
    bgSprite.setScale(
        (float)window.getSize().x / bgTexture.getSize().x,
        (float)window.getSize().y / bgTexture.getSize().y
    );

    // Load font for button text
    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cout << "Failed to load arial.ttf" << std::endl;
        return; // Exit if font fails to load
    }

    // Create Continue button as a green rectangle
    sf::RectangleShape continueButton(sf::Vector2f(200, 50));
    continueButton.setFillColor(sf::Color(100, 250, 100));
    continueButton.setPosition(window.getSize().x / 2 - 100, window.getSize().y - 80);

    // Text label for the Continue button
    sf::Text continueText("Continue", font, 24);
    continueText.setFillColor(sf::Color::Black);
    // Center the text within the button
    sf::FloatRect textRect = continueText.getLocalBounds();
    continueText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    continueText.setPosition(window.getSize().x / 2, window.getSize().y - 55);

    // Main loop to keep the window open until Continue is clicked or window closed
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close(); // Close window if user requests

            // Detect mouse click on Continue button
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (continueButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return;  // Exit welcome screen function on Continue click
                }
            }
        }

        window.clear();               // Clear the window for new frame
        window.draw(bgSprite);        // Draw the background image
        window.draw(continueButton);  // Draw the Continue button
        window.draw(continueText);    // Draw the button text
        window.display();             // Display everything on the screen
    }
}

#endif
