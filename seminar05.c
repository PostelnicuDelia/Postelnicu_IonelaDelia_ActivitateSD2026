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

//creare structura pentru un nod dintr-o lista dublu inlantuita
struct Nod {
	Masina info;
	struct Nod* next;
	struct Nod* prev;
};

//creare structura pentru Lista Dubla 
struct ListaD {
	int nrNoduri;
	struct Nod* first;
	struct Nod* last;
};

typedef struct ListaD ListaD;
typedef struct Nod Nod;

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

void afisareListaMasini(ListaD lista) {
	printf("Lista contine %d noduri\n", lista.nrNoduri);
	Nod* p = lista.first;
	while (p) {
		afisareMasina(p->info);
		p = p->next;
	}
}

void afisareinversListaMasini(ListaD lista) {
	printf("Lista contine %d noduri\n", lista.nrNoduri);
	Nod* p = lista.last;
	while (p) {
		afisareMasina(p->info);
		p = p->prev;
	}
}

void adaugaMasinaInLista(ListaD* lista, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->prev = lista->last;
	nou->next = NULL;
	nou->info = masinaNoua;
	
	if (lista->last) {
		lista->last->next = nou;
	}
	else {
		lista->first = nou;
	}

	lista->last = nou;
	lista->nrNoduri++;

}

void adaugaLaInceputInLista(ListaD* lista, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->prev = NULL;
	nou->next = lista->first;
	nou->info = masinaNoua;

	if (lista->first) {
		lista->first->prev = nou;
	}

	else {
		lista->last = nou;
	}

	lista->first = nou;
	lista->nrNoduri++;

}

ListaD citireLDMasiniDinFisier(const char* numeFisier) {

	FILE* fisier = fopen(numeFisier, "r");
	ListaD lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;
	if (!fisier) {
		//printf("eroare la deschidere\n");
		return lista;
	}

	while (!feof(fisier)) {
		adaugaMasinaInLista(&lista, citireMasinaDinFisier(fisier));
	}
	fclose(fisier);
	return lista;
	
}

void dezalocareLDMasini(ListaD* lista) {
	//sunt dezalocate toate masinile si lista dublu inlantuita de elemente
	Nod* nod = lista->first;
	while (nod) {
		Nod* aux = nod;
		nod = nod->next;
		if (aux->info.numeSofer) {
			free(aux->info.numeSofer);
		}
		if (aux->info.model) {
			free(aux->info.model);
		}
		free(aux);
		lista->nrNoduri--;
	}
	lista->first = NULL;
	lista->last = NULL;
}


float calculeazaPretMediu(ListaD lista) {
	float pretTotal = 0;
	if (lista.first == NULL) {
		return 0;
	}
	else {
		/*Nod* p = lista.first;
		while (p) {
			pretTotal += p->info.serie;
			p = p->next;
		}*/

		for (Nod* p = lista.first; p != NULL; p = p->next) {
			pretTotal += p->info.pret;
		}
	}


	return pretTotal/lista.nrNoduri;
}

void stergeMasinaDupaID(ListaD* lista, int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
	Nod* p;
	if (lista->first) {
		for (p = lista->first; p != NULL && p->info.id != id; p = p->next);
		if (p == NULL)return;
		else {
			if (p->prev == NULL) {
				if (p->next) {
					p->next->prev = NULL;
				}
				else {//e cazul in care avem un singur element in lista
					lista->last = NULL;
				}
				lista->first = p->next;
				free(p->info.model);
				free(p->info.numeSofer);
				free(p);

			}
			else {
				p->prev->next = p->next;
				if (p->next) {
					p->next->prev = p->prev;
				}
				else {
					lista->last = p->prev;
				}
				
				free(p->info.model);
				free(p->info.numeSofer);
				free(p);

			}
			lista->nrNoduri--;
		}
	}
}

char* getNumeSoferMasinaScumpa(/*lista dublu inlantuita*/) {
	//cauta masina cea mai scumpa si 
	//returneaza numele soferului acestei maasini.
	return NULL;
}

int main() {
	ListaD lista = citireLDMasiniDinFisier("masini.txt");
	afisareinversListaMasini(lista);
	//printf("\nPret Mediu = %5.2f\n", calculeazaPretMediu(lista));

	stergeMasinaDupaID(&lista, 1);
	afisareinversListaMasini(lista);

	stergeMasinaDupaID(&lista, 3);
	afisareinversListaMasini(lista);

	stergeMasinaDupaID(&lista, 10);
	afisareinversListaMasini(lista);

	dezalocareLDMasini(&lista);
	printf("\nDupa dezalocare:");
	afisareListaMasini(lista);

	
	

	return 0;
}