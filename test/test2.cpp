#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window (sf::VideoMode(800, 500), "Chess", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize); // creat window
    sf::RectangleShape player1(sf::Vector2f(200.0f, 200.0f)); // create a shape
    player1.setOrigin(100.0f, 100.0f); // set the center of shape
    player1.setPosition(400.0f, 250.0f); // set the start of shepe

    sf::Texture playerTexture; // set photo
    playerTexture.loadFromFile("pngwing.com.png");
    player1.setTexture(&playerTexture);
    
    while (window.isOpen())
    {
        sf::Event evnt; // create event

        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed: // if tap the botten X
                window.close();
                break;

            default: 
                break;
            }
        }

        window.clear(); // clear the buffer
        window.draw(player1);
        window.display(); // out pot the buffer
    }
    

    return 0;
}
