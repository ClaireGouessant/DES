#include "Split.h"

void split(char *firstperm, char *L0, char *R0, long tabsize)
{
    for(int i = 0; i < tabsize/2; i++)
    {
        (L0)[i] = firstperm[i];
    }

    for(int i = tabsize/2; i < tabsize; i++)
    {
        (R0)[i - tabsize/2] = firstperm[i];
    }

    return;
}

char* concatenate(char* L, char* R, long t_size)
{
    char* result = new char[t_size];

    for(int i = 0; i < t_size/2; i++)
    {
        result[i] = L[i];
    }
    for(int i = 0; i < t_size/2; i++)
    {
        result[i + t_size/2] = R[i];
    }
    return result;
}
