#include <iostream>

// OOP: struct, class, ctor/dtor, inheritance

// this ptr, static functions
// functions vs function parameters
// methods vs objects

// OOP basics
// ctor/dtor
// copy-ctor, copy-assignment

// function / operator overloading

// almost always auto - aaa rule: move type to the right
// unified/universal initialization

// namespaces

// move-ctor, move-assignment
// inheritance
// dynamic polymorphism, v-table (default in Java, you opt-in in C++ with virtual keyword) (not covered in CS321)

#include <iostream>
#include <string>

//#define COMEDY 0
//#define DRAMA  1
//#define ACTION 2

enum class GENRE {
    COMEDY,
    DRAMA,
    ACTION,
};

std::string GENRE_TEXT[] = {"COMEDY", "DRAMA", "ACTION"};

inline namespace Shows {
struct TVShow
{
    std::string name; // C style
    short year;
    GENRE genre;

    TVShow(std::string name, short year, GENRE genre)
        : name(name), year(year), genre(genre) { }

    TVShow(const TVShow& other)
        : name(other.name), year(other.year), genre(other.genre)
    { // copy ctor
        std::cout << "Copy constructor has been called" << std::endl;
    }

    void operator =(const TVShow& right)
    {
        name = right.name;
        year = right.year;
        genre = right.genre;
        std::cout << "TVShow's copy assignment has been called" << std::endl;
    }

    ~TVShow() { // destructor

    }

    void print()
    {
        std::cout << name << std::endl;
        std::cout << year << std::endl;
        std::cout << GENRE_TEXT[(int)genre] << std::endl;
    }
};

void print(const TVShow& show)
{
//    show.name = "FRIENDS";
    std::cout << show.name << std::endl;
    std::cout << show.year << std::endl;
    std::cout << GENRE_TEXT[(int)show.genre] << std::endl;
}

} // end of Shows namespace


int main(int argc, char* argv[])
{
    const int a = 5;

    auto show = TVShow{"Seinfeld", 1990, GENRE::COMEDY};
    print(show);

    std::cout << std::endl;

//    auto show2 = show; // copy construction

    auto show2 = TVShow{"Seinfeld", 1990, GENRE::COMEDY};
    show2 = show; // copy assignment

    4 + 5; // infix notation
//    operator+(4, 5); prefix notatin

//    show2.operator=(show);

    show2.name = "FRIENDS";
    print(show2);

//    std::cout << show.name << std::endl;
//    std::cout << show.year << std::endl;
//    std::cout << GENRE_TEXT[(int)show.genre] << std::endl;

    return 0;
}
