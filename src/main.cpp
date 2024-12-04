#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <sstream>

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

        // Load the font, file in resources
        sf::Font font;
        if (!font.loadFromFile("resources/ARIAL.ttf")) {
            cout << "Failed to load font" << endl;
            return -1;
        }

        // Creates example size button
        sf::RectangleShape button1(sf::Vector2f(200, 40));
        button1.setPosition(1020, 50);
        button1.setFillColor(sf::Color(200, 200, 200));
        sf::Text button1Text = createText("Example Size", font, 20, 1030, 55);

        // this creates the dropdown
        bool showExampleMenu = false;
        sf::Text smallExample = createText("Small Example", font, 18, 1040, 120);
        sf::Text largeExample = createText("Large Example", font, 18, 1040, 150);
        sf::Text selectedExample = createText("None", font, 18, 1030, 90);

        // Maze input size popup, bool is true if small example is clicked
        bool showMazeSizePrompt = false;
        sf::Text mazeSizeText = createText("Maze Size (max 50):", font, 18, 1030, 200);
        sf::Text mazeSizeInput = createText("", font, 18, 1030, 230);
        // this STORES the MAZE SIZE and also checks if it is >= limit
        int mazeSize = 0;
        bool inputValid = true;

        // Creates the algorithm button
        sf::RectangleShape button2(sf::Vector2f(200, 40));
        button2.setPosition(1020, 200);
        button2.setFillColor(sf::Color(200, 200, 200));
        sf::Text button2Text = createText("Algorithm Type", font, 20, 1030, 205);

        // this drops down the options for the second button
        bool showAlgorithmMenu = false;
        sf::Text bfsOption = createText("BFS", font, 18, 1040, 270);
        sf::Text dfsOption = createText("DFS", font, 18, 1040, 310);
        sf::Text selectedAlgorithm = createText("None", font, 18, 1030, 240);

        // Timer display
        sf::Text timerLabel = createText("Timer:", font, 20, 1020, 350);
        sf::Text timerValue = createText("0.000s", font, 20, 1080, 350);

        // Start button
        sf::RectangleShape startButton(sf::Vector2f(200, 40));
        startButton.setPosition(1020, 450);
        startButton.setFillColor(sf::Color(0, 255, 0));
        sf::Text startButtonText = createText("Start", font, 20, 1080, 455);

        // Reset button
        sf::RectangleShape resetButton(sf::Vector2f(200, 40));
        resetButton.setPosition(1020, 500);
        resetButton.setFillColor(sf::Color(255, 0, 0));
        sf::Text resetButtonText = createText("Reset", font, 20, 1080, 505);

        // The box that contains the maze size prompt
        sf::RectangleShape mazeSizeBox(sf::Vector2f(250, 100));
        mazeSizeBox.setPosition(1020, 170);
        mazeSizeBox.setFillColor(sf::Color(173, 216, 230));
        mazeSizeBox.setOutlineColor(sf::Color::Black);
        mazeSizeBox.setOutlineThickness(1);

        // This tracks if the menu is active, this helps with being able to use buttons
        bool menuActive = true;
        // Tracks the popup, if true you can't use other buttons
        bool mazeSizePopup = false;
        // Main loop
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                // This is the mouse click event for the dropdown menus
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (mazeSizePopup) {
                        // disables button use
                        continue;
                    }

                    // Is it clicking the example button?
                    if (button1.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                        // Dropdown options visibility
                        if (!mazeSizePopup && menuActive) {
                            showExampleMenu = !showExampleMenu;
                        }
                    }
                    // Is it clicking the algorithm button?
                    if (button2.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                        if (!mazeSizePopup && menuActive) {
                            showAlgorithmMenu = !showAlgorithmMenu;
                        }
                    }

                    // Check if an option is selected from examples
                    if (showExampleMenu) {
                        if (smallExample.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            selectedExample.setString("Small Example");
                            // Closes dropdown and shows prompts when Small Example is chosen
                            showExampleMenu = false;
                            showMazeSizePrompt = true;
                            mazeSizePopup = true;
                            cout << "Small Example selected" << endl;
                        } else if (largeExample.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            selectedExample.setString("Large Example");
                            // This does not show any popups but closes the dropdown
                            showExampleMenu = false;
                            showMazeSizePrompt = false;
                            mazeSizePopup = false;
                            cout << "Large Example selected" << endl;
                        }
                    }

                    // Check if an option is selected from algorithms
                    if (showAlgorithmMenu) {
                        if (bfsOption.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            // Same logic of selecting an option and then closing dropdown
                            selectedAlgorithm.setString("BFS");
                            showAlgorithmMenu = false;
                            cout << "BFS selected" << endl;
                        } else if (dfsOption.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            selectedAlgorithm.setString("DFS");
                            showAlgorithmMenu = false;
                            cout << "DFS selected" << endl;
                        }
                    }

                    // Is the Start button clicked? If so you can't interact further, besides resetting
                    if (startButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                        if (menuActive && !mazeSizePopup && selectedExample.getString() != "None" && selectedAlgorithm.getString() != "None") {
                            cout << "Start button was clicked." << endl;
                            menuActive = false;
                        }
                    }

                    // Check if Reset button is clicked, if so reset inputs
                    if (resetButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                        selectedExample.setString("None");
                        selectedAlgorithm.setString("None");
                        showExampleMenu = false;
                        showAlgorithmMenu = false;
                        showMazeSizePrompt = false;
                        mazeSizePopup = false;
                        menuActive = true;
                        cout << "Menu was reset" << endl;
                    }
                }

                // This is for the size input and handles the text
                if (event.type == sf::Event::TextEntered) {
                    if (mazeSizePopup) {
                        if (event.text.unicode == 8) {
                            std::string currentText = mazeSizeInput.getString();
                            if (!currentText.empty()) {
                                currentText.pop_back();
                                mazeSizeInput.setString(currentText);
                            }
                        } else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                            std::string currentText = mazeSizeInput.getString();
                            currentText += static_cast<char>(event.text.unicode);
                            mazeSizeInput.setString(currentText);
                        }
                        stringstream ss(mazeSizeInput.getString());
                        ss >> mazeSize;
                        // this checks if the number entered was within the accepted maze range
                        if (mazeSize <= 50 && mazeSize > 0) {
                            inputValid = true;
                        } else {
                            inputValid = false;
                        }
                        // this is for the enter key
                        if (event.text.unicode == 13 && inputValid) {
                            showMazeSizePrompt = false;
                            mazeSizePopup = false;
                            cout << "Maze Size set to " << mazeSize << endl;
                        }
                    }
                }
            }

            // Clears the window
            window.clear(sf::Color::White);

            // draws all the buttons
            window.draw(button1);
            window.draw(button1Text);
            window.draw(selectedExample);
            if (showExampleMenu) {
                window.draw(smallExample);
                window.draw(largeExample);
            }

            window.draw(button2);
            window.draw(button2Text);
            window.draw(selectedAlgorithm);
            if (showAlgorithmMenu) {
                window.draw(bfsOption);
                window.draw(dfsOption);
            }

            window.draw(timerLabel);
            window.draw(timerValue);

            window.draw(startButton);
            window.draw(startButtonText);

            window.draw(resetButton);
            window.draw(resetButtonText);

            // if true, draw the maze size prompt
            if (showMazeSizePrompt) {
                window.draw(mazeSizeBox);
                window.draw(mazeSizeText);
                window.draw(mazeSizeInput);
                if (!inputValid) {
                    sf::Text errorText = createText("Maze Size must be <= 50", font, 18, 1030, 300);
                    errorText.setFillColor(sf::Color::Red);
                    window.draw(errorText);
                }
            }

            window.display();
        }
    }else {
        // No GUI implementation here
    }

    return 0;
}
