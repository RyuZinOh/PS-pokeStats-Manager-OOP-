// removemyinv.h

#ifndef REMOVEMYINV_H
#define REMOVEMYINV_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h> 
using namespace std;

void remove_inv()
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

    ifstream removecontent;
    removecontent.open("./Admins/temp.txt");

    string user_name;
    getline(removecontent, user_name);
    removecontent.close();

    bool pokemonFound = false;

    while (true)
    {
        ifstream pokemonFilex("./Assets/poke_base.dat");
        system("clear");
        int num = 1;

        cout << setw(3) << "ID  " << setw(15) << left << setw(15) << "Name" << setw(15) << "Type" << endl;
        cout << "+------------------+---------------+--------+" << endl;

        while (pokemonFilex >> name >> spdiv >> atk >> spatk >> spdef >> def >> hp >> iv >> type >> user)
        {
            if (user == user_name)
            {
                cout << setw(3) << num << setw(15) << left << setw(15) << name << setw(15) << type << endl;
                num++;
                pokemonFound = true;
            }
        }

        pokemonFilex.close();

        if (!pokemonFound)
        {
            cout << "You don't have any Pokemon entered yet. Please add them first." << endl;
            sleep(1);
            break;
        }

        
        int deleteNum;
        cout << "Enter the number of the Pokemon to delete (or 0 to exit): ";
        cin >> deleteNum;

        if (deleteNum == 0)
        {
            break;
        }

        
        if (deleteNum < 1 || deleteNum >= num)
        {
            cout << "Error: Invalid number entered. Please enter a valid number." << endl;
            sleep(2);
            continue;
        }
        ifstream inFile("./Assets/poke_base.dat");
        ofstream outFile("./Assets/temp.dat");

        int currentNum = 1;
        while (inFile >> name >> spdiv >> atk >> spatk >> spdef >> def >> hp >> iv >> type >> user)
        {
            if (user == user_name)
            {
                if (currentNum != deleteNum)
                {
                    outFile << name << " " << spdiv << " " << atk << " " << spatk << " " << spdef << " " << def << " " << hp << " " << iv << " " << type << " " << user << "\n";
                }
                currentNum++;
            }
            else
            {
                // ignore additionof  other users
                outFile << name << " " << spdiv << " " << atk << " " << spatk << " " << spdef << " " << def << " " << hp << " " << iv << " " << type << " " << user << "\n";
            }
        }

        inFile.close();
        outFile.close();
        remove("./Assets/poke_base.dat");
        rename("./Assets/temp.dat", "./Assets/poke_base.dat");

        cout << "Pokémon deleted successfully.\n";
        sleep(1);
    }
}

#endif
