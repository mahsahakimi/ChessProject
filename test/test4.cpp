#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>  




int main()
{
    int turn = 0;

    int window_height = 850 + 400 + 5, window_width = 850;
    float cell_size = 100.0f;

    sf::RenderWindow window (sf::VideoMode(window_height, window_width), "Basic Chess", sf::Style::Close | sf::Style::Titlebar); // creat window

    sf::RectangleShape back_ground (sf::Vector2f(845 + 600, 845)); // create a shape
    back_ground.setFillColor(sf::Color(0, 0, 128)); // color the shape
    back_ground.setOrigin(845 / 2 + 300, 845 / 2); // set the center of shape
    back_ground.setPosition(window_height / 2, window_width / 2); // set the start of shepe

    sf::RectangleShape cells[8][8];
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            sf::RectangleShape cell (sf::Vector2f(cell_size, cell_size)); // create a shape

            if (i % 2 == j % 2)
                cell.setFillColor(sf::Color(0, 0, 0)); // color the shape
            else
                cell.setFillColor(sf::Color(0, 0, 28)); // color the shape

            cell.setOrigin(cell_size / 2, cell_size / 2); // set the center of shape
            cell.setPosition((cell_size / 2) + (i*105) + 7.5f, (cell_size / 2) + (j*105) + 7.5f); // set the start of shepe
            cells[i][j] = cell;
        }

    int i1 = 7, j1 = 0;
    sf::RectangleShape rook(sf::Vector2f(90.0f, 90.0f)); // create a MOHRE
    rook.setOrigin(45.0f, 45.0f); // set the center of MOHRE
    rook.setPosition(7.5f + 50.0f + (105*j1), 7.5f + 50.0f + (105*i1)); // set the start of MOHRE
    sf::Texture rook_texture; // set photo
    rook_texture.loadFromFile("./images/rook.jpg");
    rook.setTexture(&rook_texture);
    rook.setFillColor(sf::Color::Green);

    i1 = 0, j1 = 1;
    sf::RectangleShape king(sf::Vector2f(90.0f, 90.0f)); // create a MOHRE
    king.setOrigin(45.0f, 45.0f); // set the center of MOHRE
    king.setPosition(7.5f + 50.0f + (105*j1), 7.5f + 50.0f + (105*i1)); // set the start of MOHRE
    sf::Texture king_texture; // set photo
    king_texture.loadFromFile("./images/king.jpg");
    king.setTexture(&king_texture);
    king.setFillColor(sf::Color::Blue);

    i1 = 5, j1 = 5;
    sf::RectangleShape pawn(sf::Vector2f(90.0f, 90.0f)); // create a MOHRE
    pawn.setOrigin(45.0f, 45.0f); // set the center of MOHRE
    pawn.setPosition(7.5f + 50.0f + (105*j1), 7.5f + 50.0f + (105*i1)); // set the start of MOHRE
    sf::Texture pawn_texture; // set photo
    pawn_texture.loadFromFile("./images/pawn.jpg");
    pawn.setTexture(&pawn_texture);
    pawn.setFillColor(sf::Color::Green);

    i1 = 3, j1 = 1;
    sf::RectangleShape bishop(sf::Vector2f(90.0f, 90.0f)); // create a MOHRE
    bishop.setOrigin(45.0f, 45.0f); // set the center of MOHRE
    bishop.setPosition(7.5f + 50.0f + (105*j1), 7.5f + 50.0f + (105*i1)); // set the start of MOHRE
    sf::Texture bishop_texture; // set photo
    bishop_texture.loadFromFile("./images/bishop.jpg");
    bishop.setTexture(&bishop_texture);
    bishop.setFillColor(sf::Color::Green);

    i1 = 4, j1 = 5;
    sf::RectangleShape queen(sf::Vector2f(90.0f, 90.0f)); // create a MOHRE
    queen.setOrigin(45.0f, 45.0f); // set the center of MOHRE
    queen.setPosition(7.5f + 50.0f + (105*j1), 7.5f + 50.0f + (105*i1)); // set the start of MOHRE
    sf::Texture queen_texture; // set photo
    queen_texture.loadFromFile("./images/queen.jpg");
    queen.setTexture(&queen_texture);
    queen.setFillColor(sf::Color:: Green);

    i1 = 4, j1 = 6;
    sf::RectangleShape knight(sf::Vector2f(90.0f, 90.0f)); // create a MOHRE
    knight.setOrigin(45.0f, 45.0f); // set the center of MOHRE
    knight.setPosition(7.5f + 50.0f + (105*j1), 7.5f + 50.0f + (105*i1)); // set the start of MOHRE
    sf::Texture knight_texture; // set photo
    knight_texture.loadFromFile("./images/knight.jpg");
    knight.setTexture(&knight_texture);
    knight.setFillColor(sf::Color:: Blue);

    i1 = 7, j1 = 7;
    sf::RectangleShape dot(sf::Vector2f(90.0f, 90.0f)); // create a MOHRE
    dot.setOrigin(45.0f, 45.0f); // set the center of MOHRE
    dot.setPosition(7.5f + 50.0f + (105*j1), 7.5f + 50.0f + (105*i1)); // set the start of MOHRE
    sf::Texture dot_texture; // set photo
    dot_texture.loadFromFile("./images/dot2.png");
    dot.setTexture(&dot_texture);
    dot.setFillColor(sf::Color:: Yellow);

    i1 = 7, j1 = 11;
    sf::RectangleShape clr(sf::Vector2f(90.0f, 90.0f)); // create a MOHRE
    clr.setOrigin(45.0f, 45.0f); // set the center of MOHRE
    clr.setPosition(7.5f + 50.0f + (105*j1), 7.5f + 50.0f + (105*i1)); // set the start of MOHRE
    sf::Texture clr_texture; // set photo
    clr_texture.loadFromFile("./images/return.png");
    clr.setTexture(&clr_texture);
    // clr.setFillColor(sf::Color::Yellow);



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

            case sf::Event::TextEntered: // print the chars which inputed of keyboard
                if (evnt.text.unicode < 128) // the char != ctrl, '\n', ...
                    printf("%c", evnt.text.unicode);
                if (evnt.text.unicode == 's')
                    turn++;
                break;

            default: 
                break;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // move the shape by mouse
        {
            // x = column, y = row
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            int x = mousePos.x, y = mousePos.y;
            x = (x - 7.5) / (cell_size + 5), y = (y - 7.5) / (cell_size + 5);

            if (turn % 2 == 0)
                rook.setPosition((float)(7.5f + 50.0f + (105*x)), (float)(7.5f + 50.0f + (105*y)));
            else
                king.setPosition((float)(7.5f + 50.0f + (105*x)), (float)(7.5f + 50.0f + (105*y)));                

            // printf("x: %i,  y: %i,  turn: %i\n", x, y, turn);
            
        }

        window.clear(sf::Color(0, 0, 0)); // clear the buffer
        window.draw(back_ground);
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                window.draw(cells[i][j]);
        
        window.draw(rook);
        window.draw(king);
        window.draw(bishop);
        window.draw(pawn);
        window.draw(queen);
        window.draw(knight);
        window.draw(dot);
        window.draw(clr);
        window.display(); // out pot the buffer
    }
    

    return 0;
}
