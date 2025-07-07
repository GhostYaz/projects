#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Create an 800x600 window titled "Enter Trainer Name"
    sf::RenderWindow window(sf::VideoMode(800, 600), "Enter Trainer Name");

    // Load font from file (make sure arial.ttf is in executable folder)
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return 1; // Exit if font fails to load
    }

    std::string trainerName; // Holds the inputted trainer name

    // Prompt text shown to user
    sf::Text prompt("Enter Your Trainer Name:", font, 30);
    prompt.setPosition(100, 100);
    prompt.setFillColor(sf::Color::Black);

    // Text object that displays current typed name
    sf::Text nameText("", font, 28);
    nameText.setPosition(100, 160);
    nameText.setFillColor(sf::Color::Blue);

    // Green rectangular Continue button
    sf::RectangleShape continueButton(sf::Vector2f(200, 50));
    continueButton.setPosition(100, 250);
    continueButton.setFillColor(sf::Color(100, 250, 100));

    // Text for Continue button
    sf::Text continueText("Continue", font, 24);
    continueText.setPosition(130, 260);
    continueText.setFillColor(sf::Color::Black);

    // Main event loop to keep window open and handle input
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close(); // Close window if requested

            // Handle text input events (typing and backspace)
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') { // Backspace pressed
                    if (!trainerName.empty())
                        trainerName.pop_back(); // Remove last character
                } else if (event.text.unicode < 128 && isprint(event.text.unicode)) {
                    if (trainerName.size() < 20) // Limit input length to 20 chars
                        trainerName += static_cast<char>(event.text.unicode); // Append character
                }
            }

            // Handle mouse click events
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    auto mouse = sf::Mouse::getPosition(window);
                    // Check if click was on Continue button
                    if (continueButton.getGlobalBounds().contains(mouse.x, mouse.y)) {
                        if (!trainerName.empty()) { // Only proceed if name entered
                            std::cout << "Trainer Name: " << trainerName << std::endl;
                            // TODO: Move to next screen here
                            window.close(); // Temporarily close window for demo
                        }
                    }
                }
            }
        }

        // Update the text displaying current trainer name
        nameText.setString(trainerName);

        // Clear window with white background
        window.clear(sf::Color::White);
        // Draw prompt and typed name
        window.draw(prompt);
        window.draw(nameText);

        // Show Continue button only if name is not empty
        if (!trainerName.empty()) {
            window.draw(continueButton);
            window.draw(continueText);
        }

        // Display all drawn elements on screen
        window.display();
    }

    return 0;
}
