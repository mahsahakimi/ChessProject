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
    int f = 1;

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

        std::string str;
        str = sf::Clipboard::getString();

        if (str == "")
            str = "Nothing";

        
        if (f)
            for (int i = 0; i < 194; i++)
            {
                f = 0;
                std::cout << i <<  " = " << str[i]<< (str[i] == 'B' ? 1 : 70) << std::endl;
            }

        window.clear(sf::Color(100, 150, 150)); // clear the buffer
        window.draw(printText(str, font, status_text));
        window.display(); // out pot the buffer
    }
    

    return 0;
}

/*
BD
-- -- -- -- -- -- -- --
PB -- -- -- -- -- -- --
KB -- KW -- -- -- -- --
-- -- -- -- -- -- -- --
-- PB PB -- -- PW -- --
-- -- -- -- -- RW -- --
-- -- -- -- -- -- -- --
-- -- -- -- BW -- -- LK
*/