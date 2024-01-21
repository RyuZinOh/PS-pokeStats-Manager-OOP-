#ifndef HELP_H
#define HELP_H

#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>

using namespace std;

class Helper
{
private:
    string line;

public:
void showHelp()
{
    ifstream helpTxt("./Admins/help.txt");
    cout << "loading";
    for (int i =0 ; i < 5 ; i++){
        sleep(1);
        cout << ".";
    }
    system("cls");
    while (getline(helpTxt, line))
    {
        cout << line << endl;
    }

    cout << "\nEnter anything to exit: ";
    string choice;
    cin >> choice;

    if (choice != "exit")
    {
        system("cls");
        sleep(1);
        cout << endl;
    }

    helpTxt.close();
}
};

#endif
