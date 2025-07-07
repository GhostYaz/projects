#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm> // for std::transform

// Custom screens and classes
#include "WelcomeScreen.h"
#include "InputScreens.h"
#include "PokemonSelectionScreen.h"
#include "NicknameScreen.h"
#include "GameManager.h"
#include "EndScreen.h"

// Pokémon types
#include "FireType.h"
#include "WaterType.h"
#include "EarthType.h"
#include "ElectricType.h"
#include "AirType.h"
#include "CyberpunkType.h"
#include "ShadowType.h"
#include "MagicType.h"
#include "IceType.h"
#include "ScorpionType.h"
#include "TsunamiWaterType.h"
#include "LavaType.h"

// Animate attack - simple animation by moving the attacking sprite left-right
void animateAttack(sf::Sprite &sprite, sf::RenderWindow &window, sf::Sprite &bgSprite, sf::Sprite &cpuSprite, sf::Sprite &playerSprite)
{
    sf::Vector2f originalPos = sprite.getPosition(); // Save original position
    for (int i = 0; i < 5; ++i)
    {
        sprite.move(5, 0); // Move sprite right
        window.clear();
        window.draw(bgSprite);
        window.draw(playerSprite);
        window.draw(cpuSprite);
        window.display();
        sf::sleep(sf::milliseconds(20)); // Short delay for smooth animation
    }
    for (int i = 0; i < 5; ++i)
    {
        sprite.move(-5, 0); // Move sprite back to original position
        window.clear();
        window.draw(bgSprite);
        window.draw(playerSprite);
        window.draw(cpuSprite);
        window.display();
        sf::sleep(sf::milliseconds(20));
    }
    sprite.setPosition(originalPos); // Reset to original position
}

// Flash sprite - simple effect to show sprite flash for hit
void flashSprite(sf::Sprite &sprite, sf::RenderWindow &window, sf::Sprite &bgSprite, sf::Sprite &cpuSprite, sf::Sprite &playerSprite)
{
    sf::Color originalColor = sprite.getColor(); // Save original color
    sprite.setColor(sf::Color::White);           // Flash white
    window.clear();
    window.draw(bgSprite);
    window.draw(playerSprite);
    window.draw(cpuSprite);
    window.display();
    sf::sleep(sf::milliseconds(50)); // Flash duration
    sprite.setColor(originalColor);  // Revert color
}

// Health bar - draw outer border and inner bar based on HP
void drawHealthBar(sf::RenderWindow &window, int x, int y, int hp)
{
    sf::RectangleShape outer(sf::Vector2f(100, 20));
    outer.setPosition(x, y);
    outer.setFillColor(sf::Color::White);
    outer.setOutlineThickness(2);
    outer.setOutlineColor(sf::Color::Black);

    sf::RectangleShape inner(sf::Vector2f((float)hp, 20));
    inner.setPosition(x, y);
    inner.setFillColor(hp < 30 ? sf::Color::Red : sf::Color::Green); // Change to red if low HP

    window.draw(outer); // Draw border
    window.draw(inner); // Draw inner HP bar
}

int main()
{
    // 🎵 Background music setup
    sf::Music bgMusic;
    if (!bgMusic.openFromFile("assets/bgm.flac"))
    {
        std::cerr << "Failed to load bgm.flac!" << std::endl;
    }
    else
    {
        bgMusic.setLoop(true); // Loop background music
        bgMusic.play();
    }

    // Show welcome screen
    sf::RenderWindow welcomeWindow(sf::VideoMode(800, 600), "Welcome");
    showWelcomeScreen(welcomeWindow);
    welcomeWindow.close();

    // Get player name
    sf::RenderWindow window(sf::VideoMode(800, 600), "Trainer Setup");
    std::string trainerName = getTrainerName(window);
    if (trainerName.empty())
        return 0; // Exit if player cancels

    // Pokémon selection screen
    sf::RenderWindow selectWindow(sf::VideoMode(800, 600), "Choose 3 Pokemon");
    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf"))
    {
        std::cerr << "Font load failed!" << std::endl;
        return 1;
    }
    std::vector<std::string> chosenTypes = selectPokemons(selectWindow, font);
    if (chosenTypes.empty())
        return 0; // Exit if player cancels

    // Nickname input screen
    sf::RenderWindow nicknameWindow(sf::VideoMode(800, 600), "Nickname Your Pokemon");
    std::vector<std::string> nicknames = getNicknames(nicknameWindow, font, chosenTypes);
    if (nicknames.empty())
        return 0; // Exit if player cancels

    // Create player's Pokémon team based on chosen types
    std::vector<Pokemon *> playerTeam;
    for (int i = 0; i < 3; ++i)
    {
        if (chosenTypes[i] == "Fire")
            playerTeam.push_back(new FireType(nicknames[i]));
        else if (chosenTypes[i] == "Water")
            playerTeam.push_back(new WaterType(nicknames[i]));
        else if (chosenTypes[i] == "Earth")
            playerTeam.push_back(new EarthType(nicknames[i]));
        else if (chosenTypes[i] == "Electric")
            playerTeam.push_back(new ElectricType(nicknames[i]));
        else if (chosenTypes[i] == "Air")
            playerTeam.push_back(new AirType(nicknames[i]));
        else if (chosenTypes[i] == "Cyberpunk")
            playerTeam.push_back(new CyberpunkType(nicknames[i]));
        else if (chosenTypes[i] == "Shadow")
            playerTeam.push_back(new ShadowType(nicknames[i]));
        else if (chosenTypes[i] == "Magic")
            playerTeam.push_back(new MagicType(nicknames[i]));
        else if (chosenTypes[i] == "Ice")
            playerTeam.push_back(new IceType(nicknames[i]));
        else if (chosenTypes[i] == "Scorpion")
            playerTeam.push_back(new ScorpionType(nicknames[i]));
        else if (chosenTypes[i] == "Tsunami")
            playerTeam.push_back(new TsunamiWaterType(nicknames[i]));
        else if (chosenTypes[i] == "Lava")
            playerTeam.push_back(new LavaType(nicknames[i]));
    }

    // Create CPU team
    std::vector<Pokemon *> cpuTeam = {
        new FireType("InfernoBot"),
        new WaterType("AquaBot"),
        new ElectricType("ZappyBot")};
    std::vector<std::string> cpuTypes = {"Fire", "Water", "Electric"};

    // Initialize GameManager with teams
    GameManager game(playerTeam, cpuTeam);

    // Load battle sprites (mapping type names to image files)
    std::map<std::string, std::string> typeToFile = {
        {"Fire", "assets/fire.png"}, {"Water", "assets/water.png"}, {"Earth", "assets/earth.png"}, {"Electric", "assets/electric.png"}, {"Air", "assets/air.png"}, {"Cyberpunk", "assets/cyberpunk.png"}, {"Shadow", "assets/shadow.png"}, {"Magic", "assets/magic.png"}, {"Ice", "assets/ice.png"}, {"Scorpion", "assets/scorpion.png"}, {"Tsunami", "assets/tsunami.png"}, {"Lava", "assets/lava.png"}};

    // Load battle background image
    sf::Texture bgTexture;
    bgTexture.loadFromFile("assets/battle_bg.png");
    sf::Sprite bgSprite(bgTexture);
    bgSprite.setScale(800.0f / bgTexture.getSize().x, 600.0f / bgTexture.getSize().y); // Scale to fit window
    bgSprite.setColor(sf::Color(255, 255, 255, 120));                                  // Slightly transparent background

    // Load initial player and CPU Pokémon images
    sf::Texture playerTexture, cpuTexture;
    playerTexture.loadFromFile(typeToFile[chosenTypes[0]]);
    cpuTexture.loadFromFile(typeToFile[cpuTypes[0]]);
    sf::Sprite playerSprite(playerTexture);
    sf::Sprite cpuSprite(cpuTexture);

    // Scale images to 150x150 for uniform size
    playerSprite.setScale(150.0f / playerSprite.getLocalBounds().width, 150.0f / playerSprite.getLocalBounds().height);
    cpuSprite.setScale(150.0f / cpuSprite.getLocalBounds().width, 150.0f / cpuSprite.getLocalBounds().height);

    // Battle log to store messages
    std::vector<std::string> battleLog;

    // Setup battle window and flags
    sf::RenderWindow battleWindow(sf::VideoMode(800, 600), "3v3 Pokemon Battle");
    bool playerTurn = true, playerUsedUltimate = false, battleOver = false;
    std::string result = "";
    int currentPlayerIndex = 0, currentCpuIndex = 0;

    while (battleWindow.isOpen())
    {
        // Get active Pokémon
        Pokemon *player = game.getPlayerPokemon();
        Pokemon *cpu = game.getCpuPokemon();

        // Position sprites at left/right side
        float pX = (800 / 4.0f) - (playerSprite.getGlobalBounds().width / 2.0f);
        float cX = (800 * 3 / 4.0f) - (cpuSprite.getGlobalBounds().width / 2.0f);
        float y = (600 / 2.0f) - (playerSprite.getGlobalBounds().height / 2.0f);
        playerSprite.setPosition(pX, y);
        cpuSprite.setPosition(cX, y);

        sf::Event event;
        while (battleWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                battleWindow.close();
                goto cleanup; // Skip to cleanup if window closed
            }

            // Player's turn: handle attack/ultimate button clicks
            if (!battleOver && playerTurn && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(battleWindow);
                sf::FloatRect attackBtn(50, 450, 150, 50);
                sf::FloatRect ultBtn(250, 450, 150, 50);

                battleLog.clear(); // Clear log for new turn

                if (attackBtn.contains(mousePos.x, mousePos.y))
                {
                    int oldCpuHP = cpu->getHP();
                    game.playerAttack(false); // Basic attack
                    animateAttack(playerSprite, battleWindow, bgSprite, cpuSprite, playerSprite);
                    flashSprite(cpuSprite, battleWindow, bgSprite, cpuSprite, playerSprite);
                    int dmgDealt = oldCpuHP - cpu->getHP();
                    battleLog.push_back(player->getName() + " dealt " + std::to_string(dmgDealt) + " damage!");
                    playerTurn = false;
                }
                if (!playerUsedUltimate && ultBtn.contains(mousePos.x, mousePos.y))
                {
                    int oldCpuHP = cpu->getHP();
                    game.playerAttack(true); // Ultimate attack
                    animateAttack(playerSprite, battleWindow, bgSprite, cpuSprite, playerSprite);
                    flashSprite(cpuSprite, battleWindow, bgSprite, cpuSprite, playerSprite);
                    int dmgDealt = oldCpuHP - cpu->getHP();
                    battleLog.push_back(player->getName() + " used Ultimate! Dealt " + std::to_string(dmgDealt) + " damage!");
                    playerUsedUltimate = true;
                    playerTurn = false;
                }
            }
        }

        // CPU's turn: decide to attack or use ultimate
        if (!playerTurn && !battleOver)
        {
            int oldHp = player->getHP();
            static bool cpuUsedUltimate = false; // CPU can use ultimate once
            if (!cpuUsedUltimate && rand() % 5 == 0)
            { // 1-in-5 chance to use ultimate
                cpu->useUltimate(*player);
                int dmg = oldHp - player->getHP();
                battleLog.push_back(cpu->getName() + " USED ULTIMATE! DEALT " + std::to_string(dmg) + " DAMAGE!");
                cpuUsedUltimate = true;
            }
            else
            {
                cpu->attack(*player); // Regular attack
                int dmg = oldHp - player->getHP();
                battleLog.push_back(cpu->getName() + " DEALT " + std::to_string(dmg) + " DAMAGE!");
            }

            animateAttack(cpuSprite, battleWindow, bgSprite, cpuSprite, playerSprite);
            flashSprite(playerSprite, battleWindow, bgSprite, cpuSprite, playerSprite);
            playerTurn = true;
        }

        // Check if CPU Pokémon fainted
        if (game.isCpuFainted())
        {
            game.nextCpu();
            currentCpuIndex++;
            if (!game.isBattleOver() && currentCpuIndex < cpuTypes.size())
            {
                cpuTexture.loadFromFile(typeToFile[cpuTypes[currentCpuIndex]]);
                cpuSprite.setTexture(cpuTexture);

                // Consistent scaling for next Pokémon
                sf::Vector2u texSize = cpuTexture.getSize();
                cpuSprite.setScale(150.0f / texSize.x, 150.0f / texSize.y);
            }
        }

        // Check if Player Pokémon fainted
        if (game.isPlayerFainted())
        {
            game.nextPlayer();
            playerUsedUltimate = false; // Reset ultimate usage for next Pokémon
            currentPlayerIndex++;
            if (!game.isBattleOver() && currentPlayerIndex < chosenTypes.size())
            {
                playerTexture.loadFromFile(typeToFile[chosenTypes[currentPlayerIndex]]);
                playerSprite.setTexture(playerTexture);

                // Consistent scaling for next Pokémon
                sf::Vector2u texSizeP = playerTexture.getSize();
                playerSprite.setScale(150.0f / texSizeP.x, 150.0f / texSizeP.y);
            }
        }

        // If battle over, show result and play again screen
        if (game.isBattleOver())
        {
            battleOver = true;
            result = game.getResult();
            battleWindow.close();

            sf::RenderWindow endWindow(sf::VideoMode(800, 600), "Battle Result");
            bool playAgain = showEndScreen(endWindow, result, font);
            if (playAgain)
            {
                main(); // Restart game
            }
            return 0; // Exit if player chooses not to play again
        }

        // Drawing phase: render everything
        battleWindow.clear();
        battleWindow.draw(bgSprite);
        battleWindow.draw(playerSprite);
        battleWindow.draw(cpuSprite);

        // Display Pokémon names with type and nickname
        sf::Text pName(chosenTypes[currentPlayerIndex] + " (" + player->getName() + ")", font, 28);
        pName.setPosition(50, 50);
        pName.setFillColor(sf::Color::White);
        pName.setStyle(sf::Text::Bold);
        pName.setOutlineThickness(2);
        pName.setOutlineColor(sf::Color::Black);
        battleWindow.draw(pName);

        sf::Text cName(cpuTypes[currentCpuIndex] + " (" + cpu->getName() + ")", font, 28);
        cName.setPosition(550, 50);
        cName.setFillColor(sf::Color::White);
        cName.setStyle(sf::Text::Bold);
        cName.setOutlineThickness(2);
        cName.setOutlineColor(sf::Color::Black);
        battleWindow.draw(cName);

        // Draw health bars and numeric HP values
        drawHealthBar(battleWindow, 50, 100, player->getHP());
        drawHealthBar(battleWindow, 550, 100, cpu->getHP());

        sf::Text pHPText(std::to_string(player->getHP()) + "/" + std::to_string(player->getMaxHP()), font, 16);
        pHPText.setPosition(50, 80);
        pHPText.setFillColor(sf::Color::White);
        pHPText.setStyle(sf::Text::Bold);
        battleWindow.draw(pHPText);

        sf::Text cHPText(std::to_string(cpu->getHP()) + "/" + std::to_string(cpu->getMaxHP()), font, 16);
        cHPText.setPosition(550, 80);
        cHPText.setFillColor(sf::Color::White);
        cHPText.setStyle(sf::Text::Bold);
        battleWindow.draw(cHPText);

        // Draw attack button
        sf::RectangleShape attack(sf::Vector2f(150, 50));
        attack.setPosition(50, 450);
        attack.setFillColor(sf::Color(200, 200, 255));
        battleWindow.draw(attack);
        sf::Text aText("Attack", font, 20);
        aText.setPosition(80, 460);
        aText.setFillColor(sf::Color::Black);
        battleWindow.draw(aText);

        // Draw ultimate button (if not used)
        if (!playerUsedUltimate)
        {
            sf::RectangleShape ult(sf::Vector2f(150, 50));
            ult.setPosition(250, 450);
            ult.setFillColor(sf::Color(255, 200, 200));
            battleWindow.draw(ult);
            sf::Text uText("Ultimate", font, 20);
            uText.setPosition(270, 460);
            uText.setFillColor(sf::Color::Black);
            battleWindow.draw(uText);
        }

        // Draw score text at top center
        std::string scoreStr = "Your Pokemon: " + std::to_string(currentPlayerIndex) + "/3 fainted, CPU Pokemon: " + std::to_string(currentCpuIndex) + "/3 fainted";
        sf::Text scoreText(scoreStr, font, 18);
        sf::FloatRect scoreBounds = scoreText.getLocalBounds();
        scoreText.setPosition((800 - scoreBounds.width) / 2.0f, 20);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setStyle(sf::Text::Bold);
        battleWindow.draw(scoreText);

        // Draw battle log messages at bottom center
        float logY = 600 - 20 * battleLog.size() - 10;
        int lineHeight = 20;
        for (const auto &log : battleLog)
        {
            sf::Text logText(log, font, 18);
            sf::FloatRect logBounds = logText.getLocalBounds();
            logText.setPosition((800 - logBounds.width) / 2.0f, logY);
            logText.setFillColor(sf::Color::White);
            logText.setStyle(sf::Text::Bold);
            battleWindow.draw(logText);
            logY += lineHeight;
        }

        battleWindow.display(); // Update window
    }

// Cleanup: free memory for Pokémon
cleanup:
    for (auto p : playerTeam)
        delete p;
    for (auto c : cpuTeam)
        delete c;
    return 0;
}
