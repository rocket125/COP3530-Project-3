#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include "Maze.h"

using namespace std;

// Helper function to create text
sf::Text createText(const std::string& content, sf::Font& font, unsigned int size, float x, float y) {
    sf::Text text(content, font, size);
    text.setPosition(x, y);
    text.setFillColor(sf::Color::Black);
    return text;
}

void renderMaze(sf::RenderWindow& window, Maze maze, sf::Vector2f startPos) {
    auto mazeData = maze.getMaze();
    float tileSize = 20;
    // Scales down for size 49 maze
    if (mazeData.size() == 49 && mazeData[0].size() == 49) {
        tileSize = 12;
    }
    for (size_t y = 0; y < mazeData.size(); ++y) {
        for (size_t x = 0; x < mazeData[y].size(); ++x) {
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
            tile.setPosition(startPos.x + x * tileSize, startPos.y + y * tileSize);

            char tileChar = maze.getTile({x, y});
            switch (tileChar) {
                case '.': tile.setFillColor(sf::Color::White); break;
                case '#': tile.setFillColor(sf::Color::Black); break;
                case 's': tile.setFillColor(sf::Color::Green); break;
                case 't': tile.setFillColor(sf::Color::Red); break;
                default: tile.setFillColor(sf::Color::Transparent); break;
            }
            window.draw(tile);
        }
    }
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
        sf::RectangleShape mazeSizeMenuBackdrop(sf::Vector2f(150, 120));
        mazeSizeMenuBackdrop.setPosition(1030, 110);
        mazeSizeMenuBackdrop.setFillColor(sf::Color(173, 216, 230));
        mazeSizeMenuBackdrop.setOutlineColor(sf::Color::Black);
        mazeSizeMenuBackdrop.setOutlineThickness(1);

        // Maze size options text
        sf::Text mazeOption5 = createText("5x5", font, 18, 1040, 120);
        sf::Text mazeOption11 = createText("11x11", font, 18, 1040, 150);
        sf::Text mazeOption25 = createText("25x25", font, 18, 1040, 180);
        sf::Text mazeOption49 = createText("49x49", font, 18, 1040, 210);
        Maze maze;
        bool mazeLoaded = false;
        sf::Vector2f mazeStartPosition(50, 50);

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
                        if (mazeOption5.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            cout << "5x5 option clicked" << endl;  // Debugging line
                            Maze::loadMazeFromFile(maze, "resources/mazes/5x5.txt");
                            if (!maze.getMaze().empty()) {
                                mazeLoaded = true;
                                showMazeSizePrompt = false;
                                mazeSizePopup = false;
                                cout << "5x5 Maze loaded successfully" << endl;
                            } else {
                                cout << "Failed to load 5x5 Maze" << endl;
                            }
                        } else if (mazeOption11.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            cout << "11x11 option clicked" << endl;  // Debugging line
                            Maze::loadMazeFromFile(maze, "resources/mazes/11x11.txt");
                            if (!maze.getMaze().empty()) {
                                mazeLoaded = true;
                                showMazeSizePrompt = false;
                                mazeSizePopup = false;
                                cout << "11x11 Maze loaded successfully" << endl;
                            } else {
                                cout << "Failed to load 11x11 Maze" << endl;
                            }
                        } else if (mazeOption25.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            cout << "25x25 option clicked" << endl;  // Debugging line
                            Maze::loadMazeFromFile(maze, "resources/mazes/25x25.txt");
                            if (!maze.getMaze().empty()) {
                                mazeLoaded = true;
                                showMazeSizePrompt = false;
                                mazeSizePopup = false;
                                cout << "25x25 Maze loaded successfully" << endl;
                            } else {
                                cout << "Failed to load 25x25 Maze" << endl;
                            }
                        } else if (mazeOption49.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            cout << "49x49 option clicked" << endl;
                            Maze::loadMazeFromFile(maze, "resources/mazes/49x49.txt");
                            if (!maze.getMaze().empty()) {
                                mazeLoaded = true;
                                showMazeSizePrompt = false;
                                mazeSizePopup = false;
                                cout << "49x49 Maze loaded successfully" << endl;
                            } else {
                                cout << "Failed to load 49x49 Maze" << endl;
                            }
                        }
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
                            // This does not show any popups but closes the dropdown and possible maze
                            showExampleMenu = false;
                            showMazeSizePrompt = false;
                            mazeSizePopup = false;
                            mazeLoaded = false;
                            maze = Maze();
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
                        mazeLoaded = false;
                        maze = Maze();
                        cout << "Menu was reset" << endl;
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
                window.draw(mazeSizeMenuBackdrop);
                window.draw(mazeOption5);
                window.draw(mazeOption11);
                window.draw(mazeOption25);
                window.draw(mazeOption49);
            }

            if (mazeLoaded) {
                renderMaze(window, maze, mazeStartPosition);
            }


            window.display();
        }
    }else {
        // No GUI implementation here
    }

    return 0;
}
