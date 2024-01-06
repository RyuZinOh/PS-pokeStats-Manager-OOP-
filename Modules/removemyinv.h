// removemyinv.h

#ifndef REMOVEMYINV_H
#define REMOVEMYINV_H

#include <iostream>
#include <fstream>
#include <iomanip>

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

    while (true)
    {
        ifstream pokemonFilex("./Assets/poke_base.dat");
        system("cls");
        int num = 1;

        cout << setw(3) << "ID  " << setw(15) << left << setw(15) << "Name" << setw(15) << "Type" <<  endl;
        cout << "+------------------+---------------+--------+" << endl;

        while (pokemonFilex >> name >> spdiv >> atk >> spatk >> spdef >> def >> hp >> iv >> type >> user)
        {
            if (user == user_name)
            {
                cout << setw(3) << num << setw(15) << left << setw(15) << name << setw(15) << type << endl;
                num++;
            }
        }

        pokemonFilex.close();

        // Ask the user for the number to delete
        int deleteNum;
        cout << "Enter the number of the Pokémon to delete (or 0 to exit): ";
        cin >> deleteNum;

        if (deleteNum == 0)
        {
            break; // Exit the loop if the user enters -1
        }

        // Reopen the file to perform deletion
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
                // Preserve Pokémon of other users
                outFile << name << " " << spdiv << " " << atk << " " << spatk << " " << spdef << " " << def << " " << hp << " " << iv << " " << type << " " << user << "\n";
            }
        }

        inFile.close();
        outFile.close();

        // Remove the original file and rename the temp file
        remove("./Assets/poke_base.dat");
        rename("./Assets/temp.dat", "./Assets/poke_base.dat");

        cout << "Pokémon deleted successfully.\n";
    }
}

#endif
