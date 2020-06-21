#include "mainheader.h"
void saveListToBinFile(char* file_name, boardPosArray* pos_arr);
void printWholes(FILE* file, boardPosArray* pos_arr, int size);
void printRemain(FILE* file, boardPosArray* pos_arr, int size);
unsigned int binaryPos(boardPos* pos);
void main()
{
	boardPosArray CHECK;
	boardPos POS_ARR[7];
	POS_ARR[0][0] = 'A';
	POS_ARR[0][1] = 2;
	POS_ARR[1][0] = 'B';
	POS_ARR[1][1] = 3;
	POS_ARR[2][0] = 'A';
	POS_ARR[2][1] = 1;
	POS_ARR[3][0] = 'A';
	POS_ARR[3][1] = 2;
	POS_ARR[4][0] = 'C';
	POS_ARR[4][1] = 1;
	POS_ARR[5][0] = 'B';
	POS_ARR[5][1] = 2;
	POS_ARR[6][0] = 'B';
	POS_ARR[6][1] = 2;
	CHECK.size = 7;
	CHECK.positions = POS_ARR;
	saveListToBinFile("myfile", &CHECK);
}
void saveListToBinFile(char* file_name, boardPosArray* pos_arr)
{
	FILE* file;
	file = fopen(file_name, "wb");
	assert(file != NULL);
	int size = pos_arr->size;
	fwrite(&size, sizeof(short int), 1, file);
	printWholes(file, pos_arr, size);
	if (isremain)
		printRemain(file, pos_arr, size);
	fclose(file);
}


void printWholes(FILE* file, boardPosArray* pos_arr, int size)
{
	unsigned int fourPoses;
	boardPos* firstPos; boardPos* secondPos; boardPos* thirdPos; boardPos* fourthPos;

	for (short int i = 0; i < size / 4; i++)
	{
		fourPoses = 0;
		short int j = i * 4;
		firstPos = (pos_arr->positions) + j;
		unsigned int firstPosbin = binaryPos(firstPos);
		secondPos = (pos_arr->positions) + j + 1;
		unsigned int secondPosbin = binaryPos(secondPos);
		thirdPos = (pos_arr->positions) + j + 2;
		unsigned int thirdPosbin = binaryPos(thirdPos);
		fourthPos = (pos_arr->positions) + j + 3;
		unsigned int fourthPosbin = binaryPos(fourthPos);
		fourPoses |= (firstPosbin << 26);
		fourPoses |= (secondPosbin << 20);
		fourPoses |= (thirdPosbin << 14);
		fourPoses |= (fourthPosbin << 8);
		fourPoses >>= 8;
		fwrite(&fourPoses, sizeof(char) * 3, 1, file);
	}
}
void printRemain(FILE* file, boardPosArray* pos_arr, int size)
{
	
	short int j = size - size%4;
	boardPos* firstPos;
	firstPos = (pos_arr->positions) + j;
	unsigned int firstPosbin = binaryPos(firstPos);
	unsigned char remainPoses = ((unsigned char)(firstPosbin)) << 2;
	if (remain1)
	{
		fwrite(&remainPoses, sizeof(char), 1, file);
		return;
	}
	boardPos* secondPos;
	secondPos = (pos_arr->positions) + j + 1;
	unsigned int secondPosbin = binaryPos(secondPos);
	secondPosbin = (short int)(secondPosbin << 4);
	short int remainPoses2;
	remainPoses2 = (((short int)(remainPoses)) << 8) | secondPosbin; 
	if (remain2)
	{
		fwrite(&remainPoses2, sizeof(short int), 1, file);
		return;
	}
	boardPos* thirdPos;
	thirdPos = (pos_arr->positions) + j + 2;
	unsigned int thirdPosbin = binaryPos(thirdPos);
	thirdPosbin <<= 6;
	unsigned int remainPoses3;
	remainPoses3 = (((unsigned int)(remainPoses2)) << 8) | thirdPosbin;
	if (remain3)
		fwrite(&remainPoses3, sizeof(char), 3, file);
	return;

}
unsigned int binaryPos(boardPos* pos)
{
	unsigned int res = 0;
	res = (unsigned int)((*pos)[0] - 'A');
	res <<= 3;
	res |= (unsigned int)((*pos)[1] - 1);
	return res;
}