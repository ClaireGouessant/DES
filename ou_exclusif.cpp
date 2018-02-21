#include "ou_exclusif.h"

char* ou_exclusif(char* tb1, char* tb2, int length)
{
    char *result = new char[length];

    for(int i=0; i<length; i++)
    {
        if(tb1[i] == tb2[i])
        {
            result[i] = 0;
        }
        else
        {
           result[i] = 1;
        }
    }

    return result;
}

