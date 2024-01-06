#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "Modules/tempDelete.h"
#include "Modules/messages.h"
#include "Modules/param_based.h"
#include "Modules/myinv.h"
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
        cout << "Enter Name: ";
        cin >> reg_user;
        cout << "Enter pass: ";
        cin >> pss_user;

        ifstream dupecheck("Admins/registered.txt");
        bool duplicate = false;

        while (dupecheck >> clap)
        {
            if (clap == reg_user)
            {
                duplicate = true;
                break;
            }
        }

        dupecheck.close();

        if (duplicate)
        {
            cout << "Username already exists. Registration failed." << endl;
        }
        else
        {
            registrix << reg_user << " " << pss_user << endl;
            registrix.close();
            cout << "Registration successful!" << endl;
        }
    }
};
class login
{
public:
    string add_user;
    string add_pass;
    bool loginSuccessful;

public:
    void dologin()
    {
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
        add_pass = getPassword();

        ifstream loginFile("Admins/registered.txt");
        string username;
        string password;

        loginSuccessful = false; // Initialize here

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
        }
        else
        {
            cout << "Login failed. Invalid username or password." << endl;
        }
    }

private:
    string getPassword()
    {
        string password;
        char ch;
        while ((ch = _getch()) != 13)
        {
            cout << '*';
            password += ch;
        }
        cout << endl;
        return password;
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
    void firstPhase()
    {
        getRoot();
        cout << endl;
        cout << "Enter your choice: ";
        cin >> optRoot;

        switch (optRoot)
        {
        case 1:
            system("cls");
            dologin();
            break;
        case 2:
            system("cls");
            doregister();
            break;
        case 3:
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

        if (optRoot == 2 && loginSuccessful)
        {
            system("cls");
        }
    }
};

// VIEW module //
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
              system("cls");
              displayPokemonList();
              break;
            case 2:
             system("cls");
             userinv();
                break;
            case 3:
                cout << "Exiting view mode. Returning to main menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (optionForView != 3);
    }
};
// VIEW -INV //

// ADD module
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

// CENTER module
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
            system("cls");
            displayMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case '1':
                system("cls");
                addpoke();
                break;
            case '2':
                system("cls");
                viewpokemon();
                break;
            case '3':

                break;
            case '4':

                break;
            case '5':
                cout << "Exiting .." << std::endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << std::endl;
            }
        } while (choice != '5');
    }
};

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
            system("cls");
            cout << "++--++----------------------+" << endl;
            cout << "|| 1|| Pokemon Operations   |" << endl;
            cout << "|| 2|| Logout               |" << endl;
            cout << "++--++----------------------+" << endl;

            cout << "Enter your choice: ";
            cin >> mainChoice;

            switch (mainChoice)
            {
            case '1':
                system("cls");
                myPokemon.pokemonOperation();
                break;
            case '2':
                tempo.deleteFile();
                cout << "Logging out. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }

        } while (mainChoice != '2');
    }

    return 0;
}
