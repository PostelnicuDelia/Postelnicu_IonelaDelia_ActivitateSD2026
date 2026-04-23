// Stiva = structura liniara, omogena : LIFO
// Coada -> FIFO = structura de date, omogena, liniara, 

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

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

typedef struct Nod Nod;

struct Nod {
	Nod* next;
	Masina info;
};


//STACK
void pushStack(Nod** prim, Masina masina) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod)); //am creat un nod nou in memorie
	nodNou->info = masina; //am bagat masina in nod
	nodNou->next =(*prim); //i am dat nodului nou adresa primului nod
	(*prim) = nodNou; //primul nod a devenit noul nod
}

Masina popStack(Nod** prim) {
	if (*prim != NULL) {
		Masina rezultat = (*prim)->info;
		Nod* aux = *prim;
		(*prim) = (*prim)->next;
		free(aux);
		return rezultat;
	}
	else {
		Masina noua;
		noua.id = -1;
		return noua;
	}
}

//int emptyStack(Nod** cap){
//	while (*cap) {
//		Masina m = popStack(cap);
//		free(m.numeSofer); 
//		free(m.model);
//	}
//
//}

Nod* citireStackMasiniDinFisier(const char* numeFisier) {
	FILE* fisier = fopen(numeFisier, "r");
	Nod* stivaMasini = NULL;
	while (!feof(fisier)) {
		pushStack(&stivaMasini, citireMasinaDinFisier(fisier));
	}
	fclose(fisier);

	return stivaMasini;
}

void dezalocareStivaDeMasini(Nod* *cap) {
	Masina m;
	while (*cap) {
		m = popStack(cap);
		free(m.numeSofer);
		free(m.model);
	}
}

int size(Nod* cap) {
	int nr = 0;
	Nod* aux = cap;
	while (aux) {
		nr++;
		aux = aux->next;
	}
	return nr;
}

//QUEUE
typedef struct NodD NodD;
struct NodD {
	Masina info;
	NodD* next;
	NodD* prev;
};

typedef struct listaD listaD;
struct listaD {
	NodD* first;
	NodD* last;
};


void enqueue(listaD* lista, Masina masina) {
	NodD* nodNou = (NodD*)malloc(sizeof(NodD));
	nodNou->info = masina;
	nodNou->prev = NULL;
	nodNou->next = lista->first;

	if (lista->first) {
		lista->first->prev = nodNou;
	}
	else {
		lista->last = nodNou;
	}
	lista->first = nodNou;

}

Masina dequeue(listaD* lista) {
	Masina rezultat;
	if (lista->last) {
		rezultat = lista->last->info;

		lista->last = lista->last->prev;
		if (lista->last) {
			free(lista->last->next);
			lista->last->next = NULL;
		}
		else {
			free(lista->first);
			lista->first = NULL;
		}
	}
	else {
		rezultat.id = -1;
	}
	return rezultat;
}

listaD citireCoadaDeMasiniDinFisier(const char* numeFisier) {
	listaD coada;
	coada.first = coada.last = NULL;

	FILE* f = fopen(numeFisier, "r");
	if (f) {
		while (!feof(f)) {
			enqueue(&coada, citireMasinaDinFisier(f));
		}
		fclose(f);
	}
	return coada;
}

void dezalocareCoadaDeMasini(listaD* lista) {
	while (lista->first) {
		NodD* aux = lista->first;
		lista->first = lista->first->next;
		free(aux->info.model);
		free(aux->info.numeSofer);
		free(aux);
	}
	lista->first = NULL;
	lista->last = NULL;
}


//metode de procesare
Masina getMasinaByID(Nod** prim, int id) {
	Masina aux;
	Masina rez;
	Nod* stivaNoua = NULL;

		while ((*prim) && (*prim)->info.id != id) {
			pushStack(&stivaNoua, popStack(prim));
		}
		if (*prim) {
			aux = popStack(prim);

			rez = aux;
			rez.model = (char*)malloc(sizeof(char) * (strlen(aux.model) + 1));
			strcpy(rez.model, aux.model);

			rez.numeSofer = (char*)malloc(sizeof(char) * (strlen(aux.numeSofer) + 1));
			strcpy(rez.numeSofer, aux.numeSofer);

			pushStack(prim, aux);
		}
		else {
			rez.id = -1;
			
		}

		while (stivaNoua) {
			pushStack(prim, popStack(&stivaNoua));
		}
		return rez;
	
}

float calculeazaPretTotal(listaD coada) { 
	float pretTotal = 0;
	NodD* p = coada.first;

	while (p != NULL) {
		pretTotal += p->info.pret;
		p = p->next; 
	}
	return pretTotal;
}

int main() {
	Nod* stivaM = citireStackMasiniDinFisier("masini.txt");
	afisareMasina(popStack(&stivaM));
	afisareMasina(popStack(&stivaM));
	afisareMasina(getMasinaByID(&stivaM, 3));

	listaD coada = citireCoadaDeMasiniDinFisier("masini.txt");

	printf("pretul total al listei este %5.2f\n", calculeazaPretTotal(coada));

	printf("\n\n");
	printf("Coada:\n");
	afisareMasina(dequeue(&coada));
	afisareMasina(dequeue(&coada));
	dezalocareCoadaDeMasini(&coada);
	


	return 0;
}