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
#include "manager.hpp"

#define USERS_PATH "users.txt"
#define BOOKS_PATH "books.txt"
#define MANAGER_PATH "managers.txt"

using namespace std;

struct Lib{
    string name;
    string operationhour; 
    vector<Book> books;
    vector<User> users;
    vector<Manager> managers;

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

    bool addManager( string managername, string password) 
    {
        for (Manager u : managers) {
            if (u.managername == managername || u.password == password) {
                return false;
            }
        }
        Manager m={managername, password}
        managers.push_back(m);
        return true;
    }

    // file handling functions
    void save()
    {
        fstream usersfile(USERS_PATH , ios::out);
        //for (int i=0 ; i<users.size() ; i++)
        for (User u : users) {
            usersfile << u.name << "," << u.username << "," << u.id << endl;
        }
        usersfile.close();

        fstream booksfile(BOOKS_PATH , ios::out);
        for (Book b : books) {
            booksfile << b.title << "," << b.author << "," << b.description << "," << b.isAvialable << endl;
        }
        booksfile.close();

        fstream managersfile(MANAGER_PATH , ios::out);
        for (Manager m : managers) {
            managersfile << m.managername << "," << m.password << endl;
        }
        managersfile.close();
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

        fstream managersfile(MANAGER_PATH , ios::in);
        string managername,password;
        while (getline(managersfile, line))
        {
            char* ptr;
            ptr = strtok(&line[0], ",");
            managername = ptr;
            ptr = strtok(NULL, ",");
            password = ptr;
        }
    }

    // System managment for user
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

    // System management for manager
    bool logIn(string managername, string password) {
        for (Manager m : managers) {
            if (m.managername == managername) {
                if (m.password == password)
                    return true;
            }
        }

        return false;
    }

    bool signUp(string managername, string password) {
        return addManager(managername, password);
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

    bool returnBook(string title, string userID)
    {
        for (Book& b : books) {
            if (b.title == title && !b.isAvialable) {
                b.isAvialable = true;
                addBook(b.title, b.author, b.description, b.isAvialable);
                return true;
            }
        }
        return false;
    }

     void managmentMenu(vector<Book>& books, vector<User>& users){

        cout << "1:Add a book" << endl;
        cout << "2:Delete a book" << endl;
        cout << "3:Add a user" << endl;
        cout << "4:Delete a user" << endl;
        cout << "Enter a number:" << endl;

        int choice1;
        cin >> choice1;

        switch (choice1)
        {
        case 1:
            addBook(title, author, description);
            break;
        case 2:
            deleteBook(title);
            break;
        case 3:
            addUser(name, username, id);
            break;
        case 4:
            deleteUser(id);
            break;
        default:
            cout<<"please enter the valid number!!!"<<endl;
            continuePrompt();
            managmentMenu(books,users);
            break;
        }
    }

void userMenu(vector<Book>& book, vector<User>& user){

    cout << "1:add book" << endl;
    cout << "2:edit user" << endl;
    cout << "3:borrow book" << endl;
    cout << "4:return book" << endl;
    cout << "enter a number:" << endl;
    
    int choice2;
    cin >> choice2;

    switch (choice2)
    {
    case 1:
       addBook(title, author, descrption);
        break;
    case 2:
        editUser(new_name, new_username, id);
        break;
    case 3:
        borrowBook(title, userID);
        break;
    case 4:
        returnBook(title, userID);
        break;
    default:
        cout<<"please enter the valid number!!!"<<endl;
        continuePrompt();
        userMenu(books,users);
        break;
    }
}
}; 
#endif // LIB_HPP