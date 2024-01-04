// tempdelete.h

#ifndef TEMPDELETE_H
#define TEMPDELETE_H

#include <cstdio>

class TempDelete
{
public:
    void deleteFile()
    {
        char file_link[] = "Admins/temp.txt";

        if (remove(file_link) == 0)
        {
            //
        }
        else
        {
            //
        }
    }
};

#endif
