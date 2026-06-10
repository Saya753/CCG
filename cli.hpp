#ifndef CLI_HPP
#define CLI_HPP

#include <iostream>

#include "lib.hpp"

using namespace std;

struct cli
{
    Lib lib;

    string userName, userID;

    void init()
    {
        lib.name = "CCG";
        lib.operationhour = "8:00AM-8:00PM";
        lib.load();

        cout << "\e[0;34m##Welcome to CCG##\e[0;37m" << endl;
        cout << "\e[0;32m(1) Log IN        \e[0;35m(2) Sign Up\e[0;37m" << endl;
        int choice = 0;
        while (choice != 1 && choice != 2) {
            cin >> choice;
        }

        if (choice == 1) {
            string username, id;
            while (true)
            {          
                cout << "\e[0;32m -Username: ";
                cout << "\e[0;33m"; 
                cin >> username;
                cout << "\e[0;32m -Id: ";
                cout << "\e[0;33m";
                cin >> id;
                cout << "\e[0;37m";
                if (lib.logIn(username, id)) {
                    cout << "\e[0;34mLog in Successful!" << endl;
                    userName = username;
                    userID = id;
                    break;
                }
                else {
                    cout << "\e[0;31mWrong Cridintial! Try Again!\e[0;37m" << endl;
                }
            }
        } 
        else if (choice == 2) {
            string username, id, name;
            while (true)
            {          
                cout << "\e[0;32m -Name: ";
                cout << "\e[0;33m"; 
                cin >> name;
                cout << "\e[0;32m -Username: ";
                cout << "\e[0;33m";
                cin >> username;
                cout << "\e[0;32m -Id: ";
                cout << "\e[0;33m";
                cin >> id;
                cout << "\e[0;37m";
                if (lib.signUp(name, username, id)) {
                    cout << "\e[0;34mSign Up Successful!" << endl;
                    userName = username;
                    userID = id;
                    break;
                }
                else {
                    cout << "\e[0;31mWrong Cridintial! Try Again!\e[0;37m" << endl;
                }
            }
        }       
    }

    void help()
    {
        cout << "\e[0;33m -help ==> Showing this message" << endl;
        cout << " -show books ==> Showing the list of books" << endl;
        cout << " -search book ==> Searching for a book in the list" << endl;
    }

    void quit()
    {
        cout << "\e[0;31m##Thanks for using our System. Good Luck!##\e[0;37m" << endl;
        exit(0);
    }

    void run()
    {
        init();
        string prompt;
        cin.ignore();
        while (true) {
            cout << "\e[0;32m>>> \e[0;37m";
            getline(cin, prompt);

            if (prompt == "help") {
                help();
            }
            else if (prompt == "quit" || prompt == "exit") {
                lib.save();
                quit();
            }
            else if (prompt == "show books") {
                lib.showBooks();
            }
            else if (prompt == "search book") {
                cout << "\e[0;33mentry:\e[0;37m";
                string entry;
                getline(cin, entry);
                lib.searchBook(entry);
            }
            else if (prompt == "add book") {
                string title, author, description;
                cout << "\e[0;33m-Title: ";
                getline(cin, title);
                cout << "-Author: ";
                getline(cin, author);
                cout << "-Description: ";
                getline(cin, description);
                lib.addBook(title, author, description, true);
                cout << "\e[0;32m##Book added successfuly##\e[0;37m" << endl;
            }
            else if (prompt == "delete book") {
                string title;
                cout << "\e[0;33m-Title:\e[0;37m";
                getline(cin, title);
                lib.deleteBook(title);
            }
            else if (prompt == "borrow book"){
                string title;
                cout << "\e[0;33m-Title: \e[0;37m";
                getline(cin, title);
                if (lib.borrowBook(title, userID)) {
                    cout << "\e[0;32m##Book is Borrowed!##\e[0;37m" << endl;
                }
                else {
                    cout << "\e[0;31m##Book is unAvailble or Does not exist!##\e[0;37m" << endl;
                }
            }
            else if (prompt == "edit user") {
                string new_name, new_username, id;
                cout << "\e[0;33m-New-name: ";
                getline(cin, new_name);
                cout << "-New_username: ";
                getline(cin, new_username);
                cout << "-Id:\e[0;37m ";
                getline(cin, id);
                lib.editUser(new_name,new_username,id);
            }
            else {
                cout << "\e[0;31mInvalid Input!\e[0;37m" << endl;
            }
        }
    }
};


#endif