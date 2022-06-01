#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>


sf::Text printText(std::string massege, sf::Font font, sf::Text status_text)
{
    font.loadFromFile("../Resources/Fonts/PinaColadaCreation.ttf");

    status_text.setFont(font);

    const int size = 30;
    status_text.setCharacterSize(size);
    status_text.setStyle(sf::Text::Bold);
    status_text.setFillColor(sf::Color::Black);
    status_text.setPosition(400.f, 80.f);
    status_text.setString(massege);
    return status_text;
}

int main()
{
    sf::RenderWindow window (sf::VideoMode(800, 500), "Chess", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize); // creat window
    sf::Font font;
    sf::Text status_text;

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
            }
        }

        window.clear(sf::Color(100, 150, 150)); // clear the buffer
        window.draw(printText("Arezoo", font, status_text));
        window.display(); // out pot the buffer
    }
    

    return 0;
}
