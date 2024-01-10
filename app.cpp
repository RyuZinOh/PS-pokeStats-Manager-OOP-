#include <iostream>
#include <fstream>
#include <string>
#include <ncurses.h> //conio.h in linux
#include <cctype>
#include <unistd.h>
#include "Modules/tempDelete.h"
#include "Modules/messages.h"
#include "Modules/param_based.h"
#include "Modules/myinv.h"
#include "Modules/help.h"
// Remove-module-->implemted on header file
#include "Modules/removemyinv.h"
using namespace std;

//----ADMIN-SECTION----//
class registration
{
private:
    string reg_user;
    string pss_user;

public:
    void doregister()
    {
        ifstream regUI;
        string regui;
        regUI.open("Assets/register.ui");
        while (getline(regUI, regui))
        {
            cout << regui << endl;
        }
        regUI.close();
        cout << endl;
        string clap;
        ofstream registrix("Admins/registered.txt", ios::app);
        bool validUsername = false;

        do
        {
            cout << "Enter Username : ";
            cin >> reg_user;

            
            validUsername = lowerwhat(reg_user);

            if (!validUsername)
            {
                cout << "Invalid username format. Please use only lowercase letters and numbers." << endl;
            }
            else if (usernameexists())
            {
                cout << "Username already exists. Please choose a different one." << endl;
                validUsername = false; 
            }

        } while (!validUsername);

        cout << "Enter Password: ";
        cin >> pss_user;

        registrix << reg_user << " " << pss_user << endl;
        registrix.close();
        cout << "Registration successful!" << endl;
        exit(0);
    }

private:
    bool lowerwhat(const string &str)
    {
        for (char ch : str)
        {
            if (!islower(ch) && !isdigit(ch))
            {
                return false;
            }
        }
        return true;
    }

    bool usernameexists()
    {
        ifstream dupecheck("Admins/registered.txt");
        string existingUsername, existingPassword;

        while (dupecheck >> existingUsername >> existingPassword)
        {
            if (existingUsername == reg_user)
            {
                dupecheck.close();
                return true;
            }
        }

        dupecheck.close();
        return false;
        
    }
};
class login
{
private:
    string add_user;
    string add_pass;

public:
    bool loginSuccessful;

    void dologin()
    {
        int attempts = 0;
        const int maxAttempts = 3;

        do
        {
            system("clear");
            ifstream logUI;
            string logui;
            logUI.open("Assets/login.ui");
            while (getline(logUI, logui))
            {
                cout << logui << endl;
            }
            logUI.close();
            cout << endl;

            cout << "Enter Username: ";
            cin >> add_user;

            cout << "Enter Password: ";
            cin >> add_pass;
            cout << endl;

            ifstream loginFile("Admins/registered.txt");
            string username;
            string password;

            loginSuccessful = false;

            while (loginFile >> username >> password)
            {
                if (username == add_user && password == add_pass)
                {
                    loginSuccessful = true;
                    break;
                }
            }

            loginFile.close();

            if (loginSuccessful)
            {
                cout << "Login successful!" << endl;

                // note:-> creating user instance//
                ofstream tempFile("Admins/temp.txt");
                tempFile << add_user;
                tempFile.close();

                sleep(1);
            }
            else
            {
                attempts++;

                cout << "Login failed. Invalid username or password." << endl;

                if (attempts < maxAttempts)
                {
                    cout << "You have " << maxAttempts - attempts << " attempts remaining." << endl;
                }
                else
                {
                    cout << "Maximum login attempts reached. Exiting program." << endl;
                    exit(0);
                }

                sleep(1);
            }
        } while (!loginSuccessful && attempts < maxAttempts);
    }
};

class root : public registration, public login
{
private:
    int optRoot;

    void getRoot()
    {
        ifstream rootUI;
        string rootUIString;
        rootUI.open("Assets/root.ui");
        while (getline(rootUI, rootUIString))
        {
            cout << rootUIString << endl;
        }
        rootUI.close();
    }

public:
    Helper amazing;
    void firstPhase()
    {
        do
        {
            system("clear");
            getRoot();
            cout << endl;
            cout << "Enter your choice: ";
            cin >> optRoot;

            switch (optRoot)
            {
            case 1:
                system("clear");
                dologin();
                break;
            case 2:
                system("clear");
                doregister();
                break;
            case 3:
                system("clear");
                amazing.showHelp();
                exit(0);
                break;
            case 4:
                cout << "Exiting the program. Goodbye!" << endl;
                sleep(1);
                exit(0);
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                sleep(1);
            }

        } while (optRoot < 1 || optRoot > 4);

        if (optRoot == 2 && loginSuccessful)
        {
            system("clear");
        }
    }
};

//VIEW module//
class PokemonView
{
private:
    void viewMenu()
    {
        ifstream viewMenuFile;
        viewMenuFile.open("Assets/pokeview.ui");
        string line;

        while (getline(viewMenuFile, line))
        {
            cout << line << endl;
        }

        viewMenuFile.close();
    }

public:
    void viewpokemon()
    {
        int optionForView;
        do
        {
            viewMenu();
            cout << "Enter your choice: ";
            cin >> optionForView;

            switch (optionForView)
            {
            case 1:
                system("clear");
                displayPokemonList();
                break;
            case 2:
                system("clear");
                userinv();
                break;
            case 3:
                cout << "Exiting view mode. Returning to main menu." << endl;
                sleep(1);
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                sleep(1);
            }
        } while (optionForView != 3);
    }
};
//ADD module//
class pokemonadd
{
private:
    string name;
    string type;
    string addername;
    int spdiv, atk, spatk, spdef, def, hp, iv;
    string getuserfromtemp;
    void addMenu()
    {
        ifstream addMenuFile;
        addMenuFile.open("Assets/pokeadd.ui");
        string line;

        while (getline(addMenuFile, line))
        {
            cout << line << endl;
        }

        addMenuFile.close();
    }

public:
    void addpoke()
    {
        ifstream openuser;

        openuser.open("Admins/temp.txt");
        getline(openuser, getuserfromtemp);
        openuser.close();
        addMenu();
        ofstream poke("Assets/poke_base.dat", ios::app);
        cout << "Enter Pokemon name: ";
        cin >> name;
        cout << "Enter Pokemon speed: ";
        cin >> spdiv;
        cout << "Enter Pokemon attack: ";
        cin >> atk;
        cout << "Enter Pokemon special attack: ";
        cin >> spatk;
        cout << "Enter Pokemon special defense: ";
        cin >> spdef;
        cout << "Enter Pokemon defense: ";
        cin >> def;
        cout << "Enter Pokemon HP: ";
        cin >> hp;
        cout << "Enter Pokemon IV: ";
        cin >> iv;
        cout << "Enter Pokemon TYPE: ";
        cin >> type;

        poke << name << '\t' << spdiv << '\t' << atk << '\t' << spatk << '\t'
             << spdef << '\t' << def << '\t' << hp << '\t' << iv << '\t' << type << '\t' << getuserfromtemp << '\n';
        Messages::showPokemonAddedMessage();
        poke.close();

        if (Messages::askToAddAnotherPokemon())
        {
            addpoke();
        }
    }
};

//~~ CENTER module ~~//
class Pokemon : public root, public pokemonadd, public PokemonView
{
private:
    void displayMenu()
    {
        ifstream mainmenu;
        mainmenu.open("Assets/pokecenter.ui");
        string line;
        while (getline(mainmenu, line))
        {
            cout << line << endl;
        }

        mainmenu.close();
    }


public:
  
    void pokemonOperation()
    {

        char choice;
        do
        {
            system("clear");
            displayMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case '1':
                system("clear");
                addpoke();
                break;
            case '2':
                system("clear");
                viewpokemon();
                break;
            case '3':
                system("clear");
                remove_inv();
                break;
            case '4':
                cout << "Exiting .." << endl;
                sleep(1);
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                sleep(1);
            }
        } while (choice != '4');
    }
};

//------MAIN FUNCTION-----//
int main()
{
    TempDelete tempo;
    Pokemon myPokemon;
    root check;

    check.firstPhase();

    if (check.loginSuccessful)
    {
        char mainChoice;
        do
        {
            system("clear");
            cout << "++--++----------------------+" << endl;
            cout << "|| HOME PAGE [pokemon]      |" << endl;
            cout << "++--++----------------------+" << endl;
            cout << "|| 1|| Pokemon Operations   |" << endl;
            cout << "|| 2|| Logout               |" << endl;
            cout << "++--++----------------------+" << endl;

            cout << "Enter your choice: ";
            cin >> mainChoice;

            switch (mainChoice)
            {
            case '1':
                system("clear");
                myPokemon.pokemonOperation();
                break;
            case '2':
                tempo.deleteFile();
                cout << "Logging out. Goodbye!" << endl;
                sleep(1);
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                sleep(1);
            }

        } while (mainChoice != '2');
    }

    return 0;
}
