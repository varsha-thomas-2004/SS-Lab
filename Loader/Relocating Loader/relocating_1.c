#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void convert(char h[12]);
char bitmask[12];
char bit[12] = {0}; //for storing binary form of bitmask

void main()
{
	char input[10], pn[5], add[10], length[10];
	int i, start, address, tlen, len, opcode, addr, actualaddr, relocbit;
	FILE *fp1, *fp2;
	
	printf("Relocating Loader\n");
	
	printf("Enter actual starting address: ");
	scanf("%x", &start);
	
	fp1 = fopen("input1.txt", "r");
	fp2 = fopen("output1.txt", "w");
	
	fscanf(fp1, "%s", input);
	while (strcmp(input, "E") != 0)
	{
		if (strcmp(input, "H") == 0)
		{
			fscanf(fp1, "%s", pn); //name of program
			fscanf(fp1, "%s", add); //address at header record
			fscanf(fp1, "%s", length); //length of text record
			fscanf(fp1, "%s", input); //read next line
		}
		if (strcmp(input, "T") == 0)
		{
			fscanf(fp1, "%x", &address); //memory address given in text record
			fscanf(fp1, "%x", &tlen); //length of line being read
			fscanf(fp1, "%s", bitmask); //obtaining bitmask (FFC)
			address += start;
			convert(bitmask);
			len = strlen(bit);
			if (len >= 11)
				len = 10; //per line can at max consist of 10 bytes
			for (i = 0; i < len; i++)
			{
				fscanf(fp1, "%x", &opcode); //obtaining opcode (14)
				fscanf(fp1, "%x", &addr); //obtaining address next to opcode (0033)
				relocbit = bit[i];
				if (relocbit == '0')
					actualaddr = addr;
				else
					actualaddr = addr + start;
				fprintf(fp2, "\n%x\t\t%x%x", address, opcode, actualaddr);
				address += 3;
			}
			
		}
		fscanf(fp1, "%s", input); //reading next line for continuing the loop
	}
	fclose(fp1);
	fclose(fp2);
	printf("Reading from input file:\n");
	fp1 = fopen("input1.txt", "r");
	char c = fgetc(fp1);
	while (c != EOF)
	{
		printf("%c", c);
		c = fgetc(fp1);
	}
	printf("\n");
	fclose(fp1);
	printf("Reading from output file:\n");
	fp2 = fopen("output1.txt", "r");
	c = fgetc(fp2);
	while (c != EOF)
	{
		printf("%c", c);
		c = fgetc(fp2);
	}
	printf("\n");
	fclose(fp2);
}

void convert(char h[12])
{
	int i, l;
	strcpy(bit, "");
	l = strlen(h);
	for (i = 0; i < l; i++)
	{
		switch(h[i])
		{
			case '0':
				strcat(bit, "0");
				break;
			case '1':
				strcat(bit, "1");
				break;
			case '2':
				strcat(bit, "10");
				break;
			case '3':
				strcat(bit, "11");
				break;
			case '4':
				strcat(bit, "100");
				break;
			case '5':
				strcat(bit, "101");
				break;
			case '6':
				strcat(bit, "110");
				break;
			case '7':
				strcat(bit, "111");
				break;
			case '8':
				strcat(bit, "1000");
				break;
			case '9':
				strcat(bit, "1001");
				break;
			case 'A':
				strcat(bit, "1010");
				break;
			case 'B':
				strcat(bit, "1011");
				break;
			case 'C':
				strcat(bit, "1100");
				break;
			case 'D':
				strcat(bit, "1101");
				break;
			case 'E':
				strcat(bit, "1110");
				break;
			case 'F':
				strcat(bit, "1111");
				break;
		}
	}
}
