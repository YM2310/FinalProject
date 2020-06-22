#include "FullHeader.h"


void saveListToBinFile(char* file_name, boardPosArray* pos_arr) {
	int bit_arr_size = (6 * pos_arr->size / 8) + 1;
	int numbers_size = pos_arr->size*2;
	int bitmap_size;
	int* bitmap = createBitMap(pos_arr,&bitmap_size);
	BYTE* bit_arr = createBitArray(bitmap, bitmap_size, bit_arr_size);

	FILE* bin_file = fopen(file_name, "wb");
	fwrite(&pos_arr->size, sizeof(int), 1, bin_file);
	fwrite(bit_arr, sizeof(bit_arr), 1, bin_file);
	fclose(bin_file);
	return;


}
BYTE* createBitArray(int* arr, int size,int bit_arr_size) {//creates an array of BYTES in binary from a bit map
	BYTE* bit_arr = (BYTE*)malloc(bit_arr_size);

	for (int i = 0; i < bit_arr_size; i++) {
		bit_arr[i] = 0;
	}

	for (int i = 0; i < size; i++) {
		bit_arr[arr[i] / 8] = setBit(bit_arr[arr[i] / 8], arr[i] % 8);
	}

	return bit_arr;
}

BYTE setBit(BYTE byte, int bit) {
	BYTE mask = 1 << (7-bit);
	return byte | mask;
}

int* createBitMap(boardPosArray* pos_arr, int* bitmap_size) {//creates an int array, where each cell contains the position of the next lit bit.
	int* bitmap = (int*)malloc(sizeof(int)*pos_arr->size * 6);
	int bitcounter = 0;
	int j = 0;
	boardPos* numbers_arr = pos_arr->positions;
	for (int i = 0; i < pos_arr->size; i++) {
		for (int flag = 0; flag < 2; flag++) {
			for (int bit = 2; bit > -1; bit--) {
				if (isBitOn((numbers_arr[i][flag]-1), bit)) {
					bitmap[j] = bitcounter;
					j++;
				}
				bitcounter++;
			}

		}
	}
	bitmap = realloc(bitmap, sizeof(int) * j);
	*bitmap_size = j;
	return bitmap;
}

bool isBitOn(unsigned char check, int bit) {
	unsigned char mask = 1 << bit;
	if ((check & mask) == 0)
		return false;
	else
		return true;
}

void bitarraytest(BYTE* bit_arr, int size) {
	int space_count = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 7; j > -1; j--)
		{
			if (space_count % 3 == 0)
				putchar(' ');
			if (isBitOn(bit_arr[i], j))
				putchar('1');
			else
				putchar('0');
			space_count++;
		}
	}

}
