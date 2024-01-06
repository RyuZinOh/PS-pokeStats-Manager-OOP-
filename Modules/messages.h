// Messages.h

#ifndef MESSAGES_H
#define MESSAGES_H

#include <iostream>

namespace Messages {
    void showPokemonAddedMessage() {
        std::cout << "Pokemon successfully registered!" << std::endl;
    }

    bool askToAddAnotherPokemon() {
        char choice;
        std::cout << "Do you want to add another Pokemon? (y/n): ";
        std::cin >> choice;
        return (choice == 'y' || choice == 'Y');
    }
}

#endif 
