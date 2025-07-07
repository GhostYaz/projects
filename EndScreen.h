#ifndef END_SCREEN_H
#define END_SCREEN_H

#include <SFML/Graphics.hpp>
#include <string>

// Function to display the end screen of the game with result message and play again button
// Returns true if the player wants to play again, false otherwise
bool showEndScreen(sf::RenderWindow& window, const std::string& result, sf::Font& font) {
    // Create the final message based on the game result
    std::string finalMessage;
    if (result == "You Win!") {
        finalMessage = "CONGRATULATIONS! \n" + result + "\nYou are a Pokemon Master!";
    } else if (result == "You Lose!") {
        finalMessage = "BETTER LUCK NEXT TIME! \n" + result + "\nTrain harder and try again!";
    } else {
        finalMessage = result;  // For any other message
    }

    // Create SFML text object to display the result
    sf::Text resultText(finalMessage, font, 32);  // Slightly smaller font for multiline display
    resultText.setFillColor(sf::Color::White);  // White text
    resultText.setStyle(sf::Text::Bold);  // Bold text
    resultText.setOutlineThickness(2);  // Outline thickness
    resultText.setOutlineColor(sf::Color::Black);  // Black outline for better visibility

    // Center the result text within the window
    sf::FloatRect textRect = resultText.getLocalBounds();
    resultText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    resultText.setPosition(window.getSize().x / 2, window.getSize().y / 3);

    // Create "Play Again" button
    sf::RectangleShape playAgainButton(sf::Vector2f(200, 50));  // Size: 200x50
    playAgainButton.setPosition(window.getSize().x / 2 - 100, 300);  // Centered horizontally
    playAgainButton.setFillColor(sf::Color(100, 250, 100)); // Green button

    // "Play Again" button text
    sf::Text playAgainText("Play Again", font, 24);
    playAgainText.setFillColor(sf::Color::Black);  // Black text
    // Center the text inside the button
    sf::FloatRect buttonTextRect = playAgainText.getLocalBounds();
    playAgainText.setOrigin(buttonTextRect.left + buttonTextRect.width / 2.0f, buttonTextRect.top + buttonTextRect.height / 2.0f);
    playAgainText.setPosition(window.getSize().x / 2, 325);

    // Main display loop for end screen
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Handle window close event
            if (event.type == sf::Event::Closed) {
                window.close();
                return false; // Player closed the window
            }
            // Handle "Play Again" button click
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (playAgainButton.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y)) {
                    return true; // Player clicked "Play Again"
                }
            }
        }

        // Render the end screen
        window.clear(sf::Color::Black);  // Clear with black background
        window.draw(resultText);         // Draw the final result text
        window.draw(playAgainButton);    // Draw the green "Play Again" button
        window.draw(playAgainText);      // Draw the button label
        window.display();                // Display everything
    }
    return false;  // If window is closed, return false
}

#endif
