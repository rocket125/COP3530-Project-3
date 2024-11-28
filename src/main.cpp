#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    bool noGUI = false; // If "-nogui" is passed as an argument,
    for (unsigned int i = 1; i < argc; ++i)
        {
        string arg = argv[i];
        if (arg == "-nogui")
            noGUI = true;
    }

    if (!noGUI) // Everything SFML here.
    {
        auto window = sf::RenderWindow({1280, 720}, "Project 3");
        window.setFramerateLimit(60);

        while (window.isOpen())
        {
            for (auto event = sf::Event(); window.pollEvent(event);)
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }

            window.clear();
            window.display();
        }
    }
    else // No GUI implementation. Uses console to perform the same tasks.
    {

    }

    return 0;
}
