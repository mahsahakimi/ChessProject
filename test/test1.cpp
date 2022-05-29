#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window (sf::VideoMode(800, 500), "Chess", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize); // creat window
    sf::RectangleShape player1(sf::Vector2f(100.0f, 100.0f)); // create a shape
    player1.setFillColor(sf::Color::Blue); // color the shape
    player1.setOrigin(50.0f, 50.0f); // set the center of shape
    player1.setPosition(400.0f, 250.0f); // set the start of shepe

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
            
            case sf::Event::Resized:
                // std::cout << "New Window Height: " << evnt.size.height << "   New Window Width: " << evnt.size.width << std::endl;
                printf("New Window Height: %i  New Window Width: %i \n", evnt.size.height, evnt.size.width);
                break;

            case sf::Event::TextEntered: // print the chars which inputed of keyboard
                if (evnt.text.unicode < 128) // the char != ctrl, '\n', ...
                    printf("%c", evnt.text.unicode);
                break;

            default: 
                break;
            }
        }

        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) // move the shape by keyBoard
        //     player1.move(0.0f, -0.1f);
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        //     player1.move(0.0f, 0.1f);
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        //     player1.move(-0.1f, 0.0f);
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        //     player1.move(0.1f, 0.0f);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // move the shape by mouse
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            player1.setPosition((float)mousePos.x, (float)mousePos.y);
        }


        window.clear(); // clear the buffer
        window.draw(player1);
        window.display(); // out pot the buffer
    }
    

    return 0;
}
