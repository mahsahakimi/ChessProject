#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window (sf::VideoMode(800, 500), "Chess", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize); // creat window
    sf::RectangleShape player1(sf::Vector2f(300.0f, 300.0f)); // create a shape
    player1.setOrigin(150.0f, 150.0f); // set the center of shape
    player1.setPosition(400.0f, 250.0f); // set the start of shepe

    sf::Texture playerTexture; // set photo
    playerTexture.loadFromFile("cute-cartoon-penguins.jpg");
    player1.setTexture(&playerTexture);

    sf::Vector2u textureSize = playerTexture.getSize(); // get size of photo
    textureSize.x /= 4; // cut the photo
    textureSize.y /= 3;

    player1.setTextureRect(sf::IntRect(textureSize.x * 3, textureSize.y * 1, textureSize.x, textureSize.y)); // set the peace of selected
    
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

        // window.clear(sf::Color(100, 150, 150)); // clear the buffer
        window.draw(player1);
        window.display(); // out pot the buffer
    }
    

    return 0;
}
