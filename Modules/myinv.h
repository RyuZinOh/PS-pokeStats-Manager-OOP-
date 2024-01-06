#ifndef MYINV_H
#define MYINV_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
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

    while (true)
    {
        cout << left << setw(15) << "Name" << setw(10) << "Type" << setw(5) << "HP" << endl;
        cout <<"+-------------------+---------------+" << endl;
        while (pokemonFile >> name >> spdiv >> atk >> spatk >> spdef >> def >> hp >> iv >> type >> user)
        {
            if (user == username)
            {
                cout << left << setw(15) << name << setw(10) << type << setw(5) << hp << endl;
            }
        }

        pokemonFile.clear();            
        pokemonFile.seekg(0, ios::beg); 

        cout <<"\n"<< "Enter [exit] to exit: ";
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
            cout << "invalid";
        }
    }

    pokemonFile.close();
}

#endif
