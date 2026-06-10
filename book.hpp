#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>

using namespace std;

struct Book {
    string title;
    string author;
    string description;
    bool isAvialable;

    string borrowerID;
};

#endif // BOOK_HPP