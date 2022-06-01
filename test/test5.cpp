#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

int existMohre[8][8]; // is exist Mohre 1: White -1: Black
int dangerForWhite[8][8]; // is exist danger for white Mohre 1: Yes
int dangerForBlack[8][8]; // is exist danger for Black Mohre 1: Yes

bool kish(int color_king, int i, int j)
{
    bool f;
    if (color_king == 1) // White king
        if (dangerForWhite[i][j] == 1)
            f = true;
        else
            f = false;
    else if (color_king == -1) // Black king
        if (dangerForBlack[i][j] == 1)
            f = true;
        else
            f = false;
    return f;
};

class Point // the Point
{
private:
    int mem_x; // x -> column
    int mem_y; // y -> row

public:
    const int column() // return x/ column
    {
        return mem_x;
    };

    const int row() // return y/ row
    {
        return mem_y;
    };

    Point(int y = 0, int x = 0) // y, x init current address "Norm"
    {
        // if (!(0 <= x && x < 8))
        //     cout << "\nx = " << x << " is invalid!\n";
        // if (!(0 <= y && y < 8))
        //     cout << "\ny = " << y << " is invalid!\n";
        this -> mem_x = x;
        this -> mem_y = y;
    };

    Point(const Point& other) // copy constructor
        : mem_x(other.mem_x), mem_y(other.mem_y) 
    {} 

    const Point operator=(const Point& other) // = overloading
    {
        this -> mem_x = other.mem_x;
        this -> mem_y = other.mem_y;
        return *this;
    };

    bool operator==(const Point& other) // == overloading
    {
        return (mem_x == other.mem_x && mem_y == other.mem_y);
    };

    bool operator!=(const Point& other) // != overloading
    {
        return !(*this == other);
    };

    friend ostream& operator<< (ostream& stream, const Point& point);
};

ostream& operator<< (ostream& stream, const Point& point)
{
    stream << "(" << point.mem_y << ", " << point.mem_x << ")";
    // stream << char(point.mem_x + int('a')) << 8 - point.mem_y;
    return stream;
};

class Mohre
{
private:
    Point currentAddress; // current address: (row, column)

public:
    sf::RectangleShape* graph_mohre;
    sf::Texture* mem_mohre_texture;

    char type; // type of Mohre
    char color; // color of Mohre
    bool isInit; // if Mohre initialized is true; else false.

    int singleMoves[8][8]; // single moves
    void(*funcSingleMoves)(int singleMoves[8][8], Point currentAddress); // the func for update single moves

    int imageAttacks[8][8]; // noghat morede tahdid
    void(*funcImageAttacks)(int imageAttacks[8][8], Point currentAddress); // the func for update image attacks
    
    Mohre(int y_formal = 0, int x_formal = 0, char type_formal = '-', char color_formal = '-', string pic_add = "-") // init current address
    {
        for (int i = 0; i < 8; i++) // set deafult singleMoves and imageAttacks
            for (int j = 0; j < 8; j++)
            {
                singleMoves[i][j] = 0;
                imageAttacks[i][j] = 0;
            }

        Point currentAddress_formal(y_formal, x_formal);
        this -> currentAddress = currentAddress_formal;
        if (type_formal != '-')
            ::existMohre[y_formal][x_formal] = (color_formal == 'W' ? 1 : -1); // 1: White -1: Black

        this -> type = type_formal;
        this -> color = color_formal;

        if (type_formal == '-' || color_formal == '-')
            isInit = false;
        else
            isInit = true;

        if (isInit)
        {
            int i1 = y_formal, j1 = x_formal;

            graph_mohre = new  sf::RectangleShape(sf::Vector2f(90.0f, 90.0f)); // create a MOHRE
            graph_mohre -> setOrigin(45.0f, 45.0f); // set the center of MOHRE
            graph_mohre -> setPosition(7.5f + 50.0f + (105*j1), 7.5f + 50.0f + (105*i1)); // set the start of MOHRE
            graph_mohre -> setFillColor((color_formal == 'W' ? sf::Color::Green : sf::Color::Blue));

            mem_mohre_texture = new sf::Texture;
            mem_mohre_texture -> loadFromFile(pic_add);
        }
    };

    Point getCurrentAddress() // get Current Address
    {
        return currentAddress;
    };

    bool getIsInit() // return isInit.
    {
        return isInit;
    };

    int row()
    {
        return currentAddress.row();
    };

    int column() // return x of current address
    {
        return currentAddress.column();
    };

    void setSingleMove(void(*func)(int singleMoves[8][8], Point currentAddress)) // set single moves and it's func
    {
        (*func)(singleMoves, currentAddress);
        this -> funcSingleMoves = func;
    };

    void setImageAttacks(void(*func)(int imageAttacks[8][8], Point currentAddress)) // set image attacks and it's func
    {
        (*func)(imageAttacks, currentAddress);
        this -> funcImageAttacks = func;
    };

    void update()
    {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
            {
                this -> singleMoves[i][j] = 0;
                this -> imageAttacks[i][j] = 0;
            };
        funcSingleMoves(singleMoves, currentAddress); // Update singleMoves
        funcImageAttacks(imageAttacks, currentAddress); // Update imageAttacks
    };

    char getColor()
    {
        return this -> color;
    };

    char getType()
    {
        return this -> type;
    };

    void doMove(Point newAddress)
    {
        ::existMohre[currentAddress.row()][currentAddress.column()] = 0; // Update existMohre

        if (::existMohre[newAddress.row()][newAddress.column()] != 0);
            // it means attack!

        ::existMohre[newAddress.row()][newAddress.column()] = (this -> color == 'W' ? 1 : (this -> color == 'B' ? -1 : 0));

        currentAddress = newAddress; // Update currentAddress
        (*graph_mohre).setPosition((float)(7.5f + 50.0f + (105*newAddress.column())), (float)(7.5f + 50.0f + (105*newAddress.row())));
        update();
    };

    virtual void details()
    {
        update();
        cout << "\n* * * * * * * * * * * * * * * * * * * \n";
        cout << "\nThe " << type << color << " is in " << currentAddress << '\n';
        cout << "The status of it's initialized = " << isInit << '\n';
        cout << "\nThe status of it's single moves: \n\n";
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
                cout << setw(2) << singleMoves[i][j] << ' ';
            cout << '\n';
        };
 
        cout << "\nThe status of it's image attacks: \n\n";
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
                cout << setw(2) << imageAttacks[i][j] << ' ';
            cout << '\n';
        };
        cout << "\nThe status of ChessBoard: \n\n";
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
                cout << setw(2) << ::existMohre[i][j] << ' ';
            cout << '\n';
        };
        cout << "Notice: 1: White -1: Black\n";
    };

    Point** getSingleMoves()
    {
        update();

        if (this -> type == 'K')
        {
            for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                {
                    if ((this -> color == 'W' ? ::dangerForWhite : ::dangerForBlack)[i][j] == 1)
                        this -> singleMoves[i][j] = 0;
                };
        };

        Point** pointPtr = new Point*[64];
        int counter = 0;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (singleMoves[i][j] == 1)
                {
                        Point* p = new Point(i, j);
                        while (p == 0)
                            Point* p = new Point(i, j);
                        pointPtr[counter] = p;
                        counter++;
                };

        pointPtr[counter] = 0;
        counter++;
        return pointPtr;
    };

    void show(sf::RenderWindow& window)
    {
        (*graph_mohre).setTexture(&(*mem_mohre_texture));
        window.draw((*graph_mohre));
    };
};

class Pawn : public Mohre // Sarbaz
{
public:
    static void pawnSingleMove(int singleMoves[8][8], Point currentAddress)
    {
        const int i_now = currentAddress.row();
        const int j_now = currentAddress.column();
        int it_color = ::existMohre[i_now][j_now]; // 1: White -1: Black
        int direction = -it_color; // -1: White 1: Black

        if (0 <= i_now + direction && i_now + direction < 8) // 1 U/D
            if (::existMohre[i_now + direction][j_now] == 0)
                singleMoves[i_now + direction][j_now] = 1;

        if ((it_color == 1 && i_now == 6)||(it_color == -1 && i_now == 1)) // 2 U/D
            if (0 <= i_now + 2*direction && i_now + 2*direction < 8)
                if (::existMohre[i_now + 2*direction][j_now] == 0 && ::existMohre[i_now + direction][j_now] == 0)
                    singleMoves[i_now + 2*direction][j_now] = 1;

        if (j_now + 1 < 8 && 0 <= i_now + direction && i_now + direction < 8) // W: UR, B: DR
            if (::existMohre[i_now + direction][j_now + 1] == -it_color)
                singleMoves[i_now + direction][j_now + 1] = 1;

        if (j_now - 1 < 8 && 0 <= i_now + direction && i_now + direction < 8) // W: UL, B: DL
            if (::existMohre[i_now + direction][j_now - 1] == -it_color)
                singleMoves[i_now + direction][j_now - 1] = 1;
    };

    static void pawnImageAttacks(int imageAttacks[8][8], Point currentAddress)
    {            
        const int i_now = currentAddress.row();
        const int j_now = currentAddress.column();
        int it_color = ::existMohre[i_now][j_now]; // 1: White -1: Black
        int direction = -it_color; // -1: White 1: Black
        if (j_now + 1 < 8 && 0 <= i_now + direction && i_now + direction < 8) // W: UR, B: DR
            imageAttacks[i_now + direction][j_now + 1] = 1;

        if (0 <= j_now - 1 && 0 <= i_now + direction && i_now + direction < 8) // W: UL, B: DL
            imageAttacks[i_now + direction][j_now - 1] = 1;
    };

    Pawn(int y, int x, char color_formal)
        : Mohre(y, x, 'P', color_formal, "./images/pawn.jpg") // set current address
    {
        Mohre::setSingleMove(pawnSingleMove);
        Mohre::setImageAttacks(pawnImageAttacks);
    };
};

class Knight : public Mohre // Asb
{
public:
    static void knightSingleMove(int singleMoves[8][8], Point currentAddress)
    {
        const int i_now = currentAddress.row();
        const int j_now = currentAddress.column();
        int it_color = ::existMohre[i_now][j_now]; // 1: White -1: Black

        if  (i_now + 2 < 8)
        {
            if (j_now + 1 < 8 && ::existMohre[i_now + 2][j_now + 1] != it_color)
                singleMoves[i_now + 2][j_now + 1] = 1; // U U R
            if (0 <= j_now - 1 && ::existMohre[i_now + 2][j_now - 1] != it_color)
                singleMoves[i_now + 2][j_now - 1] = 1; // U U D
        };

        if  (0 <= i_now - 2)
        {
            if (j_now + 1 < 8 && ::existMohre[i_now - 2][j_now + 1] != it_color)
                singleMoves[i_now - 2][j_now + 1] = 1; // D D R
            if (0 <= j_now - 1 && ::existMohre[i_now - 2][j_now - 1] != it_color)
                singleMoves[i_now - 2][j_now - 1] = 1; // D D L
        };

        if (j_now + 2 < 8)
        {
            if (i_now + 1 < 8 && ::existMohre[i_now + 1][j_now + 2] != it_color)
                singleMoves[i_now + 1][j_now + 2] = 1; // R R U
            if (0 <= i_now - 1 && ::existMohre[i_now - 1][j_now + 2] != it_color)
                singleMoves[i_now - 1][j_now + 2] = 1; // R R D
        };

        if (0 <= j_now - 2)
        {
            if (i_now + 1 < 8 && ::existMohre[i_now + 1][j_now - 2] != it_color)
                singleMoves[i_now + 1][j_now - 2] = 1; // L L U
            if (0 <= i_now - 1 && ::existMohre[i_now - 1][j_now - 2] != it_color)
                singleMoves[i_now - 1][j_now - 2] = 1; // L L D
        };
    };

    static void knightImageAttacks(int imageAttacks[8][8], Point currentAddress)
    {
        const int i_now = currentAddress.row();
        const int j_now = currentAddress.column();
        int it_color = ::existMohre[i_now][j_now]; // 1: White -1: Black

        if  (i_now + 2 < 8)
        {
            if (j_now + 1 < 8)
                imageAttacks[i_now + 2][j_now + 1] = 1; // U U R
            if (0 <= j_now - 1)
                imageAttacks[i_now + 2][j_now - 1] = 1; // U U D
        };

        if  (0 <= i_now - 2)
        {
            if (j_now + 1 < 8)
                imageAttacks[i_now - 2][j_now + 1] = 1; // D D R
            if (0 <= j_now - 1)
                imageAttacks[i_now - 2][j_now - 1] = 1; // D D L
        };

        if (j_now + 2 < 8)
        {
            if (i_now + 1 < 8)
                imageAttacks[i_now + 1][j_now + 2] = 1; // R R U
            if (0 <= i_now - 1)
                imageAttacks[i_now - 1][j_now + 2] = 1; // R R D
        };

        if (0 <= j_now - 2)
        {
            if (i_now + 1 < 8)
                imageAttacks[i_now + 1][j_now - 2] = 1; // L L U
            if (0 <= i_now - 1)
                imageAttacks[i_now - 1][j_now - 2] = 1; // L L D
        };
    };

    Knight(int y, int x, char color_formal)
        : Mohre(y, x, 'N', color_formal, "./images/knight.jpg") // set current address
    {
        Mohre::setSingleMove(knightSingleMove);
        Mohre::setImageAttacks(knightImageAttacks);
    };
};

class Queen : public Mohre // Vazir
{
public:
    static void queenSingleMove(int singleMoves[8][8], Point currentAddress)
    {
        const int i_now = currentAddress.row();
        const int j_now = currentAddress.column();
        int it_color = ::existMohre[i_now][j_now]; // 1: White -1: Black

        for (int i = i_now - 1; 0 <= i; i--) // Down
        {
            if (::existMohre[i][j_now] == it_color)
                break;
            singleMoves[i][j_now] = 1;
            if (::existMohre[i][j_now] == -it_color)
                break;
        };
        for (int i = i_now + 1; i < 8; i++) // Up
        {
            if (::existMohre[i][j_now] == it_color)
                break;
            singleMoves[i][j_now] = 1;
            if (::existMohre[i][j_now] == -it_color)
                break;
        };
        for (int j = j_now + 1; j < 8; j++) // Right
        {
            if (::existMohre[i_now][j] == it_color)
                break;
            singleMoves[i_now][j] = 1;
            if (::existMohre[i_now][j] == -it_color)
                break;
        };
        for (int j = j_now - 1; 0 <= j; j--) // Left
        {
            if (::existMohre[i_now][j] == it_color)
                break;
            singleMoves[i_now][j] = 1;
            if (::existMohre[i_now][j] == -it_color)
                break;
        };
        for (int i = i_now + 1, j = j_now + 1; i < 8 && j < 8; i++, j++) // Right & Up
        {
            if (::existMohre[i][j] == it_color)
                break;
            singleMoves[i][j] = 1;
            if (::existMohre[i][j] == -it_color)
                break;
        };
        for (int i = i_now - 1, j = j_now + 1; 0 <= i && j < 8; i--, j++) // Right & Down
        {
            if (::existMohre[i][j] == it_color)
                break;
            singleMoves[i][j] = 1;
            if (::existMohre[i][j] == -it_color)
                break;
        };
        for (int i = i_now - 1, j = j_now - 1; 0 <= i && 0 <= j; i--, j--) // Left & Down
        {
            if (::existMohre[i][j] == it_color)
                break;
            singleMoves[i][j] = 1;
            if (::existMohre[i][j] == -it_color)
                break;
        };
        for (int i = i_now + 1, j = j_now - 1; i < 8 && 0 <= j; i++, j--) // Left & Up
        {
            if (::existMohre[i][j] == it_color)
                break;
            singleMoves[i][j] = 1;
            if (::existMohre[i][j] == -it_color)
                break;
        };
    };

    static void queenImageAttacks(int imageAttacks[8][8], Point currentAddress)
    {
        const int i_now = currentAddress.row();
        const int j_now = currentAddress.column();
        int it_color = ::existMohre[i_now][j_now]; // 1: White -1: Black

        for (int i = i_now - 1; 0 <= i; i--) // Down
        {
            imageAttacks[i][j_now] = 1;
            if (::existMohre[i][j_now] != 0)
                break;
        };
        for (int i = i_now + 1; i < 8; i++) // Up
        {
            imageAttacks[i][j_now] = 1;
            if (::existMohre[i][j_now] != 0)
                break;
        };
        for (int j = j_now + 1; j < 8; j++) // Right
        {
            imageAttacks[i_now][j] = 1;
            if (::existMohre[i_now][j] != 0)
                break;
        };
        for (int j = j_now - 1; 0 <= j; j--) // Left
        {
            imageAttacks[i_now][j] = 1;
            if (::existMohre[i_now][j] != 0)
                break;
        };
        for (int i = i_now + 1, j = j_now + 1; i < 8 && j < 8; i++, j++) // Right & Up
        {
            imageAttacks[i][j] = 1;
            if (::existMohre[i][j] != 0)
                break;
        };
        for (int i = i_now - 1, j = j_now + 1; 0 <= i && j < 8; i--, j++) // Right & Down
        {
            imageAttacks[i][j] = 1;
            if (::existMohre[i][j] != 0)
                break;
        };
        for (int i = i_now - 1, j = j_now - 1; 0 <= i && 0 <= j; i--, j--) // Left & Down
        {
            imageAttacks[i][j] = 1;
            if (::existMohre[i][j] != 0)
                break;
        };
        for (int i = i_now + 1, j = j_now - 1; i < 8 && 0 <= j; i++, j--) // Left & Up
        {
            imageAttacks[i][j] = 1;
            if (::existMohre[i][j] != 0)
                break;
        };
    };

    Queen(int y, int x, char color_formal)
        : Mohre(y, x, 'Q', color_formal, "./images/queen.jpg") // set current address
    {
        Mohre::setSingleMove(queenSingleMove);
        Mohre::setImageAttacks(queenImageAttacks);
    };
};

class Bishop : public Mohre // Fil
{
public:
    static void bishopSingleMove(int singleMoves[8][8], Point currentAddress)
    {
        const int i_now = currentAddress.row();
        const int j_now = currentAddress.column();
        int it_color = ::existMohre[i_now][j_now]; // 1: White -1: Black

        for (int i = i_now + 1, j = j_now + 1; i < 8 && j < 8; i++, j++) // Right & Up
        {
            if (::existMohre[i][j] == it_color)
                break;
            singleMoves[i][j] = 1;
            if (::existMohre[i][j] == -it_color)
                break;
        };
        for (int i = i_now - 1, j = j_now + 1; 0 <= i && j < 8; i--, j++) // Right & Down
        {
            if (::existMohre[i][j] == it_color)
                break;
            singleMoves[i][j] = 1;
            if (::existMohre[i][j] == -it_color)
                break;
        };
        for (int i = i_now - 1, j = j_now - 1; 0 <= i && 0 <= j; i--, j--) // Left & Down
        {
            if (::existMohre[i][j] == it_color)
                break;
            singleMoves[i][j] = 1;
            if (::existMohre[i][j] == -it_color)
                break;
        };
        for (int i = i_now + 1, j = j_now - 1; i < 8 && 0 <= j; i++, j--) // Left & Up
        {
            if (::existMohre[i][j] == it_color)
                break;
            singleMoves[i][j] = 1;
            if (::existMohre[i][j] == -it_color)
                break;
        };
    };

    static void bishopImageAttacks(int imageAttacks[8][8], Point currentAddress)
    {
        const int i_now = currentAddress.row();
        const int j_now = currentAddress.column();
        int it_color = ::existMohre[i_now][j_now]; // 1: White -1: Black

        for (int i = i_now + 1, j = j_now + 1; i < 8 && j < 8; i++, j++) // Right & Up
        {
            imageAttacks[i][j] = 1;
            if (::existMohre[i][j] != 0)
                break;
        };
        for (int i = i_now - 1, j = j_now + 1; 0 <= i && j < 8; i--, j++) // Right & Down
        {
            imageAttacks[i][j] = 1;
            if (::existMohre[i][j] != 0)
                break;
        };
        for (int i = i_now - 1, j = j_now - 1; 0 <= i && 0 <= j; i--, j--) // Left & Down
        {
            imageAttacks[i][j] = 1;
            if (::existMohre[i][j] != 0)
                break;
        };
        for (int i = i_now + 1, j = j_now - 1; i < 8 && 0 <= j; i++, j--) // Left & Up
        {
            imageAttacks[i][j] = 1;
            if (::existMohre[i][j] != 0)
                break;
        };
    };

    Bishop(int y, int x, char color_formal)
        : Mohre(y, x, 'B', color_formal, "./images/bishop.jpeg") // set current address
    {
        Mohre::setSingleMove(bishopSingleMove);
        Mohre::setImageAttacks(bishopImageAttacks);
    };
};

class Rook : public Mohre // Rokh
{
public:
    static void rookSingleMove(int singleMoves[8][8], Point currentAddress)
    {
        const int i_now = currentAddress.row();
        const int j_now = currentAddress.column();
        int it_color = ::existMohre[i_now][j_now]; // 1: White -1: Black

        for (int i = i_now - 1; 0 <= i; i--) // Down
        {
            if (::existMohre[i][j_now] == it_color)
                break;
            singleMoves[i][j_now] = 1;
            if (::existMohre[i][j_now] == -it_color)
                break;
        };
        for (int i = i_now + 1; i < 8; i++) // Up
        {
            if (::existMohre[i][j_now] == it_color)
                break;
            singleMoves[i][j_now] = 1;
            if (::existMohre[i][j_now] == -it_color)
                break;
        };
        for (int j = j_now + 1; j < 8; j++) // Right
        {
            if(::existMohre[i_now][j] == it_color)
                break;
            singleMoves[i_now][j] = 1;
            if (::existMohre[i_now][j] == -it_color)
                break;
        };
        for (int j = j_now - 1; 0 <= j; j--) // Left
        {
            if(::existMohre[i_now][j] == it_color)
                break;
            singleMoves[i_now][j] = 1;
            if (::existMohre[i_now][j] == -it_color)
                break;
        };
    };

    static void rookImageAttacks(int imageAttacks[8][8], Point currentAddress)
    {
        const int i_now = currentAddress.row();
        const int j_now = currentAddress.column();
        int it_color = ::existMohre[i_now][j_now]; // 1: White -1: Black

        for (int i = i_now - 1; 0 <= i; i--) // Up
        {
            imageAttacks[i][j_now] = 1;
            if (::existMohre[i][j_now] != 0)
                break;
        };
        for (int i = i_now + 1; i < 8; i++) // Down
        {
            imageAttacks[i][j_now] = 1;
            if (::existMohre[i][j_now] != 0)
                break;
        };
        for (int j = j_now + 1; j < 8; j++) // Right
        {
            imageAttacks[i_now][j] = 1;
            if (::existMohre[i_now][j] != 0)
                break;
        };
        for (int j = j_now - 1; 0 <= j; j--) // Left
        {
            imageAttacks[i_now][j] = 1;
            if (::existMohre[i_now][j] != 0)
                break;
        };
    };

    Rook(int y, int x, char color_formal)
        : Mohre(y, x, 'R', color_formal, "./images/rook.jpg") // set current address
    {
        Mohre::setSingleMove(rookSingleMove);
        Mohre::setImageAttacks(rookImageAttacks);
    };
};

class King : public Mohre // Shah
{
public:
    static void kingSingleMove(int singleMoves[8][8], Point currentAddress)
    {
        const int i_now = currentAddress.row();
        const int j_now = currentAddress.column();
        int it_color = ::existMohre[i_now][j_now]; // 1: White -1: Black

        if (0 <= i_now-1 && ::existMohre[i_now-1][j_now] != it_color) // UP
            singleMoves[i_now-1][j_now] = 1;
        if (i_now+1 < 8 && ::existMohre[i_now+1][j_now] != it_color) // Down
            singleMoves[i_now+1][j_now] = 1;
        if (j_now+1 < 8 && ::existMohre[i_now][j_now+1] != it_color) // Right
            singleMoves[i_now][j_now+1] = 1;
        if (0 <= j_now-1 && ::existMohre[i_now][j_now-1] != it_color) // Left
            singleMoves[i_now][j_now-1] = 1;

        if (0 <= i_now-1 && j_now+1 < 8 && ::existMohre[i_now-1][j_now+1] != it_color) // UP Right
            singleMoves[i_now-1][j_now+1] = 1;
        if (i_now+1 < 8 && j_now+1 < 8 && ::existMohre[i_now+1][j_now+1] != it_color) // Down Right
            singleMoves[i_now+1][j_now+1] = 1;

        if (0 <= i_now-1 && 0 <= j_now-1 && ::existMohre[i_now-1][j_now-1] != it_color) // UP Left
            singleMoves[i_now-1][j_now-1] = 1;
        if (i_now+1 < 8 && 0 <= j_now-1 && ::existMohre[i_now+1][j_now-1] != it_color) // Down Left
            singleMoves[i_now+1][j_now-1] = 1;

        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if ((it_color == 1 ? ::dangerForWhite : ::dangerForBlack)[i][j] == 1)
                    singleMoves[i][j] = 0;
    };

    static void kingImageleAttacks(int imageAttacks[8][8], Point currentAddress)
    {
        const int i_now = currentAddress.row();
        const int j_now = currentAddress.column();
        int it_color = ::existMohre[i_now][j_now]; // 1: White -1: Black
        if (0 <= i_now-1) // UP
            imageAttacks[i_now-1][j_now] = 1;
        if (i_now+1 < 8) // Down
            imageAttacks[i_now+1][j_now] = 1;
        if (j_now+1 < 8) // Right
            imageAttacks[i_now][j_now+1] = 1;
        if (0 <= j_now-1) // Left
            imageAttacks[i_now][j_now-1] = 1;

        if (0 <= i_now-1 && j_now+1 < 8) // UP Right
            imageAttacks[i_now-1][j_now+1] = 1;
        if (i_now+1 < 8 && j_now+1 < 8) // Down Right
            imageAttacks[i_now+1][j_now+1] = 1;

        if (0 <= i_now-1 && 0 <= j_now-1) // UP Left
            imageAttacks[i_now-1][j_now-1] = 1;
        if (i_now+1 < 8 && 0 <= j_now-1) // Down Left
            imageAttacks[i_now+1][j_now-1] = 1;
    };

    King(int y, int x, char color_formal)
        : Mohre(y, x, 'K', color_formal, "./images/king.jpg") // set current address
    {
        Mohre::setSingleMove(kingSingleMove);
        Mohre::setImageAttacks(kingImageleAttacks);         
    };
    
    void details() override
    {
        Mohre::details();
        const int i_now = row();
        const int j_now = column();
        int it_color = ::existMohre[i_now][j_now]; // 1: White -1: Black
        
        cout << "The status of kish = " << kish(it_color, i_now, j_now) << '\n';

        cout << "Danger For " << (it_color == 1 ? "White King:" : "Black King:") << '\n';
        if (it_color == 1)
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                    cout << ::dangerForWhite[i][j] << ' ';
                cout << '\n';
            }
        }
        else
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                    cout << ::dangerForBlack[i][j] << ' ';
                cout << '\n';
            }
    };
};

class ChessBoard
{
public:
    Mohre* chessBoard[8][8];
    King* whiteKing;
    King* blackKing;

    void copy_matrix_attack(const int matSor[][8], int matTarg[][8])
    {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (matSor[i][j] == 1)
                    matTarg[i][j] = 1;
    };

    void clear()
    {
        chessBoard[0][0] = new Rook(0, 0, 'B'); // Set Blacks
        chessBoard[0][1] = new Knight(0, 1, 'B');
        chessBoard[0][2] = new Bishop(0, 2, 'B');
        chessBoard[0][3] = new Queen(0, 3, 'B');

        blackKing = new King(0, 4, 'B');
        chessBoard[0][4] = blackKing;

        chessBoard[0][5] = new Bishop(0, 5, 'B');
        chessBoard[0][6] = new Knight(0, 6, 'B');
        chessBoard[0][7] = new Rook(0, 7, 'B');

        for (int j = 0; j < 8; j++)
            chessBoard[1][j] = new Pawn(1, j, 'B');
            
        for (int i = 2; i < 6; i++) // Set Nothing
            for (int j = 0; j < 8; j++)
                chessBoard[i][j] = new Mohre(i, j, '-');

        for (int j = 0; j < 8; j++) // Set Whites
            chessBoard[6][j] = new Pawn(6, j, 'W');

        chessBoard[7][0] = new Rook(7, 0, 'W');
        chessBoard[7][1] = new Knight(7, 1, 'W');
        chessBoard[7][2] = new Bishop(7, 2, 'W');
        chessBoard[7][3] = new Queen(7, 3, 'W');

        whiteKing = new King(7, 4, 'W');
        chessBoard[7][4] = whiteKing;

        chessBoard[7][5] = new Bishop(7, 5, 'W');
        chessBoard[7][6] = new Knight(7, 6, 'W');
        chessBoard[7][7] = new Rook(7, 7, 'W');
    };

    void input() // Set Blocks
    {
        char typ, clr;

        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
            {
                cin >> typ >> clr;
               
                if ( typ == 'R')
                {
                    Rook* R = new Rook(i, j, clr);
                    chessBoard[i][j] = R;
                }
                else if ( typ == 'N')
                {
                    Knight* N = new Knight(i, j, clr);
                    chessBoard[i][j] = N;
                }
                else if ( typ == 'B')
                {
                    Bishop* B = new Bishop(i, j, clr);
                    chessBoard[i][j] = B;
                }
                else if ( typ == 'Q')
                {
                    Queen *Q = new Queen(i, j, clr);
                    chessBoard[i][j] = Q;
                }
                else if ( typ == 'K')
                {
                    King *K = new King(i, j, clr);
                    chessBoard[i][j] = K;
                    if (clr == 'W')
                        whiteKing = K;
                    else if (clr == 'B')
                        blackKing = K;
                }
                else if ( typ == 'P')
                {
                    Pawn *P = new Pawn(i, j, clr);
                    chessBoard[i][j] = P;
                }
                else if ( typ == '-')
                {
                    Mohre* m = new Mohre(i, j, clr);
                    chessBoard[i][j] = m;
                };
            }; 
    };

    void updateAll(int row = 8, int column = 8)
    {
        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++)
            {
                ::dangerForBlack[i][j] = 0;
                ::dangerForWhite[i][j] = 0;
                ::existMohre[i][j] = 0;
            };

        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++)
                if (chessBoard[i][j] -> getIsInit() == true)
                    {
                        if (chessBoard[i][j] -> color == 'W')
                        {
                            ::existMohre[i][j] = 1;
                        }
                        else if (chessBoard[i][j] -> color == 'B')
                        {
                            ::existMohre[i][j] = -1;
                        };         
                    };  

        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++)
                if (chessBoard[i][j] -> getIsInit() == true)
                {
                    chessBoard[i][j] -> update();
                    if (chessBoard[i][j] -> color == 'W')
                    {
                        copy_matrix_attack(chessBoard[i][j] -> imageAttacks, ::dangerForBlack);
                    }
                    else if (chessBoard[i][j] -> color == 'B')
                    {

                        copy_matrix_attack(chessBoard[i][j] -> imageAttacks, ::dangerForWhite);
                    };         
                };  
    };

    void printDangerForBlack()
    {
        // updateAll();
        int i = 0;
        cout << "\nDanger for Black: \n";
        for (; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
                cout << ::dangerForBlack[i][j] << ' ';
            cout << '\n';
        };
    };

    void printDangerForWhite()
    {
        // updateAll();
        int i = 0;
        cout << "\nDanger for White: \n";
        for (; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
                cout << ::dangerForWhite[i][j] << ' ';
            cout << '\n';      
        };
    };

    bool kish(int color_king)
    {
        updateAll();

        int row = (color_king == 1 ? whiteKing -> row() : blackKing -> row()), column = (color_king == 1 ? whiteKing -> column() : blackKing -> column());
        return ::kish(color_king, row, column);
    };

    char* returnChessBoard()
    {
        updateAll();
        int counter = 1;
        char* arr = new char[130];
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
            {
                arr[counter + 0] = chessBoard[i][j]->getType();
                arr[counter + 1] = chessBoard[i][j]->getColor();
                counter += 2;
            };
        return arr;
    };

    void inputChessBoard(const char* arr)
    {
        char typ, clr;
        int counter = 1;

        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
            {
                typ = arr[counter + 0];
                clr = arr[counter + 1];
                counter += 2;
               
                if ( typ == 'R')
                {
                    Rook* R = new Rook(i, j, clr);
                    chessBoard[i][j] = R;
                }
                else if ( typ == 'N')
                {
                    Knight* N = new Knight(i, j, clr);
                    chessBoard[i][j] = N;
                }
                else if ( typ == 'B')
                {
                    Bishop* B = new Bishop(i, j, clr);
                    chessBoard[i][j] = B;
                }
                else if ( typ == 'Q')
                {
                    Queen *Q = new Queen(i, j, clr);
                    chessBoard[i][j] = Q;
                }
                else if ( typ == 'K')
                {
                    King *K = new King(i, j, clr);
                    chessBoard[i][j] = K;
                    if (clr == 'W')
                        whiteKing = K;
                    else if (clr == 'B')
                        blackKing = K;
                }
                else if ( typ == 'P')
                {
                    Pawn *P = new Pawn(i, j, clr);
                    chessBoard[i][j] = P;
                }
                else if ( typ == '-')
                {
                    Mohre* m = new Mohre(i, j, clr);
                    chessBoard[i][j] = m;
                };
            }; 
    };

    void createMohre(char typ, char clr, int i, int j)
    {
        updateAll();
        if ( typ == 'R')
        {
            Rook* R = new Rook(i, j, clr);
            this -> chessBoard[i][j] = R;
        }
        else if ( typ == 'N')
        {
            Knight* N = new Knight(i, j, clr);
            this -> chessBoard[i][j] = N;
        }
        else if ( typ == 'B')
        {
            Bishop* B = new Bishop(i, j, clr);
            this -> chessBoard[i][j] = B;
        }
        else if ( typ == 'Q')
        {
            Queen *Q = new Queen(i, j, clr);
            this -> chessBoard[i][j] = Q;
        }
        else if ( typ == 'K')
        {
            King *K = new King(i, j, clr);
            this -> chessBoard[i][j] = K;
            if (clr == 'W')
                this -> whiteKing = K;
            else if (clr == 'B')
                this -> blackKing = K;
        }
        else if ( typ == 'P')
        {
            Pawn *P = new Pawn(i, j, clr);
            this -> chessBoard[i][j] = P;
        }
    };

    void move(Point now, Point next)
    {
        updateAll();

        int i_now = now.row();
        int j_now = now.column();

        int i_next = next.row();
        int j_next = next.column();

        char clr = chessBoard[i_now][j_now]->getColor();
        char typ = chessBoard[i_now][j_now]->getType();

        Mohre* emp_mohre = new Mohre(i_now, j_now, '-');
        chessBoard[i_now][j_now] = emp_mohre;
        
        createMohre(typ, clr, i_next, j_next);

        updateAll();
        
        // cout << "Mohre Moved!\n";
    };

    void print()
    {
        // updateAll();

        int i = 0;
        cout << "\nChess Board is: \n";
        for (; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
                cout << chessBoard[i][j]->getType() << chessBoard[i][j]->getColor() << ' ';
            cout << '\n';      
        };
    };

    void statOfAll()
    {
        // updateAll();
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (chessBoard[i][j] -> isInit == true)
                    chessBoard[i][j] -> details();
    };

    void display(sf::RenderWindow& win)
    {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (chessBoard[i][j]->getIsInit())
                    chessBoard[i][j] -> show(win);
    }
};

Point** getSingleMoves2(const char* lcb, Point p0, int player1)
{
    ChessBoard ccb;
    ccb.inputChessBoard(lcb);
    ccb.updateAll();
    
    Point** sm = ccb.chessBoard[p0.row()][p0.column()]->getSingleMoves();

    int counter = 0;
    Point** pointPtr = new Point*[64];

    for (int i = 0; sm[i] != 0; i++)
    {
        ccb.inputChessBoard(lcb);
        ccb.updateAll();

        Point p1 = *sm[i];
        ccb.chessBoard[p0.row()][p0.column()] -> doMove(p1);
        ccb.move(p0, p1);

        if (ccb.kish(player1) == false)
        {
            pointPtr[counter] = sm[i];
            counter++;
        }
    }
    pointPtr[counter] = 0;
    counter++;
    return pointPtr;
}

Point** ans_point;
int* ans_Bool;
int counter_ans;

/*
step0 = makan avalie, harekat 1m ma [64] (test all)
step1 = harekat 1m harif (be eza har harkat) [64]
step2 = harekat 2m ma [64] -> (bayad oono kish kone)
step3 = harekat 2m harif (shah harif kish va harekati nabayad
                          vojod dashte bashe bara shah va be eza
                          har harekat baghie mohrehash kish raf nashe!)
*/
int Mate(int player1, const char* lcb, int step = 0) // arry of last chess board
{
    ChessBoard ccb; // current chess Board
    ccb.inputChessBoard(lcb); // create new current chessBoard from last chess board
    ccb.updateAll();   

    if (ccb.kish(player1) == false) // shah kish nist
    {
        if (step >= 3)
            return 2;
        
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (((ccb.chessBoard[i][j] -> color) == (player1 == 1 ? 'W' : 'B')) && (ccb.chessBoard[i][j] -> type != '-')) // entekhab mohre ma
                {        
                    ccb.inputChessBoard(lcb);                
                    ccb.updateAll();
                    Point** moves = ccb.chessBoard[i][j] -> getSingleMoves();

                    for (int counter = 0; moves[counter] != 0; counter++) // harekat oon Mohre moshakhas
                    {
                        Point p0 = ccb.chessBoard[i][j]-> getCurrentAddress(); // now address
                        Point p = *moves[counter]; // next address     
                        
                        ccb.chessBoard[i][j]->doMove(p); // (p0 -> p)
                        ccb.move(p0, p); // (p0 -> p)
                        
                        if (ccb.kish(player1) == true) // ba in harekat shah khodemon kish shode! -> amal maakos
                        {
                            ccb.inputChessBoard(lcb);
                            ccb.updateAll();
                            continue;
                        };
                        
                        ccb.updateAll();

                        if (step == 0) // step0 = makan avalie, harekat 1m ma (test all)
                        {
                            ::ans_point[0][::counter_ans] = p0;
                            ::ans_point[1][::counter_ans] = p;
                        };
                        if (step == 1) // step1 = harekat 1m harif (be eza har harkat)
                            ::ans_point[2][::counter_ans] = p;
                        if (step == 2) // step2 = harekat 2m ma -> (bayad oono kish kone)
                        {
                            if (ccb.kish(-player1) == false) // agar oon ro kish nakard, bro harekat baadi
                            {
                                ccb.inputChessBoard(lcb);
                                ccb.updateAll();
                                continue;
                            }              
                            else
                                ::ans_point[3][::counter_ans] = p;                      
                        };

                        if (step <= 3)
                                ans_Bool[::counter_ans] = 0;
                            else 
                                return step -1; 
                        
                        int s = Mate(-player1, ccb.returnChessBoard(), step + 1);                        

                        switch (step)
                        {
                        case 0:
                            if (ans_Bool[::counter_ans] == 1)
                                ::counter_ans++;
                        break;
                        case 1:   
                            if (ans_Bool[::counter_ans] != 1)
                                return 0;
                            break; 
                        case 2:
                            if (ans_Bool[::counter_ans] == 1)
                                return 1;
                            break;
                        default:
                            if(step >= 3)
                                if (::ans_Bool[::counter_ans] != 1)
                                    return 2;
                        break;
                        }

                        if (s < step)
                            return s;
                        ccb.inputChessBoard(lcb);
                        ccb.updateAll();
                    };
                    ccb.inputChessBoard(lcb);
                    ccb.updateAll();
                };
            ccb.inputChessBoard(lcb);
            ccb.updateAll();
    }
    else // shah kish hast
    {
        for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                    if (((ccb.chessBoard[i][j] -> color) == (player1 == 1 ? 'W' : 'B')) && (ccb.chessBoard[i][j] -> type != '-')) // entekhab mohre ma
                    {                        
                        ccb.inputChessBoard(lcb);
                        ccb.updateAll();
                        Point** moves = ccb.chessBoard[i][j] -> getSingleMoves();

                        for (int counter = 0; moves[counter] != 0; counter++) // harekat oon Mohre moshakhas
                        {
                            Point p0 = ccb.chessBoard[i][j]-> getCurrentAddress(); // now address
                            Point p = *moves[counter]; // next address
                            
                            ccb.chessBoard[i][j]->doMove(p); // (p0 -> p)
                            ccb.move(p0, p); // (p0 -> p)
                            
                            if (ccb.kish(player1) == true) // ba in harekat shah khodemon kish shode! -> amal maakos
                            {
                                ccb.inputChessBoard(lcb);
                                ccb.updateAll();
                                continue;
                            };
                            
                            ccb.updateAll();

                            if (step == 0) // step0 = makan avalie, harekat 1m ma (test all)
                            {
                                ::ans_point[0][::counter_ans] = p0;
                                ::ans_point[1][::counter_ans] = p;
                            };
                            if (step == 1) // step1 = harekat 1m harif (be eza har harkat)
                                ::ans_point[2][::counter_ans] = p;
                            if (step == 2) // step2 = harekat 2m ma -> (bayad oono kish kone)
                            {
                                if (ccb.kish(-player1) == false) // agar oon ro kish nakard, bro harekat baadi
                                {
                                    ccb.inputChessBoard(lcb);
                                    ccb.updateAll();
                                    continue;
                                }              
                                else
                                    ::ans_point[3][::counter_ans] = p;                      
                            };

                            if (step <= 3)
                                ans_Bool[::counter_ans] = 0;
                            else 
                                return 2;   
                            
                            int s = Mate(-player1, ccb.returnChessBoard(), step + 1);

                            switch (step)
                            {
                            case 0:
                                if (ans_Bool[::counter_ans] == 1)
                                    ::counter_ans++;
                                break;
                            case 1:   
                                if (ans_Bool[::counter_ans] != 1)
                                    return 0;
                                break; 
                            case 2:
                                if (ans_Bool[::counter_ans] == 1)
                                    return 1;
                                break;
                            default:
                                if(step >= 3)
                                    if (::ans_Bool[::counter_ans] != 1)
                                        return 2;
                            break;
                            }
                            
                            if (s < step)
                                return s;

                            ccb.inputChessBoard(lcb);
                            ccb.updateAll();
                        };
                        ccb.inputChessBoard(lcb);
                        ccb.updateAll();
                    };
        ccb.inputChessBoard(lcb);
        ccb.updateAll();
    }

    ccb.inputChessBoard(lcb);
    ccb.updateAll();

    if (ccb.kish(player1) == true && step % 2 != 0 )
    {
        ::ans_Bool[::counter_ans] = 1;
            return 1;
    }
    else 
        return step - 1;
};

/*
step0 = makan avalie, harekat 1m ma [64] (test all)
step1 = harekat 1m harif (vojod) [64]
step2 = harekat 2m ma [64] -> (be eza har harekat)
step3 = harekat 2m harif (vojod & kish kone)
step4 = (shah ma kish va harekati nabayad
        vojod dashte bashe bara shah va be eza
        har harekat baghie mohrehamon kish raf nashe!)
*/
int Defence(int player1, const char* lcb, int step = 0)
{
    ChessBoard ccb;
    ccb.inputChessBoard(lcb);
    ccb.updateAll();

            // KISH NIST
    if (ccb.kish(player1) == false)
    {
        if (step >= 4)
            return 2;

        for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                    if (((ccb.chessBoard[i][j] -> color) == (player1 == 1 ? 'W' : 'B')) && (ccb.chessBoard[i][j] -> type != '-'))
                    {
                        Point** moves = ccb.chessBoard[i][j] -> getSingleMoves();
                        for (int counter = 0; moves[counter] != 0; counter++)
                        {
                            Point p0 = ccb.chessBoard[i][j]-> getCurrentAddress(); // current address
                            Point p = *moves[counter]; // next address
                            
                            ccb.chessBoard[i][j]->doMove(p); // (p0 -> p)
                            ccb.move(p0, p); // (p0 -> p)
                            
                            if (ccb.kish(player1) == true) // ba in harekat shah khodemon kish shode! -> amal maakos.
                            {
                                ccb.inputChessBoard(lcb);
                                ccb.updateAll();
                                continue;
                            };

                            if (step == 0)
                            {
                                ::ans_point[0][::counter_ans] = p0;
                                ::ans_point[1][::counter_ans] = p;
                            }
                            if (step == 1)
                                ::ans_point[2][::counter_ans] = p;
                            if (step == 2)
                                ::ans_point[3][::counter_ans] = p;
                            if (step == 3 && ccb.kish(-player1) == false) // (bayad maro kish kone)
                            {
                                ccb.inputChessBoard(lcb);
                                ccb.updateAll();
                                continue;                             
                            };
                            if (step <= 4)
                                ans_Bool[::counter_ans] = 0;
                            else 
                                return step -1;

                            int s = Defence(-player1, ccb.returnChessBoard(), step + 1);

                            if (step == 0 && ans_Bool[::counter_ans] == 1)
                            {
                                ::counter_ans++;
                            };
                            if (step == 1 && ans_Bool[::counter_ans] == 1)
                                return 0;
                            if (step == 2)
                            {
                                if (::ans_Bool[::counter_ans] != 1)
                                    return 1;
                            }
                            if (step == 3 && ans_Bool[::counter_ans] == 1)
                                return 2;

                            if (s < step)
                                return s;

                            ccb.inputChessBoard(lcb);
                            ccb.updateAll();
                        }
                        delete[] moves;
                    }
        return step - 1;
    }
            // KISH HAST
    else
    {
                                // RAFE KISH

        for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                    if (((ccb.chessBoard[i][j] -> color) == (player1 == 1 ? 'W' : 'B')) && (ccb.chessBoard[i][j] -> type != '-'))
                    {
                        Point** moves = ccb.chessBoard[i][j] -> getSingleMoves();
                        for (int counter = 0; moves[counter] != 0; counter++)
                        {
                            Point p0 = ccb.chessBoard[i][j]-> getCurrentAddress(); // current address
                            Point p = *moves[counter]; // next address
                            
                            ccb.chessBoard[i][j]->doMove(p); // (p0 -> p)
                            ccb.move(p0, p); // (p0 -> p)
                            
                            if (ccb.kish(player1) == true) // ba in harekat shah khodemon kish shode! -> amal maakos.
                            {
                                ccb.inputChessBoard(lcb);
                                ccb.updateAll();
                                continue;
                            }
                            else
                            {
                                if (step > 4)
                                    return 2;
                            }

                            if (step == 0)
                            {
                                ::ans_point[0][::counter_ans] = p0;
                                ::ans_point[1][::counter_ans] = p;
                            }
                            if (step == 1)
                                ::ans_point[2][::counter_ans] = p;
                            if (step == 2)
                                ::ans_point[3][::counter_ans] = p;
                            if (step == 3 && ccb.kish(-player1) == false) // (bayad maro kish kone)
                            {
                                ccb.inputChessBoard(lcb);
                                ccb.updateAll();
                                continue;                             
                            };

                            int s = Defence(-player1, ccb.returnChessBoard(), step + 1);

                            if (step == 0 && ans_Bool[::counter_ans] == 1)
                            {
                                ::counter_ans++;
                            };
                            if (step == 1 && ans_Bool[::counter_ans] == 1)
                                return 0;
                            if (step == 2)
                            {
                                if (::ans_Bool[::counter_ans] != 1)
                                    return 1;
                            }
                            if (step == 3 && ans_Bool[::counter_ans] == 1)
                                return 2;

                            if (s < step)
                                return s;

                            ccb.inputChessBoard(lcb);
                            ccb.updateAll();
                        }
                        delete[] moves;
                    }
                                // MAT
            if (ccb.kish(player1) == true && step % 2 == 0)
            {
                ::ans_Bool[::counter_ans] = 1;
                return 2;
            }
            else if (step > 4 && ccb.kish(player1) == false)
                return 3;
            else
                return step - 1;
    }
    return step - 1;
};

void set()
{
    ::ans_point = new Point*[4];
    for (int i = 0; i < 4; i++)
        ::ans_point[i] = new Point[64];

    ans_Bool = new int[64];
    fill_n(::ans_Bool, 64, 0); // set the ans bool!

    ::counter_ans = 0;
}

void clean()
{
    for (int i = 0; i < 4; i++)
        delete[] ::ans_point[i];
    delete[] ::ans_point;

    delete[] ::ans_Bool;
}

void play_game()
{
    set(); // set deafult to statrt game

    char which_player, type_game; // Input stat of start
    cin >> which_player >> type_game;
    int player1 = (which_player == 'W' ? 1 : -1);

    ChessBoard chessBoard; // create chess board
    chessBoard.input(); // set chessBoard
    chessBoard.updateAll(); // update chess board
    // chessBoard.print(); // print chessBoard (not imp)
    // chessBoard.printDangerForBlack(); // print Danger For Black (not imp)
    // chessBoard.printDangerForWhite(); // print Danger For White (not imp)
    // chessBoard.statOfAll(); // print status of all (not imp)

    const char* backUp = chessBoard.returnChessBoard();
    // cout << "\n^^^^^^^^^^^^^^^^^^^^^^^^^^\nThe Game Started! \n\n";
    if (type_game == 'M')
        Mate(player1, chessBoard.returnChessBoard(), 0);
    else
        Defence(player1, chessBoard.returnChessBoard(), 0);

    // cout << "\nThe Game ended! \n\nans: \n";
    chessBoard.inputChessBoard(backUp); // undo

    // cout << "counter ans: " << counter_ans << endl;
    string ans[::counter_ans];
    fill_n(ans, ::counter_ans, "");

    int ans_frq[::counter_ans];
    fill_n(ans_frq, ::counter_ans, 0);

    int i_fin = 0;
    string ans_fin[::counter_ans];
    fill_n(ans_fin, ::counter_ans, "");

    int ans_fin_frq[::counter_ans];
    fill_n(ans_fin_frq, ::counter_ans, 0);

    if (counter_ans == 0)
    {
        cout << "No Answer!";
        exit(0);
    }
    else
    {
        for (int i = 0; i <= counter_ans; i++)
        {
            int row = ::ans_point[0][i].row();
            int column = ::ans_point[0][i].column();

            // if (ans_Bool[i] == 1)
            //     cout << ::ans_point[0][i] << chessBoard.chessBoard[row][column]->getType() << chessBoard.chessBoard[row][column]->getColor() << ans_point[1][i] << '\n';
            
            if (ans_Bool[i] == 1)
            {
                Point** moves = chessBoard.chessBoard[row][column] -> getSingleMoves();
                int x = 0;
                for (; moves[x] != 0; x++);
                ans_frq[i] = x;

                ans[i] += char(::ans_point[0][i].column() + int('a'));
                ans[i] += char(int('0') + 8 - ::ans_point[0][i].row());
                ans[i] += chessBoard.chessBoard[row][column]->getType();
                ans[i] += chessBoard.chessBoard[row][column]->getColor();
                ans[i] += char(::ans_point[1][i].column() + int('a'));
                ans[i] += char(int('0') + 8 - ::ans_point[1][i].row());

                if (i == 0)
                {
                    ans_fin[0] = ans[0];
                    ans_fin_frq[0]++;
                }
                else if (ans[i].substr(0, 4) == ans_fin[i_fin].substr(0, 4))
                    ans_fin_frq[i_fin]++;
                else if (ans[i].substr(0, 4) != ans_fin[i_fin].substr(0, 4))
                {
                    i_fin++;
                    ans_fin[i_fin] = ans[i];
                    ans_fin_frq[i_fin]++;
                }
            }
        }
    }

    clean(); // clean code to new set

    int i_end = 0;
    string ans_end[::counter_ans];
    fill_n(ans_end, ::counter_ans, "");
    
    int i = 0;
    while (i < counter_ans)
    {
        int itsFrqIn = ans_frq[i];
        int MaxFrq;

        for (int j = 0; j <= i_fin; j++)
            if (ans_fin[j].substr(0, 4) == ans[i].substr(0, 4))
                MaxFrq = ans_fin_frq[j];
        if (itsFrqIn == MaxFrq)
        {
            ans_end[i_end] = ans[i].substr(0, 4);
            i++;
            while (ans_end[i_end] == ans[i].substr(0, 4))
            {
                i++;
            }
            if (i_end + 1 < ::counter_ans)
                i_end++;
        }
        else
        {
            ans_end[i_end] = ans[i];
            i++;
            while (ans_end[i_end].substr(0, 4) == ans[i].substr(0, 4))
            {
                i_end++;
                ans_end[i_end] = ans[i];
                i++;
            }
            if (i_end + 1 < ::counter_ans)
                i_end++;
        }
    }

    for (int i = 0; i <= i_end; i++);

    // cout << endl << " ll";
    for (int i = 0; i <= i_end; i++)
        for (int j = i + 1; j <= i_end; j++)
            if (ans_end[j] < ans_end[i])
            {
                string tmp = ans_end[i];
                ans_end[i] = ans_end[j];
                ans_end[j] = tmp;
            }
    for (int i = 0; i <= i_end; i++)
        if (ans_end[i] != "")
            cout << ans_end[i] << '\n';
}

sf::Text printText(std::string massege, sf::Font font, sf::Text status_text)
{
    font.loadFromFile("../Resources/Fonts/PinaColadaCreation.ttf");

    status_text.setFont(font);

    int j = 7, i = 0;
    j = 7.5f + 50.0f + (105*j) + 63, i = 7.5f + 50.0f + (105*i) - 40;

    const int size = 40;
    status_text.setCharacterSize(size);
    status_text.setStyle(sf::Text::Bold);
    status_text.setFillColor(sf::Color::Black);
    status_text.setPosition(j, i);
    status_text.setString(massege);
    return status_text;
}

sf::Text printTextKishorMat(sf::Font font, sf::Text status_text, int type) // 1: kish, -1: mat
{
    std::string str = (type == 1 ? "Kish!" : "Mate!");

    font.loadFromFile("../Resources/Fonts/PinaColadaCreation.ttf");

    status_text.setFont(font);

    int j = 7, i = 1;
    j = 7.5f + 50.0f + (105*j) + 95, i = 7.5f + 50.0f + (105*i) - 70;

    const int size = 60;
    status_text.setCharacterSize(size);
    status_text.setStyle(sf::Text::Bold);
    status_text.setFillColor(sf::Color::Black);
    status_text.setPosition(j, i);
    status_text.setString(str);
    return status_text;
}

bool mat(const char* lcb, int player)
{
    ChessBoard ccb;
    ccb.inputChessBoard(lcb);
    ccb.updateAll();

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (ccb.chessBoard[i][j] -> getIsInit() == true && ccb.chessBoard[i][j] -> getColor() == (player == 1 ? 'W' : 'B'))
            {
                Point** m = getSingleMoves2(lcb, Point(i, j), player);
                if (m[0] != 0)
                    return false;
            }
    return true;
}

int main()
{
    for (int i = 0; i < 8; i++) // set global mats!
        for (int j = 0; j < 8; j++)
        {
            ::existMohre[i][j] = 0;
            ::dangerForWhite[i][j] = 0;
            ::dangerForBlack[i][j] = 0; 
        }
    
    int turn = 0; // odd: turn black
                  // even: turn white

    int window_height = 850 + 200, window_width = 850;
    float cell_size = 100.0f;

    sf::RenderWindow window (sf::VideoMode(window_height, window_width), "Basic Chess", sf::Style::Close | sf::Style::Titlebar); // creat window
    window.setFramerateLimit(8);

    sf::Font font;
    sf::Text status_text;

    sf::RectangleShape back_ground (sf::Vector2f(845 + 200, 845)); // create a shape
    back_ground.setFillColor(sf::Color(0, 0, 128)); // color the shape
    back_ground.setOrigin(845 / 2 + 100, 845 / 2); // set the center of shape
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

    int i1 = 7, j1 = 9;
    Point clr_point(i1, j1);
    sf::RectangleShape clr(sf::Vector2f(90.0f, 90.0f)); // create a MOHRE
    clr.setOrigin(45.0f, 45.0f); // set the center of MOHRE
    clr.setPosition(7.5f + 50.0f + (105*j1), 7.5f + 50.0f + (105*i1)); // set the start of MOHRE
    sf::Texture clr_texture; // set photo
    clr_texture.loadFromFile("./images/return.png");
    clr.setTexture(&clr_texture);
    // clr.setFillColor(sf::Color::Yellow);

    ChessBoard chessboard;
    chessboard.clear();  

    while (window.isOpen())
    {
        sf::Event evnt; // create event
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed: // if tap the botten X
                window.close();
                exit(0);
                break;
            }
        }
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // move the shape by mouse
        {
            // x = column, y = row
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            int x = mousePos.x, y = mousePos.y;
            x = (x - 7.5) / (cell_size + 5), y = (y - 7.5) / (cell_size + 5);    

            Point now(y, x);
            if (clr_point == now)
            {
                chessboard.clear(); 
                window.clear(sf::Color(0, 0, 0)); // clear the buffer
                    window.draw(back_ground);
                    for (int i = 0; i < 8; i++)
                        for (int j = 0; j < 8; j++)
                            window.draw(cells[i][j]);
                chessboard.display(window);
                turn = 0;
                continue;
            }

            if (chessboard.chessBoard[y][x] -> getIsInit() == true)
            {
                Point p0(y, x);

                if ((((turn % 2 == 0 && chessboard.chessBoard[y][x] -> getColor() == 'W') || (turn % 2 == 1 && chessboard.chessBoard[y][x] -> getColor() == 'B')) && (y < 8 && x < 8)) || (y == clr_point.row() && clr_point.column()))
                {
                    // printf("x0: %i,  y0: %i,  turn: %i\n", x, y, turn);
                    sf::RectangleShape which_mohre(sf::Vector2f(90.0f, 90.0f)); // create a MOHRE
                    which_mohre.setOrigin(45.0f, 45.0f); // set the center of MOHRE
                    which_mohre.setPosition(7.5f + 50.0f + (105*x), 7.5f + 50.0f + (105*y)); // set the start of MOHRE
                    sf::Texture which_mohre_texture; // set photo
                    which_mohre_texture.loadFromFile("./images/dot.png");
                    which_mohre.setTexture(&which_mohre_texture);
                    which_mohre.setFillColor(sf::Color::Magenta);

                    chessboard.updateAll();
                    Point** moves = getSingleMoves2(chessboard.returnChessBoard(), p0, (turn % 2 == 0 ? 1 : -1));

                    window.clear(sf::Color(0, 0, 0)); // clear the buffer
                    window.draw(back_ground);
                    for (int i = 0; i < 8; i++)
                        for (int j = 0; j < 8; j++)
                            window.draw(cells[i][j]);

                    chessboard.display(window);

                    for (int i = 0; moves[i] != 0; i++)
                    {
                        int i1 = (*moves[i]).row(), j1 = (*moves[i]).column();
                        sf::RectangleShape dot(sf::Vector2f(90.0f, 90.0f)); // create a MOHRE
                        dot.setOrigin(45.0f, 45.0f); // set the center of MOHRE
                        dot.setPosition(7.5f + 50.0f + (105*j1), 7.5f + 50.0f + (105*i1)); // set the start of MOHRE
                        sf::Texture dot_texture; // set photo
                        dot_texture.loadFromFile("./images/dot2.png");
                        dot.setTexture(&dot_texture);
                        int it_color = (chessboard.chessBoard[y][x] -> getColor() == 'W' ? 1 : -1);
                        dot.setFillColor((::existMohre[i1][j1] == -it_color ? sf::Color::Red : sf::Color::White));
                        window.draw(dot);
                    }

                    window.draw(clr);
                    window.draw(which_mohre);

                    int turn_who = (turn % 2 == 0 ? 1 : -1);
                    if (chessboard.kish(turn_who))
                    {
                        int i1 = (turn_who == 1 ? chessboard.whiteKing->row() : chessboard.blackKing->row()), j1 = (turn_who == 1 ? chessboard.whiteKing->column() : chessboard.blackKing->column());
                        sf::RectangleShape danger_point(sf::Vector2f(90.0f, 90.0f)); // create a MOHRE
                        danger_point.setOrigin(45.0f, 45.0f); // set the center of MOHRE
                        danger_point.setPosition(7.5f + 50.0f + (105*j1), 7.5f + 50.0f + (105*i1)); // set the start of MOHRE
                        sf::Texture danger_point_texture; // set photo
                        danger_point_texture.loadFromFile("./images/dot.png");
                        danger_point.setTexture(&danger_point_texture);
                        danger_point.setFillColor(sf::Color::Red);
                        window.draw(danger_point);
                        if (mat(chessboard.returnChessBoard(), turn_who))
                            window.draw(printTextKishorMat(font, status_text, -1));
                        else
                            window.draw(printTextKishorMat(font, status_text, 1));
                    }

                    window.draw(printText((turn % 2 == 0 ? "White Turn" : "Black Turn"), font, status_text));
                    window.display();


                    bool tmp = true;
                    while (tmp)
                    {
                        if (window.pollEvent(evnt) && evnt.type == sf::Event::Closed)
                        {
                                window.close();
                                exit(0);
                        }

                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            if (window.pollEvent(evnt) && evnt.type == sf::Event::Closed)
                            {
                                window.close();
                                exit(0);
                            }

                            sf::Vector2i mousePos2 = sf::Mouse::getPosition(window);
                            x = mousePos2.x, y = mousePos2.y;
                            x = (x - 7.5) / (cell_size + 5), y = (y - 7.5) / (cell_size + 5);  
                            Point p1(y, x);

                            if (clr_point == p1)
                            {
                                chessboard.clear(); 
                                window.clear(sf::Color(0, 0, 0)); // clear the buffer
                                    window.draw(back_ground);
                                    for (int i = 0; i < 8; i++)
                                        for (int j = 0; j < 8; j++)
                                            window.draw(cells[i][j]);
                                chessboard.display(window);
                                turn = 0;
                                break;
                            }

                            if ((((turn % 2 == 0 && chessboard.chessBoard[y][x] -> getColor() == 'W') || (turn % 2 == 1 && chessboard.chessBoard[y][x] -> getColor() == 'B')) && (y < 8 && x < 8)) || (y == clr_point.row() && clr_point.column()))
                            {
                                p0 = p1;

                                chessboard.updateAll();
                                moves = getSingleMoves2(chessboard.returnChessBoard(), p0, (turn % 2 == 0 ? 1 : -1));

                                sf::Vector2i mousePos3 = sf::Mouse::getPosition(window);
                                x = mousePos3.x, y = mousePos3.y;
                                x = (x - 7.5) / (cell_size + 5), y = (y - 7.5) / (cell_size + 5);  
                                Point p1_2(y, x);
                                p1 = p1_2;

                                if (clr_point == p1)
                                {
                                    chessboard.clear(); 
                                    window.clear(sf::Color(0, 0, 0)); // clear the buffer
                                        window.draw(back_ground);
                                        for (int i = 0; i < 8; i++)
                                            for (int j = 0; j < 8; j++)
                                                window.draw(cells[i][j]);
                                    chessboard.display(window);
                                    turn = 0;
                                    break;
                                }

                                sf::RectangleShape which_mohre(sf::Vector2f(90.0f, 90.0f)); // create a MOHRE
                                which_mohre.setOrigin(45.0f, 45.0f); // set the center of MOHRE
                                which_mohre.setPosition(7.5f + 50.0f + (105*p0.column()), 7.5f + 50.0f + (105*p0.row())); // set the start of MOHRE
                                sf::Texture which_mohre_texture; // set photo
                                which_mohre_texture.loadFromFile("./images/dot.png");
                                which_mohre.setTexture(&which_mohre_texture);
                                which_mohre.setFillColor(sf::Color::Magenta);

                                window.clear(sf::Color(0, 0, 0)); // clear the buffer
                                window.draw(back_ground);
                                for (int i = 0; i < 8; i++)
                                    for (int j = 0; j < 8; j++)
                                        window.draw(cells[i][j]);

                                chessboard.display(window);

                                for (int i = 0; moves[i] != 0; i++)
                                {
                                    int i1 = (*moves[i]).row(), j1 = (*moves[i]).column();
                                    sf::RectangleShape dot(sf::Vector2f(90.0f, 90.0f)); // create a MOHRE
                                    dot.setOrigin(45.0f, 45.0f); // set the center of MOHRE
                                    dot.setPosition(7.5f + 50.0f + (105*j1), 7.5f + 50.0f + (105*i1)); // set the start of MOHRE
                                    sf::Texture dot_texture; // set photo
                                    dot_texture.loadFromFile("./images/dot2.png");
                                    dot.setTexture(&dot_texture);
                                    int it_color = (chessboard.chessBoard[y][x] -> getColor() == 'W' ? 1 : -1);
                                    dot.setFillColor((::existMohre[i1][j1] == -it_color ? sf::Color::Red : sf::Color::White));
                                    window.draw(dot);
                                }

                                window.draw(clr);
                                window.draw(which_mohre);

                                int turn_who = (turn % 2 == 0 ? 1 : -1);
                                if (chessboard.kish(turn_who))
                                {
                                    int i1 = (turn_who == 1 ? chessboard.whiteKing->row() : chessboard.blackKing->row()), j1 = (turn_who == 1 ? chessboard.whiteKing->column() : chessboard.blackKing->column());
                                    sf::RectangleShape danger_point(sf::Vector2f(90.0f, 90.0f)); // create a MOHRE
                                    danger_point.setOrigin(45.0f, 45.0f); // set the center of MOHRE
                                    danger_point.setPosition(7.5f + 50.0f + (105*j1), 7.5f + 50.0f + (105*i1)); // set the start of MOHRE
                                    sf::Texture danger_point_texture; // set photo
                                    danger_point_texture.loadFromFile("./images/dot.png");
                                    danger_point.setTexture(&danger_point_texture);
                                    danger_point.setFillColor(sf::Color::Red);
                                    window.draw(danger_point);
                                    if (mat(chessboard.returnChessBoard(), turn_who))
                                        window.draw(printTextKishorMat(font, status_text, -1));
                                    else
                                        window.draw(printTextKishorMat(font, status_text, 1));
                                }

                                window.draw(printText((turn % 2 == 0 ? "White Turn" : "Black Turn"), font, status_text));
                                window.display();
                            }
                            for (int i = 0; moves[i] != 0; i++)
                            {
                                if (p1 == *moves[i])
                                {
                                    tmp = false;
                                    chessboard.move(p0, p1);
                                    turn++;
                                    break;
                                }
                            } 
                            // printf("x1: %i,  y1: %i,  turn: %i\n", x, y, turn);
                        }

                    }
                }

            }
        }

        window.clear(sf::Color(0, 0, 0)); // clear the buffer
        window.draw(back_ground);
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                window.draw(cells[i][j]);

        chessboard.display(window);
        window.draw(clr);

        int turn_who = (turn % 2 == 0 ? 1 : -1);
        if (chessboard.kish(turn_who))
        {
            int i1 = (turn_who == 1 ? chessboard.whiteKing->row() : chessboard.blackKing->row()), j1 = (turn_who == 1 ? chessboard.whiteKing->column() : chessboard.blackKing->column());
            sf::RectangleShape danger_point(sf::Vector2f(90.0f, 90.0f)); // create a MOHRE
            danger_point.setOrigin(45.0f, 45.0f); // set the center of MOHRE
            danger_point.setPosition(7.5f + 50.0f + (105*j1), 7.5f + 50.0f + (105*i1)); // set the start of MOHRE
            sf::Texture danger_point_texture; // set photo
            danger_point_texture.loadFromFile("./images/dot.png");
            danger_point.setTexture(&danger_point_texture);
            danger_point.setFillColor(sf::Color::Red);
            window.draw(danger_point);
            if (mat(chessboard.returnChessBoard(), turn_who))
                window.draw(printTextKishorMat(font, status_text, -1));
            else
                window.draw(printTextKishorMat(font, status_text, 1));
        }

        window.draw(printText((turn % 2 == 0 ? "White Turn" : "Black Turn"), font, status_text));
        window.display(); // out pot the buffer
    }

    return 0;
}
