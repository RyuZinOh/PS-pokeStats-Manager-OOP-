#ifndef PARAM_BASED_H
#define PARAM_BASED_H

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

struct PokemonData
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
    string ownerName;
};

void displayPokemonDetails(int pokemonID)
{
    ifstream pokeFile("./Assets/poke_base.dat");

    if (!pokeFile)
    {
        cerr << "Error opening Pokemon data file." << endl;
        return;
    }

    int currentPokemonID = 1;
    PokemonData pokemon;

    while (pokeFile >> pokemon.name >> pokemon.spdiv >> pokemon.atk >> pokemon.spatk >> pokemon.spdef >> pokemon.def >> pokemon.hp >> pokemon.iv >> pokemon.type >> pokemon.ownerName)
    {
        if (currentPokemonID == pokemonID)
        {
            system("cls");
            cout << "-------+--------+---------+" << endl;
            cout << "POKEMON DETAILS FOR ID " << pokemonID << endl;
            cout << "-------+-------+----------+" << endl;
            cout << "NAME:              " << pokemon.name << endl;
            cout << "TYPE:              " << pokemon.type << endl;
            cout << "OWNER:             " << pokemon.ownerName << endl;
            cout << "--------+----------+-----+" << endl;
            cout << "HP:                " << pokemon.hp << "/31" << endl;
            cout << "ATTACK:            " << pokemon.atk << "/31" << endl;
            cout << "DEFENCE:           " << pokemon.def << "/31" << endl;
            cout << "SPECIAL ATTACK:    " << pokemon.spatk << "/31" << endl;
            cout << "SPECIAL DEFENCE:   " << pokemon.spdef << "/31" << endl;
            cout << "SPEED :            " << pokemon.spdiv << "/31" << endl;
            cout << "--------+----------+-----+" << endl;        
            cout << "IV:                " << pokemon.iv << "%" << endl;
            cout << "--------+----------+-----+" << endl;

            break;
        }

        currentPokemonID++;
    }

    pokeFile.close();
}

void displayPokemonList()
{
    while (true)
    {
        ifstream pokeFile("./Assets/poke_base.dat");
        int number = 1;
        PokemonData pokemon;

        cout << endl;
        system("cls");
        cout << left << setw(8) << "Number" << left << setw(15) << "Name" << left << setw(8) << "IV %" << left << setw(15) << "Owner Name" << endl;
        cout << "+--------------+---------+-------------+" << endl;

        while (pokeFile >> pokemon.name >> pokemon.spdiv >> pokemon.atk >> pokemon.spatk >> pokemon.spdef >> pokemon.def >> pokemon.hp >> pokemon.iv >> pokemon.type >> pokemon.ownerName)
        {
            // Display data with mixed alignments
            cout << left << setw(8) << number << left << setw(15) << pokemon.name << left << setw(8) << pokemon.iv << setw(15) << pokemon.ownerName << endl;

            number++;
        }

        pokeFile.close();

        // Ask the user to enter a Pokemon ID to view detailed information or exit
        int selectedPokemonID;
        cout << "+++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "Enter Pokemon ID to view details: ";
        cin >> selectedPokemonID;

        // Display detailed information for the selected Pokemon
        displayPokemonDetails(selectedPokemonID);

        // Ask if the user wants to enter another ID
        char choice;
        cout << "Do you want to enter another ID? (y/n): ";
        cin >> choice;

        if (choice != 'y' && choice != 'Y')
        {
            break;
        }
    }
}

#endif
