////lista = structura de date omogena, liniara, in care fiecare elem retine adresa urmatorului element
////void* = pointer generic, adica permite sa fie pointer la orice tip si face conversie implicit catre acel tip
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//typedef struct Nod Nod;
//
//struct Nod {
//	Masina info;
//	Nod* next;
//};
//
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//void afisareListaMasini(Nod* cap) {
//	while (cap != NULL) {
//		afisareMasina(cap->info);
//		cap = cap->next;
//	}
//}
//
//void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {//** pt ca daca lista e vida, trebuie sa modificam adresa lui cap, sa adaugam o prima adresa
//
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = masinaNoua;
//	nodNou->next = NULL;
//	if ((*cap) == NULL) {
//		(*cap) = nodNou;
//	}
//
//	else {
//		Nod* aux = (*cap);
//		while (aux->next != NULL) { //analogia cu podul
//			aux = aux->next;
//		}
//		aux->next = nodNou;
//	}
//}
//
//void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) {
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = masinaNoua;
//	nodNou->next = *cap;
//	*cap = nodNou;
//}
//
//Nod* citireListaMasiniDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	if (file) {
//		Nod* cap = NULL;
//		while (!feof(file)) {
//			adaugaMasinaInLista(&cap, citireMasinaDinFisier(file));
//		}
//		fclose(file);
//		return cap;
//	}
//	return NULL;
//
//}
//
//void dezalocareListaMasini(Nod** cap) {//** pt ca modificam adresa, o facem NULL
//	while (*cap) {
//		Nod* p = *cap;
//		(*cap) = p->next;
//		if (p->info.numeSofer) {
//			free(p->info.numeSofer);
//		}
//		if (p->info.model) {
//			free(p->info.model);
//		}
//		free(p);
//	}
//
//}
//
//float calculeazaPretMediu(Nod* cap) {
//
//	float suma = 0;
//	int contor = 0;
//
//	while (cap) {
//		contor++;
//		suma = suma + (cap->info.pret);
//		cap = cap->next;
//	}
//	if (contor != 0)
//		return suma / contor;
//
//	return 0;
//}
//
//void stergeMasiniDinSeria(Nod** cap, char serieCautata) {
//
//	while ((*cap) && (*cap)->info.serie == serieCautata) {
//		Nod* temp = *cap;
//		(*cap) = temp->next;
//		if (temp->info.numeSofer)
//			free(temp->info.numeSofer);
//		if (temp->info.model)
//			free(temp->info.model);
//	}
//
//	Nod* p = *cap;
//	while (p) {
//		while (p->next && p->next->info.serie != serieCautata) {
//			p = p->next;
//		}
//
//		if (p->next) {
//			Nod* temp = p->next;
//			p->next = temp->next;
//
//			if (temp->info.model) {
//				free(temp->info.model);
//			}
//			if (temp->info.numeSofer)
//				free(temp->info.numeSofer);
//			free(temp);
//		}
//		else {
//			p = p->next;
//		}
//	}
//}
//
//float calculeazaPretulMasinilorUnuiSofer(Nod* cap,const char* numeSofer) {
//	float pretTotal = 0;
//
//	while (cap) {
//		if (strcmp(cap->info.numeSofer, numeSofer) == 0) {
//			pretTotal += cap->info.pret;
//		}
//		cap = cap->next;
//	}
//	return pretTotal;
//}
//
//int main() {
//
//	Nod* cap = NULL;
//	cap = citireListaMasiniDinFisier("masini.txt");
//	afisareListaMasini(cap);
//
//	printf("Pretul mediu=%5.2f\n", calculeazaPretMediu(cap));
//	printf("\nPretul total pentru soferul Gigel= %5.2f\n", calculeazaPretulMasinilorUnuiSofer(cap, "Gigel"));
//
//
//	printf("Stergere serie A\n");
//	stergeMasiniDinSeria(&cap, 'A');
//
//	printf("\nLista dupa stegre A\n");
//	afisareListaMasini(cap);
//
//
//	dezalocareListaMasini(&cap);
//	printf("\nLista dupa dezalocare\n");
//	afisareListaMasini(cap);
//	return 0;
//
//}
//
////char* = sir =" "