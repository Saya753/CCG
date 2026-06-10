#ifndef LIB_HPP
#define LIB_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include "book.hpp"
#include "user.hpp"

#define USERS_PATH "users.txt"
#define BOOKS_PATH "books.txt"

using namespace std;

struct Lib{
    string name;
    string operationhour; 
    vector<Book> books;
    vector<User> users;

    bool isIn(string entry, string target) {
        return target.find(entry) != string::npos;
    }

    void addBook( string title , string author , string description, bool available ) 
    {
        Book b={title, author, description, available, "None"};
        books.push_back(b);
    }

    bool deleteBook( string title )
    {
        for (int i = 0; i < books.size(); i++) {
            if (title == books[i].title) {
                books.erase(books.begin() + i);
                return true;
            }
        }

        return false;
    }

    void showBooks()
    {
        if (books.size() == 0) {
            cout << "\e[0;31mThere is no book in our library :)\e[1;37m" << endl;
            return;
        }
        cout << "\e[0;33m--~~Books~~--\e[0;37m" << endl;
        // for (int i = 0; i < books.size(); i++)
        for (Book b : books) {
            cout << ((b.isAvialable) ? "\e[0;32m" : "\e[0;31m");
            cout << " -Title: " << b.title << endl;
            cout << " -Author: " << b.author << endl;
            cout << " -Description: " << b.description << endl;
            cout << "\e[0;34m************************************************\e[0;37m" << endl;
        }

        cout << "\e[1;37m";
    }

    void searchBook( string entry )
    {
        bool found = false;
        for (Book b : books) {
            if (isIn(entry, b.title) || isIn(entry, b.author) || isIn(entry, b.description)) {
                cout << "\e[0;33m -Title: " << b.title << endl;
                cout << " -Author: " << b.author << endl;
                cout << " -Description: " << b.description << "\e[1;37m" << endl;
                found = true;
            }
        }


        if(!found)
            cout << "\e[0;31mNot Found the book with entry [" << entry << "] :(\e[1;37m" << endl;
    }

    bool addUser( string name , string username , string id )
    {
        for (User u : users) {
            if (u.username == username || u.id == id) {
                return false;
            }
        }
        User u={name, username, id};
        users.push_back(u);
        return true;
    }

    bool deleteUser( string id )
    {
         for (int i = 0; i < users.size(); i++) {
            if (id == users[i].id) {
                users.erase(users.begin() + i);
                return true;
            }
        }

        return false;
    }

    void editUser( string new_name , string new_username , string id )
    {
        for (int i = 0; i < users.size(); i++) {
            if (id == users[i].id) {
                users[i].name = new_name;
                users[i].username = new_username;
                break;
            }
        }
    }

    // file handling functions
     
    void save()
    {
        fstream usersfile(USERS_PATH , ios::out);
        //for (int i=0 ; i<users.size() ; i++)
        for (User u : users){
            usersfile << u.name << "," << u.username << "," << u.id << endl;
        }
        usersfile.close();

        fstream booksfile(BOOKS_PATH , ios::out);
        for (Book b : books){
            booksfile << b.title << "," << b.author << "," << b.description << "," << b.isAvialable << endl;
        }
        booksfile.close();
    }

    void load()
    {
        fstream usersfile(USERS_PATH , ios::in);
        string name,username,id;
        string line;
        while (getline(usersfile, line))
        {
            char* ptr;
            ptr = strtok(&line[0], ",");
            name = ptr;
            ptr = strtok(NULL, ",");
            username = ptr;
            ptr = strtok(NULL, ",");
            id = ptr;
            addUser(name, username, id);
        }
        
        usersfile.close();

        fstream booksfile(BOOKS_PATH , ios::in);
        string title,author,descriptin, avialbility;
        while (getline(booksfile, line))
        {
            char* ptr;
            ptr = strtok(&line[0], ",");
            title = ptr;
            ptr = strtok(NULL, ",");
            author = ptr;
            ptr = strtok(NULL, ",");
            descriptin = ptr;
            ptr = strtok(NULL, ",");
            avialbility = ptr;
            addBook(title, author, descriptin, avialbility == "1");
        }
        
        booksfile.close();
    }


    // System managment
    bool logIn(string username, string id) {
        for (User u : users) {
            if (u.username == username) {
                if (u.id == id)
                    return true;
            }
        }

        return false;
    }

    bool signUp(string name, string username, string id) {
        return addUser(name, username, id);
    }

    // Borrowing System
    bool borrowBook(string title, string userID)
    {
        for (Book& b : books) {
            if (b.title == title && b.isAvialable) {
                b.isAvialable = false;
                b.borrowerID = userID;
                return true;
            }
        }

        return false;
    }
}; 
#endif // LIB_HPP