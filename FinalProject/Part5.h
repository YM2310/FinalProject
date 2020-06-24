#pragma once
#include "Structs.h"


void saveListToBinFile(char* file_name, boardPosArray* pos_arr);
BYTE setBit(BYTE destination, int bit);
BYTE* createBitArray(int* arr, int size, int bit_arr_size);
int* createBitMap(boardPosArray* pos_arr, int* bitmap_size);
bool isBitOn(unsigned char check, int bit);
void bitarraytest(BYTE* bit_arr, int size);