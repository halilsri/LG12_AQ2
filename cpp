#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char direction;
	int rec_num;
	char letter;
}code_t;

void writeToBin(FILE* inp, FILE* bin_outp)
{
	code_t record;
	while (fscanf(inp, "%c %d %c", &record.direction, &record.rec_num, &record.letter) != EOF)
	{
		fwrite(&record, sizeof(code_t), 1, bin_outp);
	}
}

void move(FILE* bin_inp, code_t record)
{
	do {
		switch (record.direction)
		{
		case 'S':
			printf("%c", record.letter);
			fseek(bin_inp, (record.rec_num - 1) * sizeof(code_t), SEEK_SET);
			fread(&record, sizeof(code_t), 1, bin_inp);
			break;
		case 'C':
			printf("%c", record.letter);
			fseek(bin_inp, (record.rec_num - 1) * sizeof(code_t), SEEK_CUR);
			fread(&record, sizeof(code_t), 1, bin_inp);
			break;
		case 'E':
			printf("%c", record.letter);
			fseek(bin_inp, (-record.rec_num) * sizeof(code_t), SEEK_END);
			fread(&record, sizeof(code_t), 1, bin_inp);
			break;
		}
	} while(!feof(bin_inp) && record.rec_num != - 1);
}

int main(void)
{
	FILE* inp = fopen("input.txt", "r");
	FILE* bin_outp = fopen("bin_outp.bin", "wb");
	if (inp == NULL)
		printf("This file does not exist!");
	else
	{
		writeToBin(inp, bin_outp);
		fclose(inp);
		fclose(bin_outp);

		FILE* bin_inp = fopen("binary.bin", "rb");

		if (bin_inp == NULL)
			printf("This file does not exist!");
		else
		{
			code_t record;
			fseek(bin_inp, 0, SEEK_SET);
			fread(&record, sizeof(code_t), 1, bin_inp);
			move(bin_inp, record);
		}
	}
}
