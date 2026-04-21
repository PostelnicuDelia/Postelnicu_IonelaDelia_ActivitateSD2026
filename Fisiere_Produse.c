//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//
//struct StructuraProduse {
//	int cod;
//	char* denumire;
//	float pret;
//	float cantitate;
//};
//
//typedef struct StructuraProduse Produs;
//
//void afisareProdus(Produs p) {
//	printf("Cod:%d\n", p.cod);
//	printf("Denumire:%s\n", p.denumire);
//	printf("pret:%5.2f lei\n", p.pret);
//	printf("Cantitate:%5.2f\n\n", p.cantitate);
//}
//
//void afisareVector(Produs* p, int nrProduse) {
//	for (int i = 0;i < nrProduse;i++) {
//		afisareProdus(p[i]);
//	}
//}
//
//Produs citireProdus(FILE* fisier) {
//	Produs p;
//	char buffer[100];
//	char sep[4] = ",;\n";
//	fgets(buffer, 100, fisier);
//	p.cod = atoi(strtok(buffer, sep));
//
//	char* aux = strtok(NULL, sep);
//	p.denumire = (char*)malloc(strlen(aux) + 1);
//	strcpy(p.denumire, aux);
//
//	p.pret = atof(strtok(NULL, sep));
//	p.cantitate = atof(strtok(NULL, sep));
//
//	return p;
//
//}
//
//void adaugare(Produs** p, int* nrProduse, Produs nou) {
//	Produs* aux = (Produs*)malloc(sizeof(Produs) * ((*nrProduse) + 1));
//	for (int i = 0;i < *nrProduse; i++) {
//		aux[i] = (*p)[i];
//	}
//	aux[*nrProduse] = nou;
//	free(*p);
//	(*nrProduse)++;
//	(*p) = aux;
//}
//
//Produs* citireVectorProduse(const char* fisier, int* nrProduse) {
//	FILE* f = fopen(fisier, "r");
//	(*nrProduse) = 0;
//	Produs* vectorP = NULL;
//	while (!feof(f)) {
//		adaugare(&vectorP, nrProduse, citireProdus(f));
//	}
//	fclose(f);
//	return vectorP;
//}
//
//float calculValTot(Produs* p, int nrProduse) {
//	float valoare = 0;
//	for (int i = 0;i < nrProduse; i++)
//		valoare = p[i].cantitate * p[i].pret + valoare;
//	return valoare;
//}
//
//void dezalocare(Produs** p, int* nr) {
//	for (int i = 0;i < *nr;i++) {
//		if ((*p)[i].denumire != NULL)
//			free((*p)[i].denumire);
//	}
//	free(*p);
//	(*nr) = 0;
//}
//
//int main() {
//	Produs* p;
//	int nrProduse = 0;
//	p = citireVectorProduse("produse.txt", &nrProduse);
//	afisareVector(p, nrProduse);
//	float valoareTotala = calculValTot(p, nrProduse);
//	printf("Valoarea totala a produselor este %5.2f lei", valoareTotala);
//	dezalocare(&p, &nrProduse);
//	printf("\nDupa dezalocare:\n");
//	afisareVector(p, nrProduse);
//
//
//}