#include "s_box_compute.h"

void fill_blocks(char* block1, char* block2, char* block3, char* block4, char* block5, char* block6, char* block7, char* block8, char* tab)
{
    for(int i= 0; i< 6; i++) {block1[i] = tab[i];}
    for(int i= 6; i<12; i++) {block2[i-6] = tab[i];}
    for(int i=12; i<18; i++) {block3[i-12] = tab[i];}
    for(int i=18; i<24; i++) {block4[i-18] = tab[i];}
    for(int i=24; i<30; i++) {block5[i-24] = tab[i];}
    for(int i=30; i<36; i++) {block6[i-30] = tab[i];}
    for(int i=36; i<42; i++) {block7[i-36] = tab[i];}
    for(int i=42; i<48; i++) {block8[i-42] = tab[i];}
}

void IntToBit(char s_box, char* result)
{
    if(s_box>=8)
    {
        result[0]=(char)1;
        s_box = s_box - 8;
    }
    else{result[0]=(char)0;}

    if(s_box>=4)
    {
        result[1]=(char)1;
        s_box = s_box - 4;
    }
    else{result[1]=(char)0;}

    if(s_box>=2)
    {
        result[2]=(char)1;
        s_box = s_box - 2;
    }
    else{result[2]=(char)0;}

    if(s_box==1){result[3]=(char)1;}
    else{result[3]=(char)0;}
}

char* s_box_compute(char s_box[8][64], char* tab, int length)
{
    char block1[6], block2[6], block3[6], block4[6], block5[6], block6[6], block7[6], block8[6];

    fill_blocks(block1, block2, block3, block4, block5, block6, block7, block8, tab);

    int column1 = (int) ((block1[0]*2 + block1[5])*16 + block1[1]*8 + block1[2]*4 + block1[3]*2 + block1[4]);
    int column2 = (int) ((block2[0]*2 + block2[5])*16 + block2[1]*8 + block2[2]*4 + block2[3]*2 + block2[4]);
    int column3 = (int) ((block3[0]*2 + block3[5])*16 + block3[1]*8 + block3[2]*4 + block3[3]*2 + block3[4]);
    int column4 = (int) ((block4[0]*2 + block4[5])*16 + block4[1]*8 + block4[2]*4 + block4[3]*2 + block4[4]);
    int column5 = (int) ((block5[0]*2 + block5[5])*16 + block5[1]*8 + block5[2]*4 + block5[3]*2 + block5[4]);
    int column6 = (int) ((block6[0]*2 + block6[5])*16 + block6[1]*8 + block6[2]*4 + block6[3]*2 + block6[4]);
    int column7 = (int) ((block7[0]*2 + block7[5])*16 + block7[1]*8 + block7[2]*4 + block7[3]*2 + block7[4]);
    int column8 = (int) ((block8[0]*2 + block8[5])*16 + block8[1]*8 + block8[2]*4 + block8[3]*2 + block8[4]);

    char result1 = s_box[0][column1];
    char result2 = s_box[1][column2];
    char result3 = s_box[2][column3];
    char result4 = s_box[3][column4];
    char result5 = s_box[4][column5];
    char result6 = s_box[5][column6];
    char result7 = s_box[6][column7];
    char result8 = s_box[7][column8];

    char* result = new char[length];

    IntToBit(result1, result);
    IntToBit(result2, &(result[4]));
    IntToBit(result3, &(result[8]));
    IntToBit(result4, &(result[12]));
    IntToBit(result5, &(result[16]));
    IntToBit(result6, &(result[20]));
    IntToBit(result7, &(result[24]));
    IntToBit(result8, &(result[28]));

    return result;
}
