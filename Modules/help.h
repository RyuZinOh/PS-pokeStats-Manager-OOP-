#ifndef HELP_H
#define HELP_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Helper
{
private:
    string help;

public:
    void showHelp()
    {
        ifstream helpTxt;

        helpTxt.open("./Admins/help.txt");
        if (!helpTxt.is_open())
        {
            cerr << "Error opening help.txt" << endl;
            return;
        }

        while (getline(helpTxt, help))
        {
            cout << help << endl;

            cout << "\n"
                 << "Enter anything to exit: ";
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
               break;
                
            }
        }

        helpTxt.close();
    }
};

#endif
