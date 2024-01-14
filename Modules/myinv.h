#ifndef MYINV_H
#define MYINV_H

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

void userinv()
{
    string name;
    int spdiv;
    int atk;
    int spatk;
    int spdef;
    int def;
    int hp;
    int iv;
    string type;
    string user;

    ifstream openuser;
    openuser.open("./Admins/temp.txt");

    string username;
    getline(openuser, username);
    openuser.close();

    ifstream pokemonFile("./Assets/poke_base.dat");
    string line;
    system("cls");

    bool foundPokemon = false; //
    int num = 1;

    while (true)
    {
        cout << left << setw(15) << "S.N" << setw(10) << "NAME" << setw(5) << "TYPE" << endl;
        cout << "+-------------------+---------------+" << endl;
        while (pokemonFile >> name >> spdiv >> atk >> spatk >> spdef >> def >> hp >> iv >> type >> user)
        {
            if (user == username)
            {
                cout << left << setw(15) << num << setw(10) << name << setw(5) << type << endl;
                foundPokemon = true;  
                num++;
            }
        }

        pokemonFile.clear();
        pokemonFile.seekg(0, ios::beg);

        if (!foundPokemon)
        {
            cout << "No Pokemon in inventory for user: " << username << endl;
        }

        cout << "\n"
             << "Enter [exit] to exit: ";
        string choice;
        cin >> choice;

        if (choice == "exit")
        {
            system("cls");
            break;
        }
        else
        {
            system("cls");
            cout << endl;
            cout << "Invalid choice";
        }
    }

    pokemonFile.close();
}

#endif
