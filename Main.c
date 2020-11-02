#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char* readSentence(int* konecSouboru);
int compareStr(const void* a, const void* b) {
	const char** str1 = (const char**)a;
	const char** str2 = (const char**)b;

	return strcmp(*str1,*str2);
}
char** readInput(char** pole, int* delkaPole) {
	int isEOF=0;
	char* veta;
	while (isEOF == 0) {
		veta = readSentence(&isEOF);
		if (isEOF == 1) {
			free(veta);
			break;
		}
		if (*delkaPole == 0)
			pole = (char**)malloc(sizeof(char*));
		else pole = (char**)realloc(pole, sizeof(char*) * (*delkaPole + 1));
		pole[*delkaPole] = veta;
		(*delkaPole)++;
	}
	return pole;
}

char* readSentence(int* konecSouboru) {
	char* veta;
	int znak;
	veta = (char*)malloc(sizeof(char));
	veta[0] = '\0';
	int delkaVety = 1;
	int isZavorka = 0;
	while ((znak = getchar()) && znak != EOF) {
		if (delkaVety == 1 && isspace((char)znak))
			continue;
		if ( znak == '(' || znak == ')')
			continue;
		veta = (char*)realloc(veta, sizeof(char) * (delkaVety + 1));
		veta[delkaVety-1] = znak;
		veta[delkaVety] = '\0';
		delkaVety++;
		if ((znak == '.' || znak =='\t' || znak == '\n'|| znak == '!' || znak == '?') && isZavorka == 0)
			break;
		if (isZavorka == 1 && znak == ')')
			break;
	}
	if (znak == EOF)
		*konecSouboru = 1;
	return veta;
}

int main(int argc, char** argv) {
	char** poleVet=NULL;
	int delkaPole = 0;
	poleVet = readInput(poleVet, &delkaPole);
	qsort(poleVet, delkaPole, sizeof(char*), compareStr);
	for (int i = 0; i < delkaPole; i++)
		printf("%s\n\n", poleVet[i]);
	for (int i = 0; i < delkaPole; i++)
		free(poleVet[i]);
	free(poleVet);
	return 0;
}