#ifndef HELP_H
#define HELP_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Helper
{
private:
    string line;

public:
void showHelp()
{
    ifstream helpTxt("./Admins/help.txt");
    
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
        cout << endl;
    }

    helpTxt.close();
}
};

#endif
