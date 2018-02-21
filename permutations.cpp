#include "permutations.h"

char* permute(char *table, char *perm_table, long tabsize)
{
    char *result = new char[tabsize];

    for(int i=0; i < tabsize; i++)
    {
        result[i]=table[(int)perm_table[i]-1];
    }

    return result;
}

char** shift(char *key, long key_size, char *shift_table, long tabsize)
{
    char **result = new char*[tabsize];

    for(int i = 0; i < tabsize; i++)
    {
        result[i] = decale(shift_table[i], key, key_size);
    }

    return result;
}

char* decale(int dec, char *key, long key_size)
{
    char *result = new char[key_size];

    for(int i = 0; i < key_size - dec; i++)
    {
        result[i] = key[i + dec];
    }
    for(int i = key_size - dec; i < key_size; i++)
    {
        result[i] = key[i - key_size + dec];
    }

    return result;
}
