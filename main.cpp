#include <iostream>
#include "permutations.h"
#include "bit_tables.h"
#include "data_tables.h"
#include "Split.h"
#include "data_messages_examples.h"
#include "key_generation.h"
#include "ou_exclusif.h"
#include "s_box_compute.h"

using namespace std;

char* round(char* Li, char* Ri, char* Key);

int main()
{
    /// Let M be the original message (64 bits block to cipher)
    char* M = message_03;

    cout << "Message\t";
    displayBitTable(M, 64);
    displayAsHex(M, 64);

    /// Let K be the key chosen
    char* K = key_1;
    cout << "Key\t" << endl;
    displayBitTable(K, 64);
    displayAsHex(K, 64);

    /// M is shuffled using an initial permutation (init_perm array)
    char *firstperm;
    firstperm=permute(M,init_perm, 64);
    cout << "Permute\t";
    displayBitTable(firstperm, 64);
    displayAsHex(firstperm, 64);

    /// The resulting block is split in two 32-bit blocks: L0 and R0
    char *L0, *R0;
    L0 = new char[32];
    R0 = new char[32];
	split(firstperm, L0, R0, 64);
    /*cout << "L0\t";
	displayBitTable(L0, 32);
    displayAsHex(L0, 32);
    cout << "R0\t";
    displayBitTable(R0, 32);
    displayAsHex(R0, 32);*/

    /// generate 48 bits subkeys
    char** keys = generate_key(K, pc_1_left, pc_1_right, pc_2, keyshift);

    cout << "Keys" << endl;
    for(int i = 0; i < 16; i++)
    {
        //displayBitTable(keys[i], 48);
        cout << i << ". ";
        displayAsHex(keys[i], 48);
    }

    /// 16 rounds
    char* L = L0;
    char* R = R0;

    for(int i = 0; i < 16 ; i++)
    {
        /*cout << "L" << i << "\t";
        displayBitTable(L, 32);
        displayAsHex(L, 32);
        cout << "R" << i << "\t";
        displayBitTable(R, 32);
        displayAsHex(R, 32);*/

        char* tmp = R;
        R = round(L, R, keys[i]);
        L = tmp;
    }
    cout << endl;

    /// L16 is appended to R16
    char* concat = concatenate(R, L, 64);

    cout << "Concat\t";
    displayBitTable(concat, 64);
    displayAsHex(concat, 64);

    /// a reverse permutation is done (reverse_perm array)
    char* result = permute(concat, reverse_perm, 64);

    cout << "Result\t";
    displayBitTable(result, 64);
    displayAsHex(result, 64);
}

char* round(char* Li, char* Ri, char* Keyi)
{
    cout << "------------------------------------------" << endl;
    /// expand Ri using the E table (expansion_table array)
    char *expanded;
    expanded = permute(Ri, expansion_table, 48);
    cout << "Exp ";
    displayBitTable(expanded,48);
    displayAsHex(expanded,48);

    /// operate a XOR between expanded version of Ri and keyi
    char* XOR1 = new char[48];
    XOR1 = ou_exclusif(expanded, Keyi, 48);
    cout << "XOR ";
    displayBitTable(XOR1, 48);
    displayAsHex(XOR1, 48);

    /// input the 48 bit computed value at step 2.3 to the ith S-Box (s_boxes array), get the 32 bits output
    char* S = s_box_compute(s_boxes, XOR1, 32);
    cout << "sbox\t";
    displayBitTable(S, 32);
    displayAsHex(S, 32);

    /// permute the previous result (permut_32 array)
    char *P = permute(S, permut_32, 32);
    cout << "P32\t";
    displayBitTable(P, 32);
    displayAsHex(P, 32);

    /// operate a XOR between the result and Li
    char* XOR2 = ou_exclusif(P, Li, 32);
    /*cout << "XOR2\t";
    displayBitTable(XOR2, 32);
    displayAsHex(XOR2, 32);*/

    return XOR2;
}
