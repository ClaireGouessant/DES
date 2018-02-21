#include <iostream>
#include "key_generation.h"
#include "permutations.h"
#include "bit_tables.h"
#include "Split.h"

using namespace std;


/// generate 48 bits subkey keyi
char** generate_key(char* init_key, char* pc_1_left, char* pc_1_right, char* pc_2, char* keyshift)
{
    ///The key is divided in two blocks of 28 bits each
    char *Lkey, *Rkey;
    Lkey = new char[32];
    Rkey = new char[32];
	Lkey = permute(init_key,pc_1_left,28);//The left block L is calculated from the key with the pc_1_left array
	Rkey = permute(init_key,pc_1_right,28);//The right block R is calculated from the key with the pc_1_right array

    /*cout << "clef" << endl;
    displayAsHex(init_key,64);
    cout << "clef gauche" << endl;
	displayAsHex(Lkey,28);
	cout << "clef droite" << endl;
	displayAsHex(Rkey,28);*/

    /// Each of these two blocks is then left shifted by some number of positions, the keyshift table give the left shift offset.
	char **shifted_left;

	shifted_left = shift(Lkey, 28, keyshift, 16);
	/*cout << "clef gauche shift" << endl;
	for(int i = 0; i < 16; i++)
    {
        displayAsHex(shifted_left[i],28);
    }*/


	char **shifted_right;

	shifted_right  = shift(Rkey, 28, keyshift, 16);
	/*cout << "clef droite shift" << endl;
	for(int i = 0; i < 16; i++)
    {
        displayAsHex(shifted_right[i],28);
    }*/

    /// The shifted R block is then appended to the shifted L block
    char** concat = new char*[16];
    for(int i = 0; i < 16; i++)
    {
        concat[i] = concatenate(shifted_left[i], shifted_right[i], 56);
    }

    /// The resulting 48 blocks is finally extracted using the pc_2 array.
    char** result = new char*[16];

    for(int i = 0; i < 16; i++) {
        result[i] = permute(concat[i], pc_2, 48);
    }

    return result;
}
