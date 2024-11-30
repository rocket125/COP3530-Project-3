#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;

// Helper function to create text
sf::Text createText(const std::string& content, sf::Font& font, unsigned int size, float x, float y) {
    sf::Text text(content, font, size);
    text.setPosition(x, y);
    text.setFillColor(sf::Color::Black);
    return text;
}

int main(int argc, char* argv[]) {
    bool noGUI = false; // Check for "-nogui" argument
    for (unsigned int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-nogui")
            noGUI = true;
    }

    if (!noGUI) {
        sf::RenderWindow window({1280, 720}, "Project 3");
        window.setFramerateLimit(60);

        // Load the font, need to put file in repository
        // I have it I'll put it in soon
        sf::Font font;
        if (!font.loadFromFile("ARIAL.ttf")) {
            cout << "Failed to load font" << endl;
            // if load fails -> exit
            return -1;
        }

        // Creates example size button
        sf::RectangleShape button1(sf::Vector2f(200, 40));
        button1.setPosition(1020, 50);
        button1.setFillColor(sf::Color(200, 200, 200));
        sf::Text button1Text = createText("Example Size", font, 20, 1030, 55);

        // this creates the dropdown
        bool showExampleMenu = false;
        sf::Text smallExample = createText("Small Example", font, 18, 1040, 100);
        sf::Text largeExample = createText("Large Example", font, 18, 1040, 130);

        // Creates the algorithm button
        sf::RectangleShape button2(sf::Vector2f(200, 40));
        button2.setPosition(1020, 200);
        button2.setFillColor(sf::Color(200, 200, 200));
        sf::Text button2Text = createText("Algorithm Type", font, 20, 1030, 205);

        // this drops down the options for the second button
        bool showAlgorithmMenu = false; // Track if the dropdown is open
        sf::Text bfsOption = createText("BFS", font, 18, 1040, 250);
        sf::Text dfsOption = createText("DFS", font, 18, 1040, 280);

        // Timer display
        sf::Text timerLabel = createText("Timer:", font, 20, 1020, 350);
        sf::Text timerValue = createText("0.000s", font, 20, 1080, 350);

        // Start button
        sf::RectangleShape startButton(sf::Vector2f(200, 40));
        startButton.setPosition(1020, 450);
        startButton.setFillColor(sf::Color(150, 0, 0));

        sf::Text startButtonText = createText("Start", font, 20, 1080, 455);

        // Main window loop
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                // This is the mouse click event for the dropdown menus
                if (event.type == sf::Event::MouseButtonPressed) {
                    // Is it clicking the example button?
                    if (button1.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                        showExampleMenu = !showExampleMenu; // dropdown visibility
                    }
                    // Is it clicking the example button?
                    if (button2.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                        showAlgorithmMenu = !showAlgorithmMenu;
                    }

                    // Check if an option is selected from examples
                    if (showExampleMenu) {
                        if (smallExample.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            // small Example selected
                            cout << "Small Example selected" << endl;
                            showExampleMenu = false;
                        } else if (largeExample.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            // large Example selected
                            cout << "Large Example selected" << endl;
                            showExampleMenu = false;
                        }
                    }

                    // Check if an option is selected from algorithms
                    if (showAlgorithmMenu) {
                        if (bfsOption.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            // BFS selected
                            cout << "BFS selected" << endl;
                            showAlgorithmMenu = false;
                        } else if (dfsOption.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            // DFS selected
                            cout << "DFS selected" << endl;
                            showAlgorithmMenu = false;
                        }
                    }
                }
            }

            // Clear window
            window.clear(sf::Color::White);

            // draw all the buttons
            window.draw(button1);
            window.draw(button1Text);
            if (showExampleMenu) {
                window.draw(smallExample);
                window.draw(largeExample);
            }

            window.draw(button2);
            window.draw(button2Text);
            if (showAlgorithmMenu) {
                window.draw(bfsOption);
                window.draw(dfsOption);
            }

            window.draw(timerLabel);
            window.draw(timerValue);

            window.draw(startButton);
            window.draw(startButtonText);

            window.display();
        }
    } else {
        // No GUI implementation here
    }

    return 0;
}
