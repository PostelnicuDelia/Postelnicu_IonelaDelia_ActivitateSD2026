#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru un nod dintr-o lista simplu inlantuita
typedef struct Nod Nod;
struct Nod {
	Masina info;
	Nod* next;
};

//creare structura pentru tabela de dispersie
// aceasta este un vector de liste
struct HashTable {
	int dim;
	Nod** vector;
};
typedef struct HashTable HashTable;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(Nod* cap_lista) {
	while (cap_lista) {
		afisareMasina(cap_lista->info);
		cap_lista = cap_lista->next;
	}
}

void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = masinaNoua;
	nodNou->next = NULL;

	if (*cap) {
		Nod* aux = *cap;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nodNou;
	}
	else {
		(*cap) = nodNou;
	}
	
}

HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	ht.dim = dimensiune;
	ht.vector = (Nod**)malloc(sizeof(Nod) * dimensiune);
	for (int i = 0;i < dimensiune;i++)
	{
		ht.vector[i] = NULL;
	}

	return ht;
}

int calculeazaHash(int id, int dimensiune) {
	id = id * 23 + 123;
	return id % dimensiune;
}

void inserareMasinaInTabela(HashTable hash, Masina masina) {
	int poz = calculeazaHash(masina.id, hash.dim);
	if (hash.vector[poz]) {
		//avem coliziune
		adaugaMasinaInLista(&hash.vector[poz], masina); //prin indexare s-a pierdut un pointer si de aceea avem nevoie de adresa
	}
	else {
		//nu avem coliziune
		adaugaMasinaInLista(&hash.vector[poz], masina);
	}
}

HashTable citireMasiniDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	HashTable tabela = initializareHashTable(3);
	Masina mCitita;
	if (!file) {
		printf("Fisierul nu exista!\n");
		return tabela;
	}

	while (!feof(file)) {
		mCitita = citireMasinaDinFisier(file);
		inserareMasinaInTabela(tabela, mCitita);
	}
	fclose(file);
	return tabela;

}

void afisareTabelaDeMasini(HashTable ht) {
	for (int i = 0;i < ht.dim;i++) {
		if (ht.vector[i] != NULL) {
			printf("Cluster %d:\n", i+1);
			afisareListaMasini(ht.vector[i]);
			printf("========================================================================================\n");
		}
	}
}

void dezalocareTabelaDeMasini(HashTable* ht) {
	//sunt dezalocate toate masinile din tabela de dispersie
}

float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {

	(*nrClustere) = 0;
	for (int i = 0;i < ht.dim;i++) {
		if (ht.vector[i] != NULL) {
			(*nrClustere)++;
		}
	}

	float* vectorPreturi = malloc(sizeof(float) * (*nrClustere));
	int k = 0;
	

	for (int i = 0;i < ht.dim;i++) {
		if (ht.vector[i] != NULL) {
			float suma = 0;
			int nrMasini = 0;
			Nod* nod = ht.vector[i];;
			while (nod) {
				suma = nod->info.pret + suma;
				nrMasini++;
				nod = nod->next;
			}
			vectorPreturi[k++] = suma / nrMasini;
		}
	}

	return vectorPreturi;
}

Masina getMasinaDupaCheie(HashTable ht, int id) {
	Masina m;
	m.id = -1;
	int hash = calculeazaHash(id, ht.dim);

	if (hash >= 0 && hash < ht.dim) {
		Nod* aux = ht.vector[hash];
		while (aux) {
			if (aux->info.id == id) {
				m = aux->info;
				m.model = malloc(sizeof(char) * (strlen(aux->info.model) + 1));
				strcpy(m.model, aux->info.model);
				m.numeSofer = malloc(sizeof(char) * (strlen(aux->info.numeSofer) + 1));
				strcpy(m.numeSofer, aux->info.numeSofer);
				break;
			}
			aux = aux->next;
		}
	}
	return m;
}

int main() {
	HashTable tabela = citireMasiniDinFisier("masini.txt");
	afisareTabelaDeMasini(tabela);
	Masina m = getMasinaDupaCheie(tabela, 20);
		printf("Masina dupa id este:\n");
	afisareMasina(m);
	int nrClustere;
	float* vectorPreturi = calculeazaPreturiMediiPerClustere(tabela, &nrClustere);
	for (int i = 0;i < nrClustere;i++) {
		printf("Pentru clusterul cu indecele %d, media este %.2f:\n", i, vectorPreturi[i]);
	}

	return 0;
}