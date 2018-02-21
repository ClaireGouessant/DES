#ifndef PERMUTATIONS_H_INCLUDED
#define PERMUTATIONS_H_INCLUDED

char* permute(char *, char *, long);

char** shift(char *key, long key_size, char *shift_table, long tabsize);

char* decale(int dec, char *key, long key_size);

#endif // PERMUTATIONS_H_INCLUDED
